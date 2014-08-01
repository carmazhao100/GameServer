#include"command.h"
#include<string.h>

IMPLEMENT_OBJ_POOL(command)

command::command (const uint_32 & _name, const int_32 & _fd) {
	m_msg_name = _name;
	m_fd = _fd;

	//first check the space
	if(NULL == m_data) {
		m_data = new int_8[INI_SIZE];
		m_limit = INI_SIZE;
	}
	m_cur_size = 0;
	m_reader = m_data;
}
command::~command() {
}

//read data functions
uint_32 command::get_msg_name() {
	return m_msg_name;
}
int_32	command::get_fd() {
	return m_fd;
}

int_32 command::read_int_32() {
	int_32 		_data = 0;

	if(m_data !=  NULL) {	
		memcpy(&_data,m_reader,sizeof(_data));
		m_reader += sizeof(_data);
		return _data;
	}	
	return 0;
}

int_8 command::read_int_8() {
	int_8 		_data = 0;

	if(m_data !=  NULL) {	
		memcpy(&_data,m_reader,sizeof(_data));
		m_reader += sizeof(_data);
		return _data;
	}	
	return 0;
}

int_8* command::read_str() {
	int_8 * 	_data; 
	uint_32		_size = 0;

	if(m_data != NULL) {
		//get the length of str
		memcpy(&_size,m_reader,sizeof(_size));
		_data = new char[_size + 1];
		m_reader += sizeof(_size);
		//get the str
		memcpy(_data,m_reader,_size);
		m_reader += _size;
		_data[_size] = '\0';
		return _data;
	}
	return 0;
}


//---------the functions to write data

void command::write_int_32 (int_32 _data) {	
	uint_32		_size = sizeof(_data);
	int_8*		_cur_pos  = NULL;
	int_8*		_tmp_buf = NULL;

	if((m_cur_size + _size) > m_limit) {
		_tmp_buf = new int_8[m_limit + INTERVAL];
		memcpy(_tmp_buf,m_data,m_cur_size);
		delete m_data;
		m_data = _tmp_buf;
		m_limit = m_limit + INTERVAL;
	}
	_cur_pos = m_data + m_cur_size;
	memcpy(_cur_pos,&_data,_size);
	m_cur_size += _size;
}
void command::write_int_8 (int_8 _data) {	
	uint_32 	_size = sizeof(_data);
	int_8*		_cur_pos  = NULL;
	int_8*		_tmp_buf = NULL;

	if((m_cur_size + _size) > m_limit) {
		_tmp_buf = new int_8[m_limit + INTERVAL];
		memcpy(_tmp_buf,m_data,m_cur_size);
		delete m_data;
		m_data = _tmp_buf;
		m_limit = m_limit + INTERVAL;
	}
	_cur_pos = m_data + m_cur_size;
	memcpy(_cur_pos , &_data , _size);
	m_cur_size += _size;
}
void command::write_str (int_8 * _data) {
	int_8*		_tmp_buf = NULL;
	int_8*		_cur_pos  = NULL;
	int_32		_size = strlen(_data);

	//need the length of the string
	if((m_cur_size + _size+sizeof(_size)) > m_limit) {
		_tmp_buf = new int_8[m_limit + INTERVAL];
		memcpy(_tmp_buf,m_data,m_cur_size);
		delete m_data;
		m_data = _tmp_buf;
		m_limit = m_limit + INTERVAL;
	}
	//copy the size of str
	_cur_pos = m_data + m_cur_size;
	memcpy(_cur_pos,&_size,sizeof(_size));
	//copy the str
	_cur_pos += sizeof(_size);
	memcpy(_cur_pos,_data,_size);

	m_cur_size += _size;
	m_cur_size += sizeof(_size);
}
