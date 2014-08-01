/*-------------------------
Author: carmazhao

Date:	2011/12/20

Function:
-------------------------*/
#ifndef HEAD_GS_SOCKET
#define HEAD_GS_SOCKET

#include"sys.h"
#include"NetMsg.h"
#include<vector>

#define IO_MEM_INI	2048	//initial mem size
#define IO_MEM_INTER	50	//added interval
#define IO_LIMIT	1500	//protect our memory

class gsSocket {
private:
	//select socket fd
	int_32		m_fd;
	fd_set		m_fd_set;
	std::vector<int_32>	m_fd_cache;
	sys_h_mutex	m_cache_mutex;
	sys_h_mutex	m_write_mutex;
	
	//io mem 
	int_8*		m_io_mem;
	uint_32		m_cur_limit;
	//info cut mem
	int_8*		m_cut_mem;
	uint_32		m_cut_mem_size;
	
	gsSocket();
	
	DEFINE_SINGLE_MODEL(gsSocket)

	void 		build_and_send_msg(const int_32 &);
public:
	~gsSocket();
	void		initial_socket();
 	
	void		gs_loop();
	
	int_32		get_fd();
	void 		push_fd_cache(const int_32&);
	void		rm_fd_cache(const int_32&);
	void		send_net_msg(int_32 _fd , NetMsg * _msg);
};
#endif
