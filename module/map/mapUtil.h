/*=============================
Author: carmazhao

Date:	2012/2/24

Function:the util of the map module
=============================*/
#ifndef MAP_UTIL_HEAD_
#define MAP_UTIL_HEAD_
#include"mapCtr.h"

class mapUtil {
	DEFINE_SINGLE_MODEL(mapUtil)
public:
	~mapUtil();
	enum {	
	MOVE_SPEED = 5
	};
	
	gameMap*	    get_map(int_32  _map_id);
	std::vector<int_32> get_map_id_arr();
	DISPLAY_LIMIT	    get_display_limit();
private:
	mapUtil();
};
#endif
