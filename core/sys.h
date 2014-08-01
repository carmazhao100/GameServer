/*------------------------------------
Author:carmazhao

Date:2011/12/17

FUnction:  The sys.h ecapsulate the system
	   functions 
	   types
	   macros
	   and make it stronger
LibNeeded: pthread
------------------------------------*/
#ifndef SYS_ENCAPSULATE
#define SYS_ENCAPSULATE
//sys socket
#include<sys/socket.h>
#include<netinet/in.h>

//sys standard
#include<unistd.h>
#include<stdlib.h>
#include<memory.h>
#include<sys/time.h>

//sys thread
#include<pthread.h>
#include<semaphore.h>
#include<signal.h>

//sys io
#include<stdio.h>
#include<sys/ioctl.h>
#include<errno.h>


/*+++++++++++++++++DEBUG DEFINE++++++++++++++++*/
#define DEBUG
#ifdef DEBUG
	#define DEBUG_SHOW(str) printf("DEBUG MODE : %s\n" , str);
#else
	#define DEBUG_SHOW(str)
#endif
//---define the used macro
#define	LISTEN_QUEUE_LENGTH	5
#define AFFAIR_THREAD_NUM	6
#define AFFAIR_QUEUE_LENGTH	100
#define MAX_SQL_LENGTH		256
//socket used macro
#define	sys_fd_is_set		FD_ISSET
#define sys_fd_zero		FD_ZERO
#define sys_fd_set		FD_SET
#define sys_fd_clear		FD_CLR
//define the objPool use macro
#define DEFINE_OBJ_POOL(_T) private:\
				static objPool<_T> _pool;\
			    public:\
				void* operator new (size_t size) {return _pool.malloc_mem();}\
    				void operator delete(void* p) {_pool.free_mem(p);}
#define IMPLEMENT_OBJ_POOL(_T) objPool<_T> _T::_pool;

//define the copy mem
#define COPY_FROM_MEM(_target,_mem)  memcpy(&_target , _mem , sizeof(_target));\
				     _mem += sizeof(_target);\
//define the single instance pattern
#define DEFINE_SINGLE_MODEL(_T)	private:\
					static _T * h_inst;\
				public:\
					static _T * get_instance();

#define IMPLEMENT_SINGLE_MODEL(_T) 	_T * _T::h_inst(NULL);\
					_T * _T::get_instance() {\
						if(h_inst == NULL) {\
							h_inst = new _T();\
						}\
						return h_inst;\
					}
				  

//---ecapsulate the data kind
typedef long long               int_64;
typedef unsigned long long      uint_64;
typedef unsigned int            uint_32;
typedef int 			int_32;
typedef unsigned short		uint_16;
typedef short 			int_16;
typedef unsigned char 		uint_8;
typedef char 			int_8;

//---ecapsulate the system var type
typedef struct sockaddr_in 	sys_sockaddr_in;
typedef struct sockaddr		sys_sockaddr;
typedef        fd_set		sys_fd_set;
typedef	struct timeval		sys_timeval;

typedef	       pthread_t	sys_h_thread;
typedef	       pthread_mutex_t  sys_h_mutex;
typedef	       sem_t		sys_h_sem;	

//---ecapsulate the system interface
bool   	sys_zero_str(int_8 * buff);

int_32 		sys_tcp_socket ();
int_32 		sys_bind (const int_32 & _socket , const sys_sockaddr_in & addr);
int_32 		sys_listen (const int_32 & _socket);
int_32		sys_select (sys_fd_set * _fd_set , sys_timeval _timeout);
int_32		sys_accept (int_32 _socket);

int_32		sys_create_thread (sys_h_thread * ptr_thread , void * (* start_routine)(void *) , void * arg);
bool   		sys_check_thread_alive (const sys_h_thread _thread);

int_32 		sys_init_mutex(sys_h_mutex & _mutex);
int_32 		sys_mutex_lock (sys_h_mutex & _mutex);
int_32		sys_mutex_unlock (sys_h_mutex & _mutex);

int_32		sys_init_sem(sys_h_sem &);
int_32		sys_p(sys_h_sem &);
int_32		sys_v(sys_h_sem &);

#endif
