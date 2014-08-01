#include"Facade.h"
#include"core/gsSocket.h"
#include"core/gsThread.h"
#include"core/gsTimer.h"
#include"core/msg/proxyCenter.h"
#include"core/msg/msgCenter.h"
#include"core/gsSQL.h"
//================modules================
#include"module/player/roleCtrMediator.h"
#include"module/player/roleCtrProxy.h"
//map
#include"module/map/mapCtrMediator.h"
#include"module/map/mapCtrProxy.h"
#include"module/map/mapCtr.h"
//snap shot
#include"module/snapShot/snapShotCtr.h"
#include"module/snapShot/snapShotProxy.h"


IMPLEMENT_SINGLE_MODEL(Facade)

Facade::Facade() {
}
Facade::~Facade() {
}
void Facade::initial_game_ini() {
	mapCtr::get_instance()->initial_map_info();	
	snapShotCtr::get_instance()->initial_snap_shot_module();
}
void Facade::initial_game_module() {
	//login module
	roleCtrProxy * _role_ctr_proxy= new roleCtrProxy();
	roleCtrMediator * _role_ctr_mediator= new roleCtrMediator();
	
	this->register_proxy(_role_ctr_proxy);
	this->register_mediator(_role_ctr_mediator);
	//map module
	mapCtrMediator* _map_ctr_mediator = new mapCtrMediator();
	mapCtrProxy*	_map_ctr_proxy	  = new mapCtrProxy();
	
	this->register_proxy(_map_ctr_proxy);
	this->register_mediator(_map_ctr_mediator);
	//snapshot
	snapShotProxy*	_snap_shot_proxy = new snapShotProxy();

	this->register_proxy(_snap_shot_proxy);
}
/*****************G A M E  S O C K E T*****************/
void Facade::initial_server_socket() {
	gsSocket::get_instance()->initial_socket();
}

void Facade::remove_fd(const int_32 & _fd) {
	gsSocket::get_instance()->rm_fd_cache(_fd);
}

void Facade::send_net_msg(const int_32 & _fd,
			  NetMsg* _msg) 
{
	gsSocket::get_instance()->send_net_msg(_fd , _msg);
}
/******************T H R E A D*****************/
void Facade::create_threads() {
	uint_32		i = 0;

	for(;i < AFFAIR_THREAD_NUM;i++) {
		gsThread::get_instance()->create_affair_thread();
	}

//	gsThread::get_instance()->create_db_thread();
	gsThread::get_instance()->create_accept_thread();
	gsThread::get_instance()->create_guard_thread();
	//time counting thread
	gsTimer::get_instance()->init_time_manager();
}

void Facade::game_loop() {
	printf("begin to loop\n");
	gsSocket::get_instance()->gs_loop();
}
/************T I M E R*************/
void Facade::add_timer(const uint_32 & _inter , handle_func _handler , void * _param) {
	gsTimer::get_instance()->add_timer_event(_inter , _handler , _param);
}

void Facade::remove_timer(handle_func _handler) {
	gsTimer::get_instance()->remove_timer_event( _handler);
}

void Facade::remove_timer_unit(embed_handleUnit _unit){
	gsTimer::get_instance()->remove_timer_unit(_unit);
}
/***********M S G****************/
void Facade::send_proxy_msg(proxyMsg * _p_msg) {
	proxyCenter::getInstance()->send_proxy_msg(_p_msg);
}

void Facade::register_proxy(Iproxy * _proxy) {
	proxyCenter::getInstance()->registerProxy(_proxy);
}

void Facade::send_command_msg(command * _cmd) {
	msgCenter::getInstance()->sendCommand(_cmd);
}

void Facade::register_mediator(Imediator * _mediator) {
	msgCenter::getInstance()->registerMediator(_mediator);
}

/*****************D  B********************/
bool Facade::execute_set(int_8 * _sql) {
	return gsSQL::get_instance()->execute_set(_sql);
}

MYSQL_RES* Facade::execute_get(int_8 * _sql) {
	return gsSQL::get_instance()->execute_get(_sql);
}
