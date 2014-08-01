#ifndef HEAD_TEST_PROXY
#define HEAD_TEST_PROXY
#include"Iproxy.h"
#include"typeDef.h"
#include<iostream>
using namespace std;
class testProxy:public Iproxy {
public:
	testProxy() {
		init_msg_arr();
	}
	virtual void init_msg_arr() {
		proxy_msg_id id = 10;
		m_msg_arr.push_back(id);
	}
	virtual void dispatchMsg(proxyMsg *msg) {
		cout<<"in dispatchMsg"<<endl;
		proxy_msg_id id = msg->get_proxy_msg_id();
		cout<<"the result is "<<id<<endl;
	}
};
#endif
