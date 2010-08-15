//------------------------------------------------------------------------------------
//	coreconst.h
//
//	2010. 08. 04	CoderK	
//
//	core모드 관련 define
//------------------------------------------------------------------------------------
#pragma once
#include <windows.h>
#include "MainWin.h"

#define LOGIN_FILE_CONNECTBTN		".\\Data\\Login\\connect.img"
#define LOGIN_SIZE_CONNECTBTNW		50
#define LOGIN_SIZE_CONNECTBTNH		20
#define LOGIN_VERT_CONNECTBTN		false
#define LOGIN_POS_CONNECTBTNX		330
#define LOGIN_POS_CONNECTBTNY		360

// connect
#define LOGIN_FILE_BACK				".\\Data\\Login\\login_back.img"

// id, pw edit control
#define LOGIN_EDIT_SZLENGTH			12			// 사실 바이트 수
#define LOGIN_EDIT_IMG				".\\Data\\Login\\login_edit.img"
#define LOGIN_EDIT_ID_W				120
#define LOGIN_EDIT_ID_H				20
#define LOGIN_EDIT_ID_X				((WNDSIZEW - LOGIN_EDIT_ID_W) / 2)
#define LOGIN_EDIT_ID_Y				300
#define LOGIN_EDIT_PW_W				120
#define LOGIN_EDIT_PW_H				20
#define LOGIN_EDIT_PW_X				((WNDSIZEW - LOGIN_EDIT_ID_W) / 2)
#define LOGIN_EDIT_PW_Y				330


// ECM_BATTLENET
#define BNET_FILE_BACK				".\\Data\\BattleNet\\battlebg.img"