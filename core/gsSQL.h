/*----------------------------------
Author: carmazhao

Date:	2011/12/25

Function: keep the connection pool
	and execute the sql
----------------------------------*/

#ifndef HEAD_GSSQL
#define HEAD_GSSQL
#include"sys.h"
#include"mysql/mysql.h"

#include<queue>

class conn_pool {
private:
	//std::queue<MYSQL *> 		m_pool;
	MYSQL*				m_conn;
	sys_h_mutex			m_mutex;
public:
	conn_pool();
	~conn_pool();
		
	MYSQL * get_conn();
	void 	release_conn(MYSQL *);
};


class gsSQL {
	DEFINE_SINGLE_MODEL(gsSQL)
private:
	conn_pool		m_conn_pool;
	
	gsSQL();
public:
	~gsSQL();

	MYSQL_RES*   execute_get(int_8 * _sql);
	bool	     execute_set(int_8 * _sql);
};
	
#endif 
