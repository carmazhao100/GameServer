/*------------------------------
Author: carmazhao

Date:   2011/12/19

Function: The command is used to
	  pass message to the tar-
	  get class to deal
------------------------------*/
#ifndef HEAD_ICOMMAND
#define HEAD_ICOMMAND
#include"../sys.h"
#include"../objPool.h"

#define INI_SIZE 40
#define INTERVAL 20
class command {
private:
	uint_32		m_msg_name;	//the msg id 
	int_32		m_fd;		//the handler fo socket

	int_8*		m_data;		//the data to pass
	int_8*		m_reader;	//the pos pointer
	uint_32		m_cur_size;	//cur size for the data 
	uint_32		m_limit;	//cur limit for mem space
	
	DEFINE_OBJ_POOL(command);
public:
	command (const uint_32 & _name, 
		const int_32 & _fd = 0);
	~command ();
	
//read data functions
	uint_32		get_msg_name ();
	int_32		get_fd();

	int_32		read_int_32 ();
	int_8		read_int_8 ();
	int_8*		read_str ();
//construct the struct 
	void write_int_32 (int_32 data);
	void write_int_8 (int_8 data);
	void write_str (int_8 *);
};


#endif
