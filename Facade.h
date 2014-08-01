/*------------------------------------
Author: carmazhao

Date: 	2011/12/22

Function:this is an interface for the
	 core classes
------------------------------------*/
#ifndef HEAD_FACADE
#define HEAD_FACADE
#include"core/sys.h"
#include"core/gsSQL.h"
#include"core/msg/proxyMsg.h"
#include"core/msg/command.h"
#include"core/msg/Iproxy.h"
#include"core/msg/Imediator.h"
#include"core/gsTimer.h"
#include"core/NetMsg.h"

class Facade {	
	DEFINE_SINGLE_MODEL(Facade)
private:
	Facade();
public:
	~Facade();
	//initial game module
	void 	initial_game_ini();
	void 	initial_game_module();
	//socket class
	void 	initial_server_socket();
	void 	game_loop();
	void 	remove_fd(const int_32 & _fd);
	void 	send_net_msg(const int_32 & _fd , NetMsg* _msg);
	//thread
	void	create_threads();
	
	//timer
	void 	add_timer(const uint_32 & _t , handle_func _handle , void * _param = NULL);
	void 	remove_timer(handle_func _handle);
	void 	remove_timer_unit(embed_handleUnit  _unit);
	
	//msg
	void 	send_proxy_msg(proxyMsg *);
	void 	send_command_msg(command *);
	void 	register_proxy(Iproxy *);
	void 	register_mediator(Imediator *);
	
	//db
	bool	execute_set(int_8 *);
	MYSQL_RES * execute_get(int_8 *);
};
#endif
