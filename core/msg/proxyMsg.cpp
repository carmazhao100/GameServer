#include"proxyMsg.h"

IMPLEMENT_OBJ_POOL(proxyMsg)

proxyMsg::proxyMsg(int_8* _content , uint_32 _size , int_32 _fd) {
	uint_32		c_size;
	int_8 *		c_pointer;

	m_fd = _fd;
	m_cur_pos = 0;

	//get the info id 
	memcpy(&m_id,_content,sizeof(m_id)); 
	m_id = ntohl(m_id);
	
	c_size = _size - sizeof(m_id);
	c_pointer = _content + sizeof(m_id);
	
	//if no mem is set
	if(NULL == m_content) {
		m_content = new int_8[c_size];
		m_size = c_size;
	}else {	
		//if mem size is not enough
		if(m_size < c_size) {
			delete m_content;
			m_content = NULL;
			m_content = new int_8[c_size];
			m_size = c_size;
		}
	}
	
	//when the mem is ready for cp
	memcpy(m_content , c_pointer , c_size);
	m_cur_pos = m_content;
}
proxyMsg::~proxyMsg() {
	m_cur_pos = NULL;
}
uint_32 proxyMsg::get_proxy_msg_id() {
	return m_id;
}

int_32	proxyMsg::get_int_32() {
	int_32		_result = 0;

	COPY_FROM_MEM(_result , m_cur_pos);
	_result = ntohl(_result);
	return _result;
}


int_8	proxyMsg::get_int_8() {
	int_8		_result = 0;

	COPY_FROM_MEM(_result , m_cur_pos);
	return _result;
}

int_8*	proxyMsg::get_string() {
	int_32		_size = 0;
	int_8*		_result = 0;

	memcpy((void *)&_size , m_cur_pos , sizeof(_size));
	m_cur_pos += sizeof(_size);
	_size = ntohl(_size);

	//copy the string
	_result = new int_8[_size+1];
	memcpy(_result , m_cur_pos , _size);
	_result[_size] = '\0';
	//copy the string
	m_cur_pos += _size;
	return _result;
}

int_32	proxyMsg::get_fd() {
	return m_fd;
}
