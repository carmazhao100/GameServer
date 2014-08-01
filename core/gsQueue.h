/*------------------------------------
Author: carmazhao

Date:	2011/12/23

Function: there is two queue, one for
	  get and one for read
------------------------------------*/
#ifndef HEAD_QUEUE
#define HEAD_QUEUE
#include"sys.h"
#include"msg/proxyMsg.h"
#include<queue>
// the single queue

class affair_queue {
private:
	proxyMsg* 	m_queue[AFFAIR_QUEUE_LENGTH];
	int_32		m_begin;
	int_32		m_end;
public:

	affair_queue();
	~affair_queue();

	bool 		push(proxyMsg *);
	proxyMsg*	pop();
};

//the queue manager
class gsQueue {
	DEFINE_SINGLE_MODEL(gsQueue)
private:
	/*affair_queue * 		m_in_queue;
	affair_queue * 		m_out_queue;
*/
	std::queue<proxyMsg*> * 		m_in_queue;
	std::queue<proxyMsg*> * 		m_out_queue;

	
	sys_h_mutex 		m_ex_mutex;
	sys_h_mutex		m_deal_mutex;
	
	sys_h_sem		m_sem;//for the exchange 
	gsQueue();
public:
	~gsQueue();
	bool		put_in_affair(proxyMsg *);
	proxyMsg* 	get_out_affair();
};


#endif
