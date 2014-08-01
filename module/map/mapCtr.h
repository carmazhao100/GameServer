/*==============================
Author : carmazhao

Date:	 2012/2/23

Function:ctr of map roles
===============================*/
#ifndef MAP_CTR_HEAD_
#define MAP_CTR_HEAD_
#include"../../core/sys.h"
#include"../player/role.h"
#include<map>
#include<vector>

//define the struct to discribe the screen

class gameMap {
public:
	gameMap();
	~gameMap();

	void		set_width(const int_32 	& _width);
	void 		set_height(const int_32	& _height);
	int_32		get_width();
	int_32		get_height();
	
	void 		add_role(role* _role);
	void 		remove_role(role* _role);
	role*		get_role(const uint_32 & _order);
private:
	std::vector<role*>	m_role_arr;
	int_32			m_width;
	int_32			m_height;
	sys_h_mutex		m_arr_mutex;
};

struct DISPLAY_LIMIT {
	int_32		width;
	int_32		height;
};
class mapCtr {
	DEFINE_SINGLE_MODEL(mapCtr)
private:
	mapCtr();
	std::map<int_32 , gameMap*> 		m_map_table;
	std::vector<int_32>			m_map_id_arr;
	DISPLAY_LIMIT	 			m_dis_limit;
public:
	~mapCtr();
	enum {
		TEST_MAP = 26
	};
		//about initial role
	void 			initial_map_info();
		//about role 
	void 			add_role_2_map(int_32 _map_id , role* _role);
	void 			remove_role_from_map(int_32 _map_id , role* _role);
	gameMap*		get_map(int_32 _map_id);
	std::vector<int_32>	get_map_id_arr();
		//about display
	DISPLAY_LIMIT		get_display_limit();
};
#endif
