#include"gsSocket.h"
#include"gsQueue.h"
#include"msg/proxyMsg.h"

IMPLEMENT_SINGLE_MODEL(gsSocket);

gsSocket::gsSocket() {
	m_io_mem = NULL;
	m_cur_limit = 0;
	m_cut_mem = NULL;
	m_cut_mem_size = 0;
}
gsSocket::~gsSocket() {
}

void gsSocket::initial_socket() {
	sys_sockaddr_in		_addr;

	m_fd = sys_tcp_socket();
	//initial the cache mutex
	sys_init_mutex(m_cache_mutex);
	sys_init_mutex(m_write_mutex);

	_addr.sin_family 	= AF_INET;
	_addr.sin_addr.s_addr 	= htonl(INADDR_ANY);
	_addr.sin_port 		= htons(8866);

	sys_bind(m_fd , _addr);
	sys_listen(m_fd);
}

void gsSocket::gs_loop() {
	int_32		_res = 0;
	uint_32		i = 0;
	uint_32		j = 0;
	sys_timeval	_timeval;

	while(true) {
		//set the time out
		_timeval.tv_sec = 0;
		_timeval.tv_usec = 50000;

		//fill in the fd set 	
		sys_fd_zero(&m_fd_set);
		sys_mutex_lock(m_cache_mutex);
			if(m_fd_cache.size() == 0) {
				sys_mutex_unlock(m_cache_mutex);
				continue;
			}
			for(i = 0;i < m_fd_cache.size(); i++) {
				sys_fd_set(m_fd_cache[i] , &m_fd_set);
			}
		sys_mutex_unlock(m_cache_mutex);
		
		//begin to select
		_res = sys_select(&m_fd_set , _timeval);

		if(_res < 0) {
			DEBUG_SHOW("bad select res")
			continue;
		}
		//check if selected
		sys_mutex_lock(m_cache_mutex);
		for(j = 0;j < m_fd_cache.size();j++) {
			if(sys_fd_is_set(m_fd_cache[j],&m_fd_set)){
				build_and_send_msg(m_fd_cache[j]);
			}
		}
		sys_mutex_unlock(m_cache_mutex);
	}
};

void gsSocket::build_and_send_msg(const int_32 & _fd) {
	uint_32		_nread = 0;
	uint_32		_pos   = 0;
	uint_32		_size  = 0;
	int_8*		_reader = NULL;
	
	
	ioctl(_fd , FIONREAD , &_nread);
	if(_nread <= 0) {
		//if no msg then delete the fd
		return;
	}
	//if the io is too big
	if(_nread > IO_LIMIT) {
		DEBUG_SHOW("nread is too large");
		return;
	}
	//initial the io mem to store info stream
	if(m_io_mem == NULL) {
		DEBUG_SHOW("the m_io_mem is null , so we create it");
		m_io_mem = new int_8[IO_MEM_INI];
		m_cur_limit = IO_MEM_INI;
	}
	
	if(m_cur_limit < _nread) {
	/*	DEBUG_SHOW("the m_io_mem is small , so we create it");
		delete m_io_mem;
		m_cur_limit += IO_MEM_INTER;
		m_io_mem = new int_8[m_cur_limit];
*/
		return ;
	}
	//clear mem
	memset(m_io_mem , 0 , m_cur_limit);
	if(read(_fd , m_io_mem , _nread) == -1) {
		DEBUG_SHOW("can't read!");
		return;
	}
	_reader = m_io_mem;
	//construct the proxy msg
	while(_pos < _nread) {
		//get the info size
		memcpy(&_size , _reader , sizeof(_size));
		_size = ntohl(_size);
		_reader += sizeof(_size);
		//check the cut mem
		if(m_cut_mem == NULL) {
			m_cut_mem = new int_8[IO_MEM_INI];
			m_cut_mem_size = IO_MEM_INI;
		}
		//if not enough
		if(m_cut_mem_size < _size) {
			delete m_cut_mem;
			m_cut_mem = NULL;
			m_cut_mem_size += IO_MEM_INTER;
			m_cut_mem = new int_8[m_cut_mem_size];
		}
		memcpy(m_cut_mem , _reader , _size);
		_reader += _size;
		proxyMsg* p_msg = new proxyMsg(m_cut_mem , _size , _fd);	

		gsQueue::get_instance()->put_in_affair(p_msg);
		p_msg = NULL;
		//change pos
		_pos = _pos + sizeof(_size) + _size;
	}
}
 
int_32	gsSocket::get_fd() {
	return m_fd;
}

void gsSocket::push_fd_cache(const int_32 & _fd) {
	sys_mutex_lock(m_cache_mutex);
		m_fd_cache.push_back(_fd);
	sys_mutex_unlock(m_cache_mutex);
}

void gsSocket::rm_fd_cache(const int_32 & _fd) {
	uint_32				i = 0;

	sys_mutex_lock(m_cache_mutex);
	for(;i < m_fd_cache.size();i++) {
		if(m_fd_cache[i] == _fd) {
			close(_fd);
			m_fd_cache.erase(m_fd_cache.begin() + i);
			break;
		}
	}
	sys_mutex_unlock(m_cache_mutex);
}

void gsSocket::send_net_msg(int_32 _fd , NetMsg* _msg) {
	int_32			_res = 0;

//	sys_mutex_lock(m_write_mutex);
	_res = write(_fd , _msg->get_data() , _msg->get_data_size());
//	sys_mutex_unlock(m_write_mutex);
	if(_res <= -1) {
		return ;
	}
}
