/*-------------------------
Author: carmazhao

Date: 2011/12/17

Function: keep the obj alive
	  in order to save the 
	  memory
--------------------------*/
#ifndef HEAD_OBJPOOL
#define HEAD_OBJPOOL
#include"sys.h"
#include<list>
using namespace std;

template <class _T>
class objPool {
private:
	list<void *>		_pool;
	sys_h_mutex		_mutex;
public:
	objPool() {sys_init_mutex(_mutex);}
	~objPool(){}
	void * malloc_mem() {
		void * p_t = NULL;

		sys_mutex_lock(_mutex);
		if(_pool.empty()) {
			p_t = malloc(sizeof(_T));
			memset(p_t , 0 , sizeof(_T));
		}else {
			list<void *>::iterator it = _pool.begin();
	    		p_t = *it;
	                _pool.pop_front();
		}
		sys_mutex_unlock(_mutex);
		return p_t;
	}	

	void free_mem(void* _p) {
		sys_mutex_lock(_mutex);
		_pool.push_back(_p);
		sys_mutex_unlock(_mutex);
	}
};
#endif
