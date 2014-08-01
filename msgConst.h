#ifndef HEAD_MSG_CONST
#define HEAD_MSG_CONST
#include"core/sys.h"
class msgConst {
public:
//--------------login info
	static const uint_32		CLIENT_LOGIN = 0;
	static const uint_32		HEART_BEAT_FROM_CLIENT = 1;
//--------------role move state
	static const uint_32		ROLE_MOVE_STATE_CHANGE = 2;
//--------------map role add info
	static const uint_32		ROLE_ADD_TO_MAP = 3;
	static const uint_32		ROLE_REMOVE_FROM_MAP = 4;
};
#endif
