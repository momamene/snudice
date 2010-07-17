//------------------------------------------------------------------------------------
//	const.h
//------------------------------------------------------------------------------------
#pragma once
#define BIT			32
#define	WNDSIZEW	640
#define WNDSIZEH	480
#define GAMENAME	"SNU Dice"
#define WNDSTYLE	(WS_CAPTION | WS_SYSMENU)

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

//	Title
#define TITLE_IMG_TITLE		"title.img"
//	start button
#define TBT_START_IMG		"tstart.img"
#define TBT_START_SIZEW		62			// start button 가로
#define TBT_START_SIZEH		20			// start button 세로
#define TBT_START_VERTICAL	false		// 가로로 3개
#define TBT_START_X			40			// 시작 x
#define TBT_START_Y			350			// 시작 y
//	exit button
#define TBT_EXIT_IMG		"texit.img"
#define TBT_EXIT_SIZEW		62			// EXIT button 가로
#define TBT_EXIT_SIZEH		20			// EXIT button 세로
#define TBT_EXIT_VERTICAL	false		// 가로로 3개
#define TBT_EXIT_X			40			// 시작 x
#define TBT_EXIT_Y			380			// 시작 y



