#include"NetMsg.h"
#include<string.h>

IMPLEMENT_OBJ_POOL(NetMsg)
NetMsg::NetMsg(){
	if (m_data == NULL)
	{
		m_data = new int_8[INI_LENGTH];
	}
	m_cur = m_data;
	m_limit = INI_LENGTH;
	m_data_size = 0;
}
NetMsg::~NetMsg(){
}

int_32	NetMsg::get_data_size() {
	return m_data_size;
}
int_8*	NetMsg::get_data() {
	return m_data;
}


void NetMsg::write_int_32(int_32  _data) {
	int_32			_needed_size = 0;

	_data = htonl(_data);
	if (NULL == m_data)
	{
			return;
	}
	_needed_size = m_data_size + sizeof(_data);

	if(_needed_size > m_limit) {
		expand_mem();
	}
	memcpy(m_cur , &_data , sizeof(_data));
	m_cur += sizeof(_data);
	m_data_size += sizeof(_data);
}


void NetMsg::write_int_8(int_8 _data) {
	int_32			_needed_size = 0;

	if (NULL == m_data)
	{
		return;
	}
	_needed_size = m_data_size + sizeof(_data);

	if(_needed_size > m_limit) {
		expand_mem();
	}
	memcpy(m_cur , &_data , sizeof(_data));
	m_cur += sizeof(_data);
	m_data_size += sizeof(_data);
}

void NetMsg::write_str(int_8* _str) {
	int_32			_needed_size = 0;
	uint_32			_size = strlen(_str);
 
	_needed_size = m_data_size;
	_needed_size += _size;
	_needed_size += sizeof(_size);

	if (NULL == m_data)
	{
		return;
	}

	if(_needed_size > m_limit) {
		expand_mem();
	}
//change to net size
	_size = htonl(_size);
	memcpy(m_cur , &_size, sizeof(_size));
	m_cur += sizeof(_size);
//change to host size
	_size = ntohl(_size);
	
	memcpy(m_cur , _str, _size);
	m_cur += _size;

	m_data_size += sizeof(_size);
	m_data_size += _size;
}
 
void NetMsg::expand_mem() {
	int_8*			_temp = NULL;
	
	m_limit = m_limit + INTER;
	_temp = new int_8[m_limit];
	memcpy(_temp , m_data , m_data_size);
	delete m_data;
	m_data = _temp;
	m_cur = m_data + m_data_size;
}
