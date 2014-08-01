#include"mapCtr.h"

//=================GAME MAP
gameMap::gameMap() {
	sys_init_mutex(m_arr_mutex);
}

gameMap::~gameMap() {
}

void gameMap::set_width(const int_32 & _width) {
	m_width = _width;
}

void gameMap::set_height(const int_32 & _height) {
	m_height = _height;
}

int_32	gameMap::get_width() {
	return m_width;
}

int_32 gameMap::get_height() {
	return m_height;
}

void gameMap::add_role(role* _role) {
	if(_role == NULL) {
		return ;
	}
	sys_mutex_lock(m_arr_mutex);
	m_role_arr.push_back(_role);
	sys_mutex_unlock(m_arr_mutex);
}

void gameMap::remove_role(role* _role) {
	if(_role == NULL) {
		return ;
	}

	sys_mutex_lock(m_arr_mutex);
	for(uint_32 i = 0;i < m_role_arr.size();i++) {
		if(m_role_arr[i] == _role) {
			m_role_arr.erase(m_role_arr.begin() + i);
			break;
		}
	}
	sys_mutex_unlock(m_arr_mutex);
}

role* gameMap::get_role(const uint_32 & _order) {
	sys_mutex_lock(m_arr_mutex);
	if(_order >= m_role_arr.size()) {		
		sys_mutex_unlock(m_arr_mutex);
		return NULL;
	}
	sys_mutex_unlock(m_arr_mutex);
	return m_role_arr[_order];
}
//=================GAME MAP CTR
IMPLEMENT_SINGLE_MODEL(mapCtr)

mapCtr::mapCtr() {
}

mapCtr::~mapCtr() {
}

void mapCtr::initial_map_info() {
	//here we should read the ini file
	//intial map id arr
	m_map_id_arr.push_back(26);
	//initial role table
	gameMap*		_game_map = new gameMap();
	_game_map->set_width(1024);
	_game_map->set_height(1024);
	m_map_table[mapCtr::TEST_MAP] = _game_map;
	//initial the display limit
	m_dis_limit.width = 800;
	m_dis_limit.height = 600;
}

void mapCtr::add_role_2_map(int_32 _map_id , role* _role) {
	if(_role == NULL) {
		return ;
	}
	if(m_map_table.find(_map_id) == m_map_table.end()) {
		return ;
	}
	m_map_table[_map_id]->add_role(_role);
}

void mapCtr::remove_role_from_map(int_32 _map_id , role* _role) {
	if(_role == NULL) {
		return ;
	}
	
	if(m_map_table.find(_map_id) == m_map_table.end()) {
		return ;
	}
	m_map_table[_map_id]->remove_role(_role);
}

gameMap* mapCtr::get_map(int_32 _map_id) {
	if(m_map_table.find(_map_id) == m_map_table.end()) {
		return NULL;
	}
	return m_map_table[_map_id];
}

std::vector<int_32> mapCtr::get_map_id_arr() {
	return m_map_id_arr;
}

DISPLAY_LIMIT	mapCtr::get_display_limit() {
	return m_dis_limit;
}
