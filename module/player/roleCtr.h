/*----------------------------
Author:	carmazhao

Date:	2011/12/27

Function: control the role list
----------------------------*/
#ifndef	HEAD_ROLE_CTR
#define HEAD_ROLE_CTR
#include"role.h"
#include"../../core/sys.h"
#include<vector>

class roleCtr {
	DEFINE_SINGLE_MODEL(roleCtr)
private:
	std::vector<role *>	m_role_list;
	sys_h_mutex		m_list_mutex;

	//sql for validating
	int_8			m_sql[MAX_SQL_LENGTH];

	roleCtr();
public:
	~roleCtr();
	
	//	get the heart beat msg and dispatch it
	void 		heart_beat_dispatch(const int_32 & _fd);
	void 		beat_to_client(int_32 _fd);
	//	deal the user login
	bool 		validate_login(int_8* _acc , int_8* _psw);
	void		add_login_client(int_8* _acc , int_32 _fd);
	void 		send_login_ok(const int_32 & _fd);
	void 		remove_client(const int_32 & _fd);
	//	deal role intial
	void 		send_role_info_to_client(role * _role);
	//deal role moving
	void 		change_role_move_state(const int_32 & _state , 
					       const int_32 & _fd);
	void 		change_role_pos(const int_32 & _fd ,
					const int_32 & _x,
					const int_32 & _y);
	//	get functions
	role * 		get_role_by_id(const int_32 & _id);
	role* 		get_role_by_fd(const int_32 & _fd);
};

#endif
