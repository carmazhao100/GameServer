#include<iostream>
#include"proxyMsg.h"
#include"command.h"
#include"string.h"
using namespace std;

int main(){
	int_8* a = new int_8[10];
	a[0] = 0;
	a[1] = 0;
	a[2] = 0;
	a[3] = 12;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
	a[7] = 13;
	int_8 * m = new int_8[10];
	int_32 t = 11;
	memcpy(m,&t,sizeof(t));
	m += sizeof(t);
	t = 12;
	memcpy(m,&t,sizeof(t));
	m -= sizeof(t);
	
	
	proxyMsg* p = new proxyMsg(a,10,10);
	cout<<"the msg id is :"<<p->get_proxy_msg_id()<<endl;
	cout<<"the msg  is :"<<p->get_int_32()<<endl;
	
	delete p;
	
	proxyMsg* pp = new proxyMsg(a,10,10);
	delete pp;	
	/*
	command * cmd = new command(12,12);
	char * a = new char[3];
	strcpy(a,"123");
	cmd->write_str(a,3);
	cmd->write_int_32(12);
	cmd->write_int_8(97);
	strcpy(a,"abc");
	cmd->write_str(a,3);
	
	cout<<cmd->read_str()<<endl;
	cout<<cmd->read_int_32()<<endl;
	cout<<cmd->read_int_8()<<endl;
	cout<<cmd->read_str()<<endl;
*/

	return 0;
}
