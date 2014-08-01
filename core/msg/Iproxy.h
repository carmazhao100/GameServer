/*-----------------------------
Author: carmazhao

Date:	2011/12/20

Function:The Iproxy is the Interface
         for proxys used to pass
	 the net information
-----------------------------*/
#ifndef HEAD_IPROXY
#define HEAD_IPROXY

#include"proxyMsg.h"
#include<vector>

class Iproxy {
public:
	std::vector<uint_32>	m_msg_arr;			// store the net message id to listen
	virtual void 		dispatchMsg(proxyMsg *msg) = 0; 
};
#endif
