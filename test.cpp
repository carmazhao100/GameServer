#include"Facade.h"
#include"core/gsQueue.h"
#include<iostream>
using namespace std;
#define DEBUG

int main() {
/*	affair_queue * q = new affair_queue();
	int fd = 0;
	uint_32	 size = 10;
	int_8 * content = new int_8[10];
	size = htonl(size);
	memcpy(content , &size , sizeof(size));
	size = ntohl(size);

	proxyMsg* p = new proxyMsg(content , size , fd);
	q->push(p);
	proxyMsg * pp = q->pop();
	cout<<"proxy id"<<pp->get_proxy_msg_id();
	pp = q->pop();
	cout<<pp<<endl;
	
	delete q;*/

	Facade::get_instance()->initial_game_ini();
	Facade::get_instance()->initial_game_module();
	Facade::get_instance()->initial_server_socket();
	Facade::get_instance()->create_threads();
	Facade::get_instance()->game_loop();
	return 0;
}
