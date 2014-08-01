#include"gsQueue.h"

IMPLEMENT_SINGLE_MODEL(gsQueue)

gsQueue::gsQueue() {
	m_in_queue = new std::queue<proxyMsg*>();
	m_out_queue = new std::queue<proxyMsg*>();
	
	sys_init_mutex(m_ex_mutex);
	sys_init_mutex(m_deal_mutex);

	sys_init_sem(m_sem);
}

gsQueue::~gsQueue() {
	delete m_in_queue;
	delete m_out_queue;
}

bool gsQueue::put_in_affair(proxyMsg * _msg) {
	bool		_result = true;

	sys_mutex_lock(m_ex_mutex);	
if(_msg->get_proxy_msg_id() == 500000) {
	printf("id is %d   pushed\n" , _msg->get_proxy_msg_id());
}
	m_in_queue->push(_msg);
	sys_v(m_sem);
	sys_mutex_unlock(m_ex_mutex);	

	return _result;
}

proxyMsg* gsQueue::get_out_affair() {
	proxyMsg*	_result = NULL;
	std::queue<proxyMsg *>*	_tmp = NULL;
	
	//get the deal affair mutex
	sys_mutex_lock(m_deal_mutex);
	if(m_out_queue->size() == 0) {
		//if no affair then change the queue
		sys_p(m_sem);
		sys_mutex_lock(m_ex_mutex);	
		
		_tmp = m_in_queue;
		m_in_queue = m_out_queue;
		m_out_queue = _tmp;
		//clear the sem for the new empty queue
		sys_init_sem(m_sem);
		sys_mutex_unlock(m_ex_mutex);	
	}else{
		_result = m_out_queue->front();
		m_out_queue->pop();
if(_result->get_proxy_msg_id() == 500000) {
printf("id is %d   out\n" , _result->get_proxy_msg_id());
}
	}
	sys_mutex_unlock(m_deal_mutex);
	return _result;
}
/**********************	AFFAIR_QUEUE*************************/
affair_queue::affair_queue() {
	memset(m_queue , 0 , sizeof(proxyMsg *) * AFFAIR_QUEUE_LENGTH);
	m_begin = 0;
	m_end = 0;
}

affair_queue::~affair_queue() {
}

bool affair_queue::push(proxyMsg * _pProxy) {
	if((m_begin + 1)%AFFAIR_QUEUE_LENGTH != m_end) {
		m_queue[m_begin] = _pProxy; 
		m_begin = (m_begin + 1) % AFFAIR_QUEUE_LENGTH;
		return true;
	}
	return false;
}

proxyMsg* affair_queue::pop() {
	proxyMsg * 	_result = NULL;

	//if queue is empty
	if(m_end == m_begin) {
		return _result;
	}
	
	_result = m_queue[m_end];
	m_queue[m_end] = NULL;
	m_end = (m_end + 1) % AFFAIR_QUEUE_LENGTH;

	return _result;
}

