#ifndef HEAD_PROXY_MSG
#define HEAD_PROXY_MSG
#include"../sys.h"
#include"../objPool.h"
class proxyMsg {
private:
	uint_32 	m_id;		//info id
	int_8 *		m_content;	//pointer to the content
	int_32 		m_fd;		//act socket fd

	DEFINE_OBJ_POOL(proxyMsg);	//define the object pool
	
	uint_32		m_size;		//content size
	int_8 *		m_cur_pos;	//current reading pos
	
public:
	proxyMsg(int_8* _content , uint_32 _size , int_32 _fd);
	~proxyMsg();

	uint_32    	get_proxy_msg_id();
	int_32		get_fd();
	
	int_32     	get_int_32();	   
	int_8	  	get_int_8();
	int_8*		get_string();
};
#endif
