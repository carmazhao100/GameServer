/*========================================
Author:		carmazhao

Date:		2011/12/26

Function:	The class is used to count
		the time of the sys.The unit
		is 1ms 1s = 1000ms
========================================*/
#ifndef H_TIME_MANAGER
#define H_TIME_MANAGER
#include"sys.h"
#include<vector>
using namespace std;

typedef  void (*handle_func)(void *);
class embed_handleUnit{
public:
 	uint_32 	m_cur_time;
	uint_32		m_tot_time;
	handle_func 	m_handler;
	void *		m_param;

	void 		check();
	bool	operator == (const embed_handleUnit & _unit) {
		if(this->m_handler == _unit.m_handler &&
		   this->m_param == _unit.m_param) {
			return true;
		}
		return false;
	}
};

class gsTimer {
	DEFINE_SINGLE_MODEL(gsTimer)
public:
	~gsTimer();
	sys_h_thread			init_time_manager();
	void 				add_timer_event(uint_32 interval = 0,handle_func handle = NULL , void * _param = NULL);
	void 				remove_timer_event(handle_func);
	void 				remove_timer_unit(embed_handleUnit _unit);
	void 				real_timer_handler();
private:
	vector<embed_handleUnit> 	m_handle_unit_arr;
	sys_h_thread			m_thread_timer;

	gsTimer();
	void 				run_funcs();
};
#endif
