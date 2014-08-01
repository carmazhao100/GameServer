#include"roleCtrMediator.h"
#include"../../msgConst.h"
#include"roleCtr.h"
#include"../../Facade.h"

roleCtrMediator::roleCtrMediator() {
	m_msg_arr.push_back(msgConst::CLIENT_LOGIN);
	m_msg_arr.push_back(msgConst::HEART_BEAT_FROM_CLIENT);
	m_msg_arr.push_back(msgConst::ROLE_MOVE_STATE_CHANGE);
}

roleCtrMediator::~roleCtrMediator() {
}


void roleCtrMediator::dispatchMsg(command *_cmd) {
	uint_32			_msg_id = _cmd->get_msg_name();
	int_8*			_acc = NULL;
	int_8*			_psw = NULL;
	int_32			_fd  = _cmd->get_fd();
//about role move state
	int_32			_mov_state = 0;

	switch(_msg_id) {
	case msgConst::CLIENT_LOGIN:
		_acc = _cmd->read_str();
		_psw = _cmd->read_str();
		if(roleCtr::get_instance()->validate_login(_acc , _psw)) {
		//login success
			roleCtr::get_instance()->add_login_client(_acc , _cmd->get_fd());
		}else {
		//login fail
			Facade::get_instance()->remove_fd(_fd);
		}
	break;
	case msgConst::HEART_BEAT_FROM_CLIENT:
		roleCtr::get_instance()->heart_beat_dispatch(_cmd->get_fd());
	break;
	case msgConst::ROLE_MOVE_STATE_CHANGE:
		_mov_state = _cmd->read_int_32();	
		roleCtr::get_instance()->change_role_move_state(_mov_state , _cmd->get_fd());
	break;
	}
}
