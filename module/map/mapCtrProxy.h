/*-===========================
Author : carmazhao

Date:  2012/2/24
 
Function:the proxy of the map 
	module
=============================*/
#ifndef MAP_CTR_PROXY_HEAD_
#define MAP_CTR_PROXY_HEAD_
#include"../../core/msg/Iproxy.h"

class mapCtrProxy:public Iproxy {
private:
	enum {
	};
public:
	~mapCtrProxy();
	mapCtrProxy();

	void 	dispatchMsg(proxyMsg* _msg);
};
#endif
