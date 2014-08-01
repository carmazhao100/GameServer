/*------------------------
Author:	carmazhao

Date:  	2012/2/20

Function:get the snapshot and
	send it 
-------------------------*/
#ifndef SNAP_SHOT_HEAD_
#define SNAP_SHOT_HEAD_
#include"../../core/sys.h"

#define  SNAP_SHOT_SEND_INTER 	50
class snapShotCtr {
	DEFINE_SINGLE_MODEL(snapShotCtr)
public:
	~snapShotCtr();
	enum {	
	SNAP_SHOT_KIND_PLAYER = 0,
	};
	void 		initial_snap_shot_module();
	void 		send_players_snap_shot();
private:
	snapShotCtr();
};
#endif
