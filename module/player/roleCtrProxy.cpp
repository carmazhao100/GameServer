#include"roleCtrProxy.h"
#include"../../core/msg/command.h"
#include"../../msgConst.h"
#include"../../Facade.h"
#include"../../core/NetMsg.h"
#include"roleCtr.h"
#include<string.h>


roleCtrProxy::roleCtrProxy() {
	m_msg_arr.push_back(R_CLIENT_LOGIN);
	m_msg_arr.push_back(R_HEART_BEAT_FROM_CLIENT);
	m_msg_arr.push_back(R_ROLE_POSTION_UPDATE);
}

roleCtrProxy::~roleCtrProxy() {
}


void roleCtrProxy::dispatchMsg(proxyMsg * _msg) {
	//check param
	if(_msg == NULL) {
		return ;
	}
	uint_32		_id = _msg->get_proxy_msg_id();

	switch(_id) {
	case R_CLIENT_LOGIN:
		do_client_login(_msg);
	break;
	case R_HEART_BEAT_FROM_CLIENT:	
		do_heart_beat(_msg->get_fd());
	break;
	case R_ROLE_POSTION_UPDATE:
		do_role_postion_update(_msg);
	break;
	}
}

void roleCtrProxy::do_heart_beat(const uint & _fd) {
	command	*		_cmd = new command(msgConst::HEART_BEAT_FROM_CLIENT , _fd);
	
	Facade::get_instance()->send_command_msg(_cmd);       
}

void roleCtrProxy::do_client_login(proxyMsg* _msg) {
	//check param
	if(_msg == NULL) {
		return ;
	}
	command *		_cmd = new command(msgConst::CLIENT_LOGIN , _msg->get_fd());

printf("fd is %d \n" ,_msg->get_fd());
	//first write in the account
	int_8*			_str  = _msg->get_string();
	if(_str == NULL) {
		if(_cmd != NULL) {
DEBUG_SHOW("BEFORE DELETE CMD")
			delete _cmd;
DEBUG_SHOW("CMD deleted")
		}
		return ;
	}
	_cmd->write_str(_str);
printf("name is %s \n" ,_str);
	_str = NULL;
	//read the password info
	_str  = _msg->get_string();
	if(_str == NULL) {
		return ;
	}
	_cmd->write_str(_str);
printf("pwd is %s \n" ,_str);
	_str = NULL;
	Facade::get_instance()->send_command_msg(_cmd);
}

void roleCtrProxy::do_role_move_state_change(proxyMsg* _msg) {
	if(_msg == NULL) {
		return ;
	}
	command * 		_cmd = new command(msgConst::ROLE_MOVE_STATE_CHANGE , _msg->get_fd());
	//write in the state 
	_cmd->write_int_32(_msg->get_int_32());
	Facade::get_instance()->send_command_msg(_cmd);
}

void roleCtrProxy::do_role_postion_update(proxyMsg* _msg) {
	if(_msg == NULL) {	
		return ;
	}
	int_32 			_fd = _msg->get_fd();
	int_32			_x = _msg->get_int_32();
	int_32			_y = _msg->get_int_32();

	roleCtr::get_instance()->change_role_pos(_fd , _x , _y);
}

//****************SEND  FUNCTIONS *******************
void roleCtrProxy::send_heart_beat(int_32  _fd) {
	NetMsg * 		_msg = new NetMsg();
	if(_msg == NULL) {
		return ;
	}	

	uint_32			_size = 0;
	uint_32			_id = S_HEART_BEAT_TO_CLIENT;
	
	_size = sizeof(int_32);
	_msg->write_int_32(_size);
	_msg->write_int_32(_id);
	
	Facade::get_instance()->send_net_msg(_fd , _msg);
	delete _msg;
}

void roleCtrProxy::send_login_ok(int_32 _fd) {
	NetMsg * 		_msg = new NetMsg();
	if(_msg == NULL) {
		return ;
	}	
	uint_32			_size = 0;
	uint_32			_id = S_CLIENT_LOGIN;

	_size = sizeof(int_32);
	_msg->write_int_32(_size);
	_msg->write_int_32(_id);
	
	Facade::get_instance()->send_net_msg(_fd , _msg);
	delete _msg;
}

void roleCtrProxy::send_role_initial(int_32 _fd , role_info * _role_info) {
	NetMsg *		_msg = new NetMsg();

	if(_msg == NULL || _role_info == NULL) {
		return ;
	}
	uint_32			_size = 0;
	uint_32			_id   = S_ROLE_INITIAL;
	
	_size = 8*sizeof(int_32) + strlen(_role_info->get_name());
	_msg->write_int_32(_size);			//write the size
	_msg->write_int_32(_id);			//write the net msg id
	_msg->write_int_32(_role_info->get_id());	//write the role id
	_msg->write_str(_role_info->get_name());	//write the role name
	_msg->write_int_32(_role_info->get_animation_type());//write the role animation type
	_msg->write_int_32(_role_info->get_hp());	//write the hp
	_msg->write_int_32(_role_info->get_map_id());	//write the map id
	_msg->write_int_32(_role_info->get_x());	//write the x
	_msg->write_int_32(_role_info->get_y());	//write the y

	Facade::get_instance()->send_net_msg(_fd , _msg);

	delete _msg;
}
