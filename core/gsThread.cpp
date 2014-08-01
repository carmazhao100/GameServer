#include"gsThread.h"
#include"gsSocket.h"
#include"gsQueue.h"
#include"msg/proxyCenter.h"

IMPLEMENT_SINGLE_MODEL(gsThread)
//helper functions
static void * accept_helper(void *p) {
	(static_cast<gsThread*>(p))->accept_deal();
	return 0;
}

static void * affair_helper(void *p) {
	(static_cast<gsThread*>(p))->affair_deal();
	return 0;
}

gsThread::gsThread() {
}
gsThread::~gsThread() {
}

void gsThread::create_affair_thread() {
	int_32		_result = 0;
	sys_h_thread	_hThread ;

	_result = sys_create_thread(&_hThread , affair_helper , this);
	if(0 != _result) {
		return ;
	}
	m_thread_arr.push_back(_hThread);
}

void gsThread::create_accept_thread() {
	int_32		_result = 0;
	sys_h_thread	_hThread ;

	_result = sys_create_thread(&_hThread , accept_helper , this);
	if(0 != _result) {
		return ;
	}
	m_thread_arr.push_back(_hThread);
}

void gsThread::create_db_thread() {
}


void gsThread::create_guard_thread() {
}

void gsThread::affair_deal() {
	proxyMsg * 	_p_msg;

	while(true) {
		_p_msg = gsQueue::get_instance()->get_out_affair();
		if(NULL == _p_msg) {
			continue ;
		}
		proxyCenter::getInstance()->send_proxy_msg(_p_msg);
		delete _p_msg;
		_p_msg = NULL;
	}
}


void gsThread::guard_deal() {
}

void gsThread::db_deal() {
}

void gsThread::accept_deal() {
	int_32		_fd;
	
	while(true) {	
		DEBUG_SHOW("GET READY TO ACCEPT")
		_fd = sys_accept(gsSocket::get_instance()->get_fd());
		gsSocket::get_instance()->push_fd_cache(_fd);
	}
}
