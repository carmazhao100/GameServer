#include"roleCtr.h"
#include<mysql/mysql.h>
#include"../../Facade.h"
#include"roleCtrProxy.h"
#include"../../core/gsSocket.h"
#include"../../core/msg/command.h"
#include"../../Facade.h"
#include"../../msgConst.h"


IMPLEMENT_SINGLE_MODEL(roleCtr)

roleCtr::roleCtr() {
	sys_init_mutex(m_list_mutex);
}

roleCtr::~roleCtr() {
}


void	roleCtr::heart_beat_dispatch(const int_32 & _fd) {
	uint_32		i = 0;

	sys_mutex_lock(m_list_mutex);
	for(;i < m_role_list.size();i++) {
		if(m_role_list[i]->get_fd() == _fd) {
			m_role_list[i]->heart_beat();
			break;
		}
	}
	sys_mutex_unlock(m_list_mutex);
}

bool 	roleCtr::validate_login(int_8* _acc , int_8* _psw) {	
	MYSQL_RES * 		_res = NULL;
	command*		_cmd = NULL;

	//check the param
	if(_acc == NULL || _psw == NULL) {
		return false;
	} 
	//construct the sql 
	snprintf(m_sql , MAX_SQL_LENGTH , \
		 "SELECT * FROM player_account WHERE p_account = '%s' AND p_password = '%s'" , _acc , _psw);
	//check the m_sql
	if(m_sql == NULL) {
		return false;
	}
	_res = Facade::get_instance()->execute_get(m_sql);
	if(_res == NULL) {
		return false;
	}else {
		return true;
	}
}

void 	roleCtr::add_login_client(int_8* _acc , int_32 _fd) {
	//check param
	if(_acc == NULL) {
		return;
	}
	role*			_role = new role(_fd , _acc);
	int_32			_map_id = 0;
	//tell the map to add role
	if(_role == NULL) {
		return;
	}
	_map_id = _role->get_role_info()->get_map_id();
	command *			_cmd = new command(msgConst::ROLE_ADD_TO_MAP);
	_cmd->write_int_32(_map_id);
	_cmd->write_int_32((int_32)(_role));
	
	Facade::get_instance()->send_command_msg(_cmd);

	if(_cmd != NULL) {
		delete _cmd;
	}
	
	sys_mutex_lock(m_list_mutex);
	m_role_list.push_back(_role);
	sys_mutex_unlock(m_list_mutex);
}

void 	roleCtr::beat_to_client(int_32 _fd) {
	roleCtrProxy			_proxy;

	_proxy.send_heart_beat(_fd);
}
void  	roleCtr::send_login_ok(const int_32 &_fd) {
	roleCtrProxy			_proxy;
	
	_proxy.send_login_ok(_fd);
}

void 	roleCtr::remove_client(const int_32 & _fd) {
	uint_32 		i = 0;
	role*			_p_role = NULL;

	sys_mutex_lock(m_list_mutex);
	for(;i < m_role_list.size();i++) {
		if(m_role_list[i]->get_fd() == _fd) {
			_p_role = m_role_list[i];
			//delete from role list
			m_role_list.erase(m_role_list.begin()+i);
			//delete from gsSocket
			Facade::get_instance()->remove_fd(_p_role->get_fd());
			delete _p_role;
			break;
		}
	}
	sys_mutex_unlock(m_list_mutex);
}

role*	roleCtr::get_role_by_id(const int_32 & _id){
	uint_32				_i = 0;

	
	sys_mutex_lock(m_list_mutex);
	for(;_i < m_role_list.size();_i++) {
		if(m_role_list[_i]->get_role_info()->get_id() == _id) {
		sys_mutex_unlock(m_list_mutex);
			return m_role_list[_i];
		}
	}
	sys_mutex_unlock(m_list_mutex);
	return NULL;
}

void 	roleCtr::send_role_info_to_client(role* _role) {
	if(_role == NULL) {
		return ;
	}

	role_info * 			_role_info = NULL;
	roleCtrProxy			_proxy;
	int_32				_fd = 0;

	_role_info = _role->get_role_info();
	_fd 	   = _role->get_fd();

	if(_role_info == NULL) {
		return ;
	}

	_proxy.send_role_initial(_fd , _role_info);
}

void roleCtr::change_role_move_state(const int_32 & _state , const int_32 & _fd){
	role* 			_role = NULL;
	
	_role = get_role_by_fd(_fd);
	if(_role == NULL) {
		return ;
	}
	_role->get_role_info()->set_mov_state(_state);
}

role *  roleCtr::get_role_by_fd(const int_32 & _fd){
	uint_32 		_i = 0;

	sys_mutex_lock(m_list_mutex);
	for(;_i < m_role_list.size();_i++) {
		if(m_role_list[_i]->get_fd() == _fd) {
			sys_mutex_unlock(m_list_mutex);
			return m_role_list[_i];
		}
	}
	sys_mutex_unlock(m_list_mutex);
}

void roleCtr::change_role_pos(const int_32 & _fd,
			      const int_32 & _x,
			      const int_32 & _y) {
	role*			_role = NULL;
	_role = get_role_by_fd(_fd); 	
	if(_role == NULL) {
		return ;
	}
	_role->get_role_info()->set_x(_x);
	if(_role == NULL) {
		return ;
	}
	_role->get_role_info()->set_y(_y);
}
