/*------------------------------
Author: carmazhao

Date:	2011/12/20

Function:The proxyCenter is used
	 to dispatch the net info
	 to the target proxy
------------------------------*/
#ifndef HEAD_PROXY_CTR
#define HEAD_PROXY_CTR

#include"Iproxy.h"
#include<map>
using namespace std;

class proxyCenter {
private:
	static proxyCenter * h_inst;
	map<uint_32,Iproxy *> m_proxy_table;

	proxyCenter();
public:
	static proxyCenter * getInstance();
	~proxyCenter();

	void registerProxy(Iproxy *proxy);
	void send_proxy_msg(proxyMsg* msg);
};
#endif
