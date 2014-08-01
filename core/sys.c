#include"sys.h"

bool   sys_zero_str(int_8 * buff) {
	if( buff == NULL)  {
		buff[0] = 0;
		return true;
	}
	return false;
}

/****************ABOUT THE SOCKET***************/
//accept a client connection
int_32	 sys_accept (int_32 _socket) {
	int_32		_result = 0;
	sys_sockaddr_in _addr;
	uint_32		_size = sizeof(_addr);
	
	_result = accept(_socket , (sys_sockaddr *)&_addr , &_size);
	if(_result <= -1) {
		printf("sys socket accept failed,the error no is :%d",errno);
		exit(EXIT_FAILURE);
	}
	return _result;
}
// create a socket 
int_32 sys_tcp_socket () {
	int_32		_result = 0;

	_result = socket(AF_INET,SOCK_STREAM,0);
	if(_result <= -1) {
		printf("sys socket initial failed,the error no is :%d",errno);
		exit(EXIT_FAILURE);
	}

	return _result;
}

// bind the socket to an address
int_32 sys_bind (const int_32& _socket , const sys_sockaddr_in& addr) {
	int_32 		_result = 0;
	uint_32 	_size = sizeof(addr);

	_result = bind(_socket , (sys_sockaddr *)&addr , _size);
	if(_result <= -1) {	
		printf("sys socket bind failed,the error no is :%d",errno);
		exit(EXIT_FAILURE);
	}
	
	return _result;
}

// ready to listen the socket
int_32 sys_listen (const int_32& _socket) {
	int_32		_result = 0;
		
	_result = listen(_socket , LISTEN_QUEUE_LENGTH);
	if(_result <= -1) {
		printf("sys socket listen failed,the error no is :%d",errno);
		exit(EXIT_FAILURE);
	}
	return _result;
}

// select opt
int_32 sys_select (sys_fd_set * _fd_set , sys_timeval _timeout) {
	int_32		_result = 0;
	
	_result = select(FD_SETSIZE , _fd_set , (sys_fd_set *)0 , (sys_fd_set *)0 , &_timeout);
	if(_result <= -1) {
		printf("sys socket select failed,the error no is :%d",errno);
		//exit(EXIT_FAILURE);
	}
	return _result;
}

/****************ABOUT THE THREAD***************/
int_32 sys_create_thread (sys_h_thread * ptr_thread , void * (* start_routine)(void *) , void * arg) {
	int_32		_result = 0;

	_result = pthread_create (ptr_thread , NULL , start_routine , arg);
	if(_result <= -1) {
		printf("sys thread create failed,the error no is :%d",errno);
		exit(EXIT_FAILURE);
	}
	return _result;
}

bool	sys_check_thread_alive (const sys_h_thread _thread) {
	bool		_result = true;

	if( pthread_kill (_thread , 0) != 0) {
		_result = false;
	}
	return _result;
}

int_32 sys_init_mutex(sys_h_mutex & _mutex) {
	int_32		_result = 0;
	_result = pthread_mutex_init(&_mutex , NULL);
 	if(_result <= -1) {
		printf("sys mutex initial failed,the error no is :%d",errno);
		exit(EXIT_FAILURE);
	}
	return _result;
}
int_32 sys_mutex_lock (sys_h_mutex & _mutex) {
	int_32		_result = 0;

	_result = pthread_mutex_lock(&_mutex);
	if(_result <= -1) {
		printf("sys mutex lock failed,the error no is :%d",errno);
		exit(EXIT_FAILURE);
	}
	return _result;
}

int_32 sys_mutex_unlock (sys_h_mutex & _mutex) {
	int_32		_result = 0;

	_result = pthread_mutex_unlock(&_mutex);
	if(_result <= -1) {
		printf("sys mutex unlock failed,the error no is :%d",errno);
		exit(EXIT_FAILURE);
	}
	return _result;
}

int_32	sys_init_sem(sys_h_sem & _sem) {
	int_32		_result = 0;

	_result = sem_init(&_sem , 0 , 0);
	if(_result <= -1) {
		printf("sys sem init failed,the error no is :%d",errno);
		exit(EXIT_FAILURE);
	}
	return _result;
}

int_32	sys_p(sys_h_sem & _sem) {
	int_32		_result = 0;

	_result = sem_wait(&_sem);
	if(_result <= -1) {
		printf("sys sem p failed,the error no is :%d",errno);
		exit(EXIT_FAILURE);
	}
	return _result;
}

int_32	sys_v(sys_h_sem & _sem) {
	int_32		_result = 0;

	_result = sem_post(&_sem);
	if(_result <= -1) {
		printf("sys sem v failed,the error no is :%d",errno);
		exit(EXIT_FAILURE);
	}
	return _result;
}
