#include"gsTimer.h"

IMPLEMENT_SINGLE_MODEL(gsTimer)
static void *helper_time_handler(void *p) {
         (static_cast<gsTimer*>(p))->real_timer_handler();
	 return NULL;
 }


gsTimer::gsTimer() {
}
gsTimer::~gsTimer() {
}
sys_h_thread gsTimer::init_time_manager() {
	sys_create_thread(&m_thread_timer,helper_time_handler,this);	
	return m_thread_timer;
}
void gsTimer::add_timer_event(uint_32 _inter,handle_func _handler , void * _param) {
	embed_handleUnit 	_unit;
	
	_unit.m_cur_time = 0;
	_unit.m_tot_time = _inter;
	_unit.m_handler = _handler;
	_unit.m_param = _param;

	m_handle_unit_arr.push_back(_unit);
}
void gsTimer::remove_timer_event(handle_func _handler) {
	uint_32		i = 0;

	for(;i < m_handle_unit_arr.size();i++) {
		if(m_handle_unit_arr[i].m_handler == _handler) {
			m_handle_unit_arr.erase(m_handle_unit_arr.begin() + i);	
		}
	}
}
void gsTimer::real_timer_handler() {	
	sys_timeval 	_tempval;

	while(true) {	
	       	_tempval.tv_sec = 0;
       		_tempval.tv_usec = 1000;
	
       		sys_select(0 , _tempval);
		run_funcs();
	}
}
void gsTimer::run_funcs() {
	uint_32		i = 0;
	for(;i < m_handle_unit_arr.size();i++) {	
		m_handle_unit_arr[i].check();
	} 
} 

void gsTimer::remove_timer_unit(embed_handleUnit _unit) {
	uint_32					i = 0;

	for(;i < m_handle_unit_arr.size();i++) {
		if(m_handle_unit_arr[i] == _unit) {
			m_handle_unit_arr.erase(m_handle_unit_arr.begin() + i);
		}
	}
}

/********************EMBED_HANDLEUNIT****************************/
void embed_handleUnit::check(){
	if(m_cur_time >= m_tot_time) {	
		if(m_handler != NULL) {
			(*m_handler)(m_param);
		}
		m_cur_time = 0;
	}else{
		m_cur_time++;
	}
}
