/*---------------------------------------------
Author: 	carmazhao

Date:		2011/12/26

Function:	1.the role_info class is used to 
		store the attributes for a role

		2.the heart_beater class is used
		to control heart beating.
=============================================*/

#ifndef HEAD_ROLE
#define HEAD_ROLE

#include"../../core/sys.h"
#include"../../core/objPool.h"
#define HEART_BEAT_LIMIT	5	//the client must beat at least once in every HEART_BEAT_LIMIT seconds

//define the attribute IN MYSQL
#define DB_ROLE_ID		0
#define DB_ROLE_NAME		2
#define DB_ROLE_AN_TYPE		3
#define DB_ROLE_HP		4
#define DB_ROLE_MAP_ID		5
#define DB_ROLE_X		6
#define DB_ROLE_Y		7

//define the used nums
#define MAX_ROLE_NAME		40

class role;
class role_info {
	DEFINE_OBJ_POOL(role_info)
private:
	uint_32		m_id;			// id of a role
	int_8		m_name[MAX_ROLE_NAME];	// name of a role
	int_32		m_hp;			// hp of a role
	int_32	 	m_map_id;		// current map id
	int_32		m_x;			// current x
	int_32		m_y;			// current y
	int_32		m_mov_state;		// current moving state
	int_32		m_animation_type;	// the type of animation
	
public:
	role_info (const uint_32 & 	_id,
		int_8*			_name,
		const int_32 &		_an_type,
		const int_32 &		_hp,
		const int_32 & 		_map_id,
		const int_32 & 		_x,
		const int_32 & 		_y);
	~role_info ();
	friend class role;
//======MOVE STATE====
	enum {
		MOVE_UP = 0,
		MOVE_DOWN ,
		MOVE_LEFT ,
		MOVE_RIGHT ,
		STATIC_UP ,
		STATIC_DOWN ,
		STATIC_LEFT ,
		STATIC_RIGHT
	};

//===============GET FUNCTIONS
	uint_32		get_id();
	int_8*		get_name();
	int_32		get_hp();
	
	int_32		get_map_id();
	int_32		get_x();
	int_32		get_y();
	int_32		get_mov_state();
	int_32		get_animation_type();
//===============GET FUNCTIONS
	void 		set_id(const int_32 & _id);
	void 		set_name(int_8* _name);
	void 		set_hp(const int_32 & _hp);

	void 		set_map_id(const int_32 & _map_id);
	void 		set_x(const int_32 & _x);
	void 		set_y(const int_32 & _y);
	void 		set_mov_state(const int_32 & _state);
	void 		set_animation_type(const int_32 & _type);
//==============FUNCTION
	void 		do_move();
};

class heart_beater {
private:
	int_32		m_cur_time;
	int_32		m_fd;
public:
	heart_beater();
	~heart_beater();

	void 		run();
	void 		stop();
	void 		beat (int_32	_fd);
	void		check ();
	void 		set_fd(const int_32 &);
};

class role {
	DEFINE_OBJ_POOL(role)
private:
	role_info * 	m_role_info;
	heart_beater 	m_hbeater;
	int_32		m_fd;
	
	//mem for sql
	int_8	 	m_sql[MAX_SQL_LENGTH];
public:
	role (int_32	_fd ,
	     int_8 *	_account);
	~role();

	void		write_back_data();

//****************role function s*********************
	void 		heart_beat();
//*****************get function***********************
	int_32		get_fd();
	role_info*	get_role_info();
};
#endif
