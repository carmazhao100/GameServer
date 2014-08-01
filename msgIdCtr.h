#pragma once
#include"core/sys.h"
#include<vector>
using namespace std;


class msgIdCtr {
private:
	static msgIdCtr * 	h_inst;
	vector<bool> 		m_id_arr;

	msgIdCtr();
public:
	static msgIdCtr * getInstance();
	uint_32 dispatch_id();
};

