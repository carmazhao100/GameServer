#include"msgIdCtr.h"

msgIdCtr * msgIdCtr::h_inst = NULL;
msgIdCtr * msgIdCtr::getInstance() {
	if(h_inst == NULL) {
		h_inst = new msgIdCtr();
	}
	return h_inst;
}
msgIdCtr::msgIdCtr() {
}

uint_32 msgIdCtr::dispatch_id() {
	uint_32		 _id = 0;
	
	for(;_id < m_id_arr.size();_id++) {
		//如果可用
		if(m_id_arr[_id]) {
			m_id_arr[_id] = false;
			return _id;
		}
	}
	m_id_arr.push_back(false);
	return _id;
}
