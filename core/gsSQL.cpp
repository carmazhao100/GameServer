#include"gsSQL.h"

IMPLEMENT_SINGLE_MODEL(gsSQL)

conn_pool::conn_pool() {
		m_conn = new MYSQL();
		mysql_init(m_conn);
		mysql_real_connect(m_conn , "localhost" , "root" , "xinzheng1218"
				 , "game" , 0 , NULL , 0);
}

conn_pool::~conn_pool() {
}

MYSQL * conn_pool::get_conn() {
		mysql_init(m_conn);
		mysql_real_connect(m_conn , "localhost" , "root" , "xinzheng1218"
				 , "game" , 0 , NULL , 0);
	/*MYSQL * p_t = NULL;
	if(m_pool.empty()) {
		p_t = new MYSQL();
		mysql_init(p_t);
		mysql_real_connect(p_t , "localhost" , "root" , "xinzheng1218"
				 , "game" , 0 , NULL , 0);
	}else {
		sys_mutex_lock(m_mutex);
		p_t = m_pool.front();
		m_pool.pop();
		sys_mutex_unlock(m_mutex);
	}
	if(p_t == NULL) {
		printf("db get conenctin Error!\n");
	}
	return p_t;*/
	return m_conn;
}

void	conn_pool::release_conn(MYSQL * _conn) {
		//sys_mutex_lock(m_mutex);
	//	m_pool.push(_conn);
//		sys_mutex_unlock(m_mutex);
}

/*
	GS _ SQL
*/
gsSQL::gsSQL() {
}

gsSQL::~gsSQL() {
}

MYSQL_RES*  gsSQL::execute_get(int_8 * _sql) {
	int_32		_result = 0;
	MYSQL_RES*	_res = NULL;
	MYSQL * 	_conn = NULL;

	_conn = m_conn_pool.get_conn();
	
	if(NULL == _sql) {
		return NULL;
	}

	if(NULL == _conn) {
		return NULL;
	}

	_result = mysql_query(_conn , _sql);
	if(_result) {
		m_conn_pool.release_conn(_conn);	
		return NULL;
	}
	_res = mysql_use_result(_conn);
	if(NULL == _res) {
		m_conn_pool.release_conn(_conn);	
		return NULL;
	}
	m_conn_pool.release_conn(_conn);	
	return _res;
}

bool 	 gsSQL::execute_set(int_8 * _sql) {
	int_32		_result = 0;
	MYSQL * 	_conn = NULL;
	
	if(NULL == _sql) {
		return false;
	}

	_conn = m_conn_pool.get_conn();
	if(NULL == _conn) {
		return false;
	}

	_result = mysql_query(_conn , _sql);
	if(_result) {
		m_conn_pool.release_conn(_conn);	
		return false;
	}
	m_conn_pool.release_conn(_conn);	
	return true;
}
