#include"proxyCenter.h"
proxyCenter::proxyCenter() {
}
proxyCenter::~proxyCenter() {
}
proxyCenter* proxyCenter::h_inst(NULL);
proxyCenter* proxyCenter::getInstance() {
	if(h_inst == NULL) {
		h_inst = new proxyCenter();
	}
	return h_inst;
}

void proxyCenter::registerProxy(Iproxy * _proxy){
	uint_32		i = 0;
	uint_32		_id;
	
	for(;i < _proxy->m_msg_arr.size(); i++) {
		_id = _proxy->m_msg_arr[i];
		if(m_proxy_table.find(_id) == m_proxy_table.end()) {
			m_proxy_table[_id] = _proxy;
		}else{
		}
	}
}
void proxyCenter::send_proxy_msg(proxyMsg* _msg) {
	uint_32		_id = _msg->get_proxy_msg_id();
	
	if(m_proxy_table.find(_id) == m_proxy_table.end()) {
		return;
	}
	m_proxy_table[_id]->dispatchMsg(_msg);
}
