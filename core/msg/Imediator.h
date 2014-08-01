/*-------------------------------
Author: carmazhao

Date:   2011/12/20

Function:The mediator class is used
	 to deal with the passed in
	 message of a module
-------------------------------*/
#ifndef HEAD_IMEDIATOR
#define HEAD_IMEDIATOR

#include<vector>
#include"command.h"

class Imediator {
public:
	std::vector<uint_32> 	m_msg_arr;

	virtual void dispatchMsg(command *_cmd)=0;
};
#endif
