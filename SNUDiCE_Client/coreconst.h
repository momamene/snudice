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

// ECM_LOGIN.		login모드인데 바꾸기 구찮아서 걍 title_xx... 로 놔둠
#define TITLE_FILE_BACK			".\\Data\\Title\\title.img"

// start
// #define TITLE_FILE_STARTBTN		".\\Data\\Title\\tstart.img"
// #define TITLE_SIZE_STARTBTNW	62
// #define TITLE_SIZE_STARTBTNH	20
// #define TITLE_VERT_STARTBTN		false
// #define TITLE_POS_STARTBTNX		40
// #define TITLE_POS_STARTBTNY		350

// exit
// #define TITLE_FILE_EXITBTN		".\\Data\\Title\\texit.img"
// #define TITLE_SIZE_EXITBTNW		62
// #define TITLE_SIZE_EXITBTNH		20
// #define TITLE_VERT_EXITBTN		false
// #define TITLE_POS_EXITBTNX		40
// #define TITLE_POS_EXITBTNY		380

#define LOGIN_FILE_CONNECTBTN		".\\Data\\Login\\connect.img"
#define LOGIN_SIZE_CONNECTBTNW		50
#define LOGIN_SIZE_CONNECTBTNH		20
#define LOGIN_VERT_CONNECTBTN		false
#define LOGIN_POS_CONNECTBTNX		330
#define LOGIN_POS_CONNECTBTNY		360

// connect

// id, pw edit control
#define LOGIN_EDIT_SZLENGTH			12			// 사실 바이트 수
#define LOGIN_EDIT_IMG				".\\Data\\Title\\login_edit.img"
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