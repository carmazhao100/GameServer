#ifndef HEAD_GS_THREAD
#define HEAD_GS_THREAD

#include"sys.h"
#include<vector>
using namespace std;

class gsThread {
	DEFINE_SINGLE_MODEL(gsThread)
private:
	vector<sys_h_thread>	m_thread_arr;
	
	gsThread();
public:
	~gsThread();
	void 		add_to_thread_arr(sys_h_thread &);
	
	void		create_affair_thread();
	void 		create_accept_thread();
	void		create_db_thread();
	void 		create_guard_thread();
	
	void 		affair_deal();
	void 		guard_deal();
	void 		db_deal();
	void 		accept_deal();
};
#endif
