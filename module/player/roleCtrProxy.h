/*=================================
Author:	carmazhao

Date:	2011/12/28

Function: the net proxy for role module
=================================*/
#ifndef HEAD_ROLE_CTR_PROXY
#define HEAD_ROLE_CTR_PROXY
#include"../../core/msg/Iproxy.h"
#include"role.h"

class roleCtrProxy:public Iproxy {
private:
	enum {
	// info to send to client
	S_CLIENT_LOGIN = 100000,
	S_HEART_BEAT_TO_CLIENT = 100001,
	S_ROLE_INITIAL = 100010,
	//info from client
	R_CLIENT_LOGIN = 500000,
	R_HEART_BEAT_FROM_CLIENT = 500001,
	R_ROLE_MOVE_STATE_CHANGE = 500010,
	R_ROLE_POSTION_UPDATE = 500011
	};
public:
	roleCtrProxy();
	~roleCtrProxy();

	void 	dispatchMsg(proxyMsg* _msg);

	void	do_heart_beat(const uint &);
	void 	do_client_login(proxyMsg * _msg);

	void 	do_role_move_state_change(proxyMsg* _msg);
	void 	do_role_postion_update(proxyMsg * _msg);

/**********************SEND FUNCS**************************/
	void 	send_heart_beat(int_32 _fd);
	void 	send_login_ok(int_32 _fd);
	void 	send_role_initial(int_32 _fd , role_info * _role_info);
};
#endif
