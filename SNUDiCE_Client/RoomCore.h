//------------------------------------------------------------------------------------
//	gRoomCore Class
//
//	2010. 08. 28	CoderK
//
//	�游���, �� �����ϱ�, �濡�� ���� ������
//	ECM_ROOMMAKE, ECM_ROOMJOIN, ECM_ROOM
//------------------------------------------------------------------------------------
#pragma once
#include "Core.h"
#include "Image.h"
#include "Edit.h"
#include "coreconst.h"
#include <windows.h>

#define ROOM_FILE_BACK				".\\Data\\Room\\room_back.img"

class gRoomCore : Core
{
public:
	static gRoomCore	*GetIF();

	gRoomCore();
	virtual ~gRoomCore();

public:
	gImage		m_ImgBack;
	gEdit		m_EditRoom;
	gEdit		m_EditPass;

public:
	// overridng from Core �������̽�
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();

	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
	// end overridng

	bool		PreTransMsg(MSG &msg);

	void		SendRoomMake();

	void		pk_roommake_rep(PK_ROOMMAKER_REP *rep);
};
