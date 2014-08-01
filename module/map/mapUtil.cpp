#include"mapUtil.h"

IMPLEMENT_SINGLE_MODEL(mapUtil)

mapUtil::mapUtil() {
}

mapUtil::~mapUtil() {
}

gameMap* mapUtil::get_map(int_32 _map_id) {
	return mapCtr::get_instance()->get_map(_map_id);
}

std::vector<int_32> mapUtil::get_map_id_arr() {
	return mapCtr::get_instance()->get_map_id_arr();
}

DISPLAY_LIMIT	mapUtil::get_display_limit() {
	return mapCtr::get_instance()->get_display_limit();
}
