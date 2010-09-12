//------------------------------------------------------------------------------------
//	gRoomCore Class
//
//	2010. 08. 28	CoderK
//
//	방만들기, 방 접속하기, 방에서 게임 전까지
//	ECM_ROOMMAKE, ECM_ROOMJOIN, ECM_ROOM
//------------------------------------------------------------------------------------
#pragma once
#include "Core.h"
#include "Image.h"
#include "ImgButton.h"
#include "Edit.h"
#include "coreconst.h"
#include <windows.h>

enum ROOMMODE
{
	ERM_MAKE,

	ERM_END,

	ERM_JOIN,
	ERM_WAITING,
};

enum BTNMAKEMODE
{
	BMM_OK,
	BMM_CANCEL,
	BMM_END,
};

#define ROOM_FILE_BACK				".\\Data\\Room\\room_back.img"

// make
#define	ROOM_FILE_MAKE_BACK			".\\Data\\Room\\make_back.img" 
#define ROOM_POS_MAKE_X				0
#define ROOM_POS_MAKE_Y				60

#define ROOM_FILE_BTN_OK			".\\Data\\Room\\make_btn_ok.img"
#define ROOM_BTN_SIZE_OK_W			99
#define	ROOM_BTN_SIZE_OK_H			40
#define ROOM_BTN_POS_OK_X			322
#define ROOM_BTN_POS_OK_Y			410

#define ROOM_FILE_BTN_CANCEL		".\\Data\\Room\\make_btn_cancel.img"
#define ROOM_BTN_SIZE_CANCEL_W		99
#define	ROOM_BTN_SIZE_CANCEL_H		40
#define ROOM_BTN_POS_CANCEL_X		475
#define ROOM_BTN_POS_CANCEL_Y		410

#define ROOM_EDIT_LEN_ID			26
#define ROOM_EDIT_SIZE_ID_W			190
#define ROOM_EDIT_SIZE_ID_H			15
#define ROOM_EDIT_POS_ID_X			33
#define ROOM_EDIT_POS_ID_Y			167

#define ROOM_EDIT_LEN_PW			16
#define ROOM_EDIT_SIZE_PW_W			110
#define ROOM_EDIT_SIZE_PW_H			15
#define ROOM_EDIT_POS_PW_X			98
#define ROOM_EDIT_POS_PW_Y			388


class gRoomCore : Core
{
public:
	static gRoomCore	*GetIF();

	gRoomCore();
	virtual ~gRoomCore();

public:
	ROOMMODE	m_eRoom;

	gImage		m_ImgBack[ERM_END];

	// make
	gImgButton	m_MakeBtn[BMM_END];


	gEdit		m_EditRoom;
	gEdit		m_EditPass;

public:
	// overridng from Core 인터페이스
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();

	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
	// end overridng

	void		Clear_Make();

	bool		PreTransMsg(MSG &msg);

	void		SendRoomMake();

	void		pk_roommake_rep(PK_ROOMMAKER_REP *rep);

private:
	bool		SetUp_Make();
	void		MainLoop_Make();
	void		Draw_Make();
	void		OnLButtonDown_Make();
	void		OnLButtonUp_Make();
	void		OnMouseMove_Make();
};
