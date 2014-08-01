#include"msgCenter.h"

msgCenter * msgCenter::h_inst(NULL);
msgCenter * msgCenter::getInstance() {
	if(h_inst == NULL) {
		h_inst = new msgCenter();
	}
	return h_inst;
}
msgCenter::msgCenter() {
}
msgCenter::~msgCenter() {
}
void msgCenter::registerMediator (Imediator* _mediator) {
	uint_32		i = 0;
	uint_32		_msg = 0;
	mediatorArr*	_m_arr = NULL;

	if(_mediator == NULL) {
		return;
	}

	for(i = 0;i < _mediator->m_msg_arr.size();i++) {
		_msg = _mediator->m_msg_arr[i];

		if(mapTable.find(_msg) == mapTable.end()) {
			_m_arr = NULL;
			_m_arr = new mediatorArr();
			if(_m_arr == NULL) {	
				return;
			}
			_m_arr->push_back(_mediator);
			mapTable[_msg] = _m_arr;	
		}else{
			mapTable[_msg]->push_back(_mediator);
		}
	}
}
void msgCenter::sendCommand(command *_cmd) {	
	uint_32		 i = 0;
	uint_32		 _msg = _cmd->get_msg_name();
	uint_32		 _count = 0;

	if(mapTable.find(_msg) == mapTable.end()) {	
		return;
	}
	_count = (*mapTable[_msg]).size();
	
	for(; i < _count;i++) {
	        (*mapTable[_msg])[i]->dispatchMsg(_cmd);
	}
	if(_cmd != NULL) {	
		delete _cmd;
	}
}

