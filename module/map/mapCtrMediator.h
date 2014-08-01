/***********************************
Author: carmazhao

Date:  2012/2/24

Functions: the mediator of map
**********************************/
#ifndef MAP_CTR_MEDIATOR_HEAD_
#define MAP_CTR_MEDIATOR_HEAD_
#include"../../core/msg/Imediator.h"

class mapCtrMediator:public Imediator {
public:
	mapCtrMediator();
	~mapCtrMediator();
	
	void 	dispatchMsg(command * _cmd);
};
#endif
