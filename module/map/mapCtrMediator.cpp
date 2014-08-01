#include"mapCtrMediator.h"
#include"../player/role.h"
#include"mapCtr.h"
#include"../../core/msg/command.h"
#include"../../msgConst.h"

mapCtrMediator::mapCtrMediator() {
	m_msg_arr.push_back(msgConst::ROLE_ADD_TO_MAP);
	m_msg_arr.push_back(msgConst::ROLE_REMOVE_FROM_MAP);
}

mapCtrMediator::~mapCtrMediator() {
}

void mapCtrMediator::dispatchMsg(command * _cmd) {
	uint_32			_msg_id = _cmd->get_msg_name();
//about add role to map
	int_32			_map_id = 0;
	role*			_role = NULL;
	
	
	switch(_msg_id)  {
	case msgConst::ROLE_ADD_TO_MAP:
		_map_id = _cmd->read_int_32();
		_role = (role*)(_cmd->read_int_32());
printf("THE MAP ID IS %d\n" , _map_id);
		mapCtr::get_instance()->add_role_2_map(_map_id , _role);
	break;
	case msgConst::ROLE_REMOVE_FROM_MAP:
		_map_id = _cmd->read_int_32();
		_role = (role*)(_cmd->read_int_32());
		mapCtr::get_instance()->remove_role_from_map(_map_id , _role);
	break;
	}
}
