/*================================
Author:	carmazhao

Date:	2011/12/28

Function:The mediator for role
================================*/
#ifndef HEAD_ROLE_CTR_MEDIATOR
#define HEAD_ROLE_CTR_MEDIATOR
#include"../../core/msg/Imediator.h"

class roleCtrMediator:public Imediator {
public:
	roleCtrMediator();
	~roleCtrMediator();

	void 	dispatchMsg(command * _cmd);
};
#endif
