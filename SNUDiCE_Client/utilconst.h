//------------------------------------------------------------------------------------
//	utilconst.h
//
//	2010. 08. 04	CoderK	
//
//	util 관련 define
//------------------------------------------------------------------------------------
#pragma once

//	Util
#define UTIL_DEFAULT_FONT		"돋움"
#define UTIL_DEFAULT_FONTSIZE	12

//	PopUp
#define POPUP_IMG_BACK			".\\Data\\Interface\\popup.img"
#define POPUP_IMG_OK			".\\Data\\Interface\\popup_ok.img"
#define POPUP_IMG_CANCEL		".\\Data\\Interface\\popup_cancel.img"
#define POPUP_WIDTH				200
#define POPUP_HEIGHT			100
#define POPUP_X					((WNDSIZEW - POPUP_WIDTH) / 2)
#define POPUP_Y					((WNDSIZEH - POPUP_HEIGHT) / 2)
#define POPUP_BTNW				50
#define POPUP_BTNH				20
#define POPUP_ONEBTNX			(POPUP_X + (POPUP_WIDTH - POPUP_BTNW) / 2)
#define POPUP_ONEBTNY			(POPUP_Y + 70)
#define POPUP_1STBTNX			(POPUP_X + 40)
#define POPUP_1STBTNY			POPUP_ONEBTNY
#define POPUP_2NDBTNX			(POPUP_X + 110)
#define POPUP_2NDBTNY			POPUP_ONEBTNY
#define POPUP_1STTEXTY			(POPUP_Y + 28)
#define POPUP_2NDTEXTY			(POPUP_Y + 48)
#define POPUP_IMG_W				48			// popup창에 띄우는 이미지
#define POPUP_IMG_H				48
#define POPUP_IMG_X				(POPUP_X + 10)
#define POPUP_IMG_Y				(POPUP_Y + 10)
#define POPUP_PIXEL_PER_LETTER	6