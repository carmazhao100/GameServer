#include"snapShotProxy.h"
#include"../../Facade.h"

snapShotProxy::snapShotProxy() {
}

snapShotProxy::~snapShotProxy() {
}

void snapShotProxy::dispatchMsg(proxyMsg* _msg) {
}

void snapShotProxy::send_role_snap_shot(const int_32 & _fd ,
					std::vector<role*> _role_arr) {
	NetMsg* 		_msg = new NetMsg();
	if(_msg == NULL) {
		return ;
	}
	int_32				_size = 0;	
	int_32				_msg_id = S_ROLE_SNAP_SHOT;
	int_32				_num = _role_arr.size();
		
	_size = sizeof(int_32) + //msg id
		sizeof(int_32) + //num of roles
		sizeof(int_32) * 5 * _num; // all role info
	_msg->write_int_32(_size);
	_msg->write_int_32(_msg_id);
	_msg->write_int_32(_num);
	for(uint_32 i = 0;i < _role_arr.size();i++) {
		_msg->write_int_32(_role_arr[i]->get_role_info()->get_id());
		_msg->write_int_32(_role_arr[i]->get_role_info()->get_animation_type());
		_msg->write_int_32(_role_arr[i]->get_role_info()->get_x());
		_msg->write_int_32(_role_arr[i]->get_role_info()->get_y());
		_msg->write_int_32(_role_arr[i]->get_role_info()->get_mov_state());
	}
	Facade::get_instance()->send_net_msg(_fd , _msg);
	if(_msg != NULL) {
		delete _msg;
	}
}
