/*=============================
Author : carmazhao

Date:   2012/2/25

Function: the proxy to snapshot
=============================*/
#ifndef SNAP_SHOT_PROXY_HEAD_
#define SNAP_SHOT_PROXY_HEAD_
#include"../../core/msg/Iproxy.h"
#include"snapShotCtr.h"
#include"../player/role.h"
	
class snapShotProxy:public Iproxy {
private:
	enum {
		S_ROLE_SNAP_SHOT = 100020
	};
public:
	snapShotProxy();
	~snapShotProxy();
	
	void	dispatchMsg(proxyMsg* _msg);

//**********SEND FUNCTIONS***************
	void 	send_role_snap_shot(const int_32 & _fd , 
				   std::vector<role*>);
};
#endif
