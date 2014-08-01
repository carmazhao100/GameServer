#include"snapShotCtr.h"
#include"../../Facade.h"
#include"../map/mapUtil.h"
#include"../player/role.h"
#include"../../gsDataStruct.h"
#include"snapShotProxy.h"

IMPLEMENT_SINGLE_MODEL(snapShotCtr)
snapShotCtr::snapShotCtr() {
}

snapShotCtr::~snapShotCtr() {
}


static void helper_send_role_snap_shot(void *_p){
	(static_cast<snapShotCtr *>(_p))->send_players_snap_shot();
}
void snapShotCtr::initial_snap_shot_module() {
	//initial the snap shot timer
	Facade::get_instance()->add_timer(SNAP_SHOT_SEND_INTER , helper_send_role_snap_shot , this);
}

void snapShotCtr::send_players_snap_shot() {
	std::vector<int_32> 		_map_id_arr;		//all the map ids
	gameMap*			_game_map = NULL;	//cur map
	int_32				_map_id = 0;		//cur map id
	DISPLAY_LIMIT			_display_limit;		//limit to display
	role*				_role = NULL;		//role to deal
	RECT				_rect;			//used to des limit

	std::vector<role*>		_role_arr_to_send;	//roles to send to client
	snapShotProxy			_proxy;
		

	_map_id_arr = mapUtil::get_instance()->get_map_id_arr();
	_display_limit = mapUtil::get_instance()->get_display_limit();
	
	//check every map role arr
	for(uint_32 i = 0;i < _map_id_arr.size();i++) {
		_map_id = _map_id_arr[i];
		_game_map = mapUtil::get_instance()->get_map(_map_id);
		//send the info of the roles
		uint_32			_order = 0;
		while(true) {
			//pick the role
			_role = _game_map->get_role(_order);
			if(_role == NULL) {
				break;
			}
			//clear the role arr
			_role_arr_to_send.clear();
			//create the rect for normal 
			_rect.left   =  _role->get_role_info()->get_x() - _display_limit.width / 2;
			_rect.right  =  _role->get_role_info()->get_x() + _display_limit.width / 2;
			_rect.top    =  _role->get_role_info()->get_y() - _display_limit.height / 2;
			_rect.bottom =  _role->get_role_info()->get_y() + _display_limit.height / 2;

			//correct the rect
			if(_role->get_role_info()->get_x() < (_display_limit.width) / 2) {
				_rect.left  = 0;
				_rect.right = _display_limit.width;
			}
			if(_role->get_role_info()->get_x() > (_game_map->get_width() - _display_limit.width / 2)) {
				_rect.left  = _game_map->get_width() - _display_limit.width;
				_rect.right = _game_map->get_width();
			}
			if(_role->get_role_info()->get_y() < (_display_limit.height) / 2) {
				_rect.top    = 0;
				_rect.bottom = _display_limit.height;
			}
			if(_role->get_role_info()->get_y() > (_game_map->get_height() - _display_limit.height / 2)) {
				_rect.top  = _game_map->get_height() - _display_limit.height;
				_rect.bottom = _game_map->get_height();
			}

			//get the roles you want
			uint_32			_c = 0;
			role*			_tmp_role = NULL;
			while(true) {
				_tmp_role = _game_map->get_role(_c);
				if(_tmp_role == NULL) {
					break;
				}
				if(_tmp_role->get_role_info()->get_id() == _role->get_role_info()->get_id()) {
					_c++;
					continue;
				}
				if(_tmp_role->get_role_info()->get_x() > _rect.left &&
				   _tmp_role->get_role_info()->get_x() < _rect.right&&
				   _tmp_role->get_role_info()->get_y() > _rect.top&&
				   _tmp_role->get_role_info()->get_y() < _rect.bottom) 
				{
					_role_arr_to_send.push_back(_tmp_role);
				}
				_c++;
			} 
			_proxy.send_role_snap_shot(_role->get_fd() , _role_arr_to_send);
			_order++;
		}	
	}
}
