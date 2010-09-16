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
#include "networkconst.h"

enum ROOMMODE
{
	ERM_MAKE,
	ERM_JOIN,
	ERM_ROOM,
	ERM_END,
};

enum BTNMAKEMODE
{
	BMM_OK,
	BMM_CANCEL,
	BMM_END,
};

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

	void		pk_roommake_rep(PK_ROOMMAKER_REP *rep);

private:
	bool		SetUp_Make();
	void		MainLoop_Make();
	void		Draw_Make();
	void		OnLButtonDown_Make();
	void		OnLButtonUp_Make();
	void		OnMouseMove_Make();
	void		Cancel_Make();
	void		SendRoomMake();

	bool		SetUp_Join();
	void		MainLoop_Join();
	void		Draw_Join();

	bool		SetUp_Room();
	void		MainLoop_Room();
	void		Draw_Room();

};
