/*******************************
Author:	carmazhao

Date:	2012/1/12

Function: construct the msg to 
	send to client
******************************/
#ifndef GS_NET_MSG_HEAD_
#define GS_NET_MSG_HEAD_
#include"sys.h"
#include"objPool.h"

#define INI_LENGTH 56
#define INTER      32
class NetMsg {
public:
	NetMsg();
	~NetMsg();

	void		write_int_32(int_32);
	void		write_int_8(int_8 );
	void		write_str(int_8*);

	int_32		get_data_size();
	int_8*		get_data();
private:
	int_32		m_limit;
	int_32		m_data_size;
	int_8*		m_cur;
	int_8*		m_data;

	void		expand_mem();
	DEFINE_OBJ_POOL(NetMsg)
};
#endif


