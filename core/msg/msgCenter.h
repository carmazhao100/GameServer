/*------------------------------
Author: carmazhao

Date: 	2011/12/20

Function: The msgCenter is used to 
          dispatch the msg to the 
	  target mediator
--------------------------------*/
#ifndef HEAD_MSG_CENTER
#define HEAD_MSG_CENTER
#include<map>
#include"command.h"
#include"Imediator.h"
using namespace std;

typedef vector<Imediator*> mediatorArr;

class msgCenter {
private:
	map<uint_32,mediatorArr*> mapTable;
	static msgCenter* 	  h_inst;

	msgCenter();
public:
	~msgCenter();
	static msgCenter * getInstance ();
	void registerMediator (Imediator *mediator);
	void sendCommand (command* cmd);
};	

#endif
