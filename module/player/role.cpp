#include"role.h"
#include<string.h>
#include"../../Facade.h"
#include"../../core/NetMsg.h"
#include"roleCtr.h"
#include"../../core/msg/command.h"
#include"../../msgConst.h"
#include"../map/mapUtil.h"


/*------------role_info-----------*/
IMPLEMENT_OBJ_POOL(role_info)
role_info::role_info (const uint_32 & 	_id,
		int_8*			_name,
		const int_32 & 		_an_type,
		const int_32 &		_hp,
		const int_32 &		_map_id,
		const int_32 & 		_x,
		const int_32 & 		_y) {

	//check the param
	if(_name == NULL) {
		return;
	}
	m_id = _id;
	m_hp = _hp;
	strcpy(m_name , _name);
	m_map_id = _map_id;
	m_x = _x;
	m_y = _y;
	m_mov_state = role_info::STATIC_UP;	
	m_animation_type = _an_type;
}

role_info::~role_info() {
}

uint_32	role_info::get_id() {
	return m_id;
}


//===============GET FUNCTIONS
int_8*	role_info::get_name() {
	return m_name;
}

int_32	role_info::get_hp() {
	return m_hp;
}

int_32	role_info::get_map_id() {
	return m_map_id;
}

int_32 role_info::get_x() {
	return m_x;
}

int_32 role_info::get_y() {
	return m_y;
}

int_32	role_info::get_mov_state() {
	return m_mov_state;
}

int_32	role_info::get_animation_type() {
	return m_animation_type;
}
//===============SET FUNCTIONS
void 	role_info::set_id(const int_32 & _id) {
	m_id = _id;
}

void 	role_info::set_name(int_8* _name){
	if(_name == NULL){
		return ;
	}
	strcpy(m_name , _name);
}

void 	role_info::set_hp(const int_32 & _hp) {
	m_hp = _hp;
}

void 	role_info::set_map_id(const int_32 & _map_id) {
	m_map_id = _map_id;
}

void 	role_info::set_x(const int_32 & _x) {
	m_x = _x;
}

void 	role_info::set_y(const int_32 & _y) {
	m_y = _y;
}

void 	role_info::set_mov_state(const int_32 & _state) {
	m_mov_state = _state;
}

void 	role_info::set_animation_type(const int_32 & _type) {
	m_animation_type = _type;
}

void 	role_info::do_move() {
	switch(m_mov_state) {
	case	MOVE_UP:
		m_y -= mapUtil::MOVE_SPEED;
	break;
	case 	MOVE_DOWN:
		m_y += mapUtil::MOVE_SPEED;
	break;
	case 	MOVE_LEFT:
		m_x -= mapUtil::MOVE_SPEED;
	break;
	case 	MOVE_RIGHT:
		m_x += mapUtil::MOVE_SPEED;
	break;
	default:
	break;
	}
}
/*-----------heart_beater--------*/
heart_beater::heart_beater() {
	m_cur_time = 0;
}
heart_beater::~heart_beater() {
}
static void helper_heart_beat(void * _p) {
	(static_cast<heart_beater *>(_p))->check();
}
void heart_beater::run() {
	Facade::get_instance()->add_timer(1000 , helper_heart_beat , this);
}

void heart_beater::stop() {
	embed_handleUnit       _unit;
	_unit.m_handler = helper_heart_beat;
	_unit.m_param = this;
	Facade::get_instance()->remove_timer_unit(_unit);
}

void heart_beater::beat(int_32	_fd) {
//  verify the server obj beat
	m_cur_time = 0; 
//send the beat msg to roleCtr
	roleCtr::get_instance()->beat_to_client(_fd);
}
void heart_beater::check() {
	if(m_cur_time < HEART_BEAT_LIMIT) {
		++m_cur_time;
		return ;
	}
	roleCtr::get_instance()->remove_client(m_fd);
	Facade::get_instance()->remove_fd(m_fd);
}

void heart_beater::set_fd(const int_32 & _fd) {
	m_fd = _fd;
}
/*-----------role--------*/
IMPLEMENT_OBJ_POOL(role)

role::role (int_32		_fd ,
	int_8 *		_account){
	//check the param
	if(_account == NULL) {
		return ;
	}

	MYSQL_RES*	_res = NULL;
	MYSQL_ROW 	_row;

	m_fd = _fd;
	m_hbeater.set_fd(_fd);

	m_sql[0] = '\0';
	snprintf(m_sql , MAX_SQL_LENGTH , 
		"SELECT * FROM role_info WHERE r_account = '%s'" , _account);
	//check the m_sql
	if(m_sql == NULL) {
		return ;
	}

	//get role info data from db
	_res = Facade::get_instance()->execute_get(m_sql);
	if(_res == NULL)  {
		return;
	}
	
	_row = mysql_fetch_row(_res);
	m_role_info = new role_info(atoi(_row[DB_ROLE_ID]) , 
					_row[DB_ROLE_NAME] ,
					atoi(_row[DB_ROLE_AN_TYPE]) ,
					atoi(_row[DB_ROLE_HP]),
					atoi(_row[DB_ROLE_MAP_ID]),
					atoi(_row[DB_ROLE_X]),
					atoi(_row[DB_ROLE_Y]));
	//create heart beater
	m_hbeater.run();
	roleCtr::get_instance()->send_login_ok(m_fd);
	roleCtr::get_instance()->send_role_info_to_client(this);
}
role::~role() {
DEBUG_SHOW("DELETE ROLE")
	write_back_data();
	//tell the map to delete the role
	command * 	_cmd = new command(msgConst::ROLE_REMOVE_FROM_MAP);
	_cmd->write_int_32(m_role_info->get_map_id());
	_cmd->write_int_32((int_32)(this));
	Facade::get_instance()->send_command_msg(_cmd);
	if(_cmd != NULL) {
		delete _cmd;
	}
	if(m_role_info != NULL) {	
		delete m_role_info;
	}
	m_hbeater.stop();
}

void role::write_back_data() {
	bool		_result = false;

	m_sql[0] = '\0';
	snprintf(m_sql , MAX_SQL_LENGTH , 
	"UPDATE role_info SET r_hp = %d ,\
			      r_map_id = %d ,\ 
			      r_x = %d ,\
			      r_y = %d WHERE r_id = %d" , 
							m_role_info->m_hp , 
							m_role_info->m_map_id ,
							m_role_info->m_x ,
							m_role_info->m_y ,
							m_role_info->m_id);

	_result = Facade::get_instance()->execute_set(m_sql);
	if(!_result) {
		//log the failure
	}
}

void 	role::heart_beat() {
	m_hbeater.beat(m_fd);
}

int_32	role::get_fd() {
	return m_fd;
}

role_info*  role::get_role_info() {
	return m_role_info;
}

