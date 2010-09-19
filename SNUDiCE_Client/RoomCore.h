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

	BMM_LIST,		//	게임 인원 리스트 버튼
	BMM_NUM2,
	BMM_NUM3,
	BMM_NUM4,
	BMM_NUM5,
	BMM_NUM6,
	BMM_NUM7,
	BMM_NUM8,

	BMM_END,
};

enum BTNJOINMODE
{
	BJM_ROOM1,
	BJM_ROOM2,
	BJM_ROOM3,
	BJM_ROOM4,
	BJM_ROOM5,
	BJM_ROOM6,
	BJM_ROOM7,
	BJM_ROOM8,

	BJM_PREV,
	BJM_NEXT,

	BJM_JOIN,

	BJM_PASS,
	
	BJM_END,
};

enum BTNWAITMODE
{
	BWM_READY,
	BWM_START,

	BWM_END,
};

enum BTNSELMODE
{
	BSM_LITERAL,		// 인문
	BSM_SOCIAL,			// 사회
	BSM_MANAGE,			// 경영
	BSM_LAW,			// 법
	BSM_LIFE,			// 생활과학
	BSM_TEACH,			// 사범대
	BSM_FREE,			// 자유전공

	// 수리
	BSM_ENGINE,			// 공
	BSM_NATURE,			// 자연
	BSM_DOCTOR,			// 의사
	BSM_ANIMAL,			// 수의사
	BSM_DRUG,			// 약
	BSM_NURSE,			// 간호
	BSM_FARM,			// 농

	// 예술
	BSM_MUSIC,			// 음
	BSM_ART,			// 미

	BSM_SELECT,

	BSM_END,
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
	gImage		m_ImgNum;
	gImage		m_ImgPass;
	int			m_nPlayer;				// 몇명이 하냐
	bool		m_bIsPull;				// 게임인원 리스트 박스 열려있냐
	gEdit		m_EditRoom;
	gEdit		m_EditPass;

	// join
	gImage		m_ImgRoomName;
	gImgButton	m_JoinBtn[BJM_END];
	int			m_nSelected;
	int			m_nPage;
	ROOM		m_Room[MAXROOMFORPAGE];
	bool		m_bEnteringPass;		// 패스워드 입력모드냐
	gImage		m_ImgPassBack;
	POINT		m_ptPass;				// ImgPass 출력 좌표		
	gEdit		m_EditPassEnter;		// 들어갈때 비번 입력창

	// room == wait
	gImage		m_ImgCharBack;
	gImgButton	m_WaitBtn[BWM_END];
	gImage		m_ImgSelBack;
	bool		m_bCharSel;				// 캐릭터 고르고 있냐
	int			m_nSelUser;				// 선택된 유저

	// room - select
	gImage		m_ImgBarStudy;
	gImage		m_ImgBarStamina;
	gImage		m_ImgBarMove;


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
	void		pk_roomlist_rep(PK_ROOMLIST_REP *rep);
	void		pk_roomjoin_rep(PK_ROOMJOIN_REP *rep);
	void		pk_roomrefresh_rep(PK_ROOMREFRESH_REP *rep);

private:
	// make
	bool		SetUp_Make();
	void		MainLoop_Make();
	void		Draw_Make();
	void		OnLButtonDown_Make();
	void		OnLButtonUp_Make();
	void		OnMouseMove_Make();
	void		Cancel_Make();
	void		SendRoomMake();

	// join
	bool		SetUp_Join();
	void		MainLoop_Join();
	void		Draw_Join();
	void		OnLButtonDown_Join();
	void		OnMouseMove_Join();
	void		SendRoomJoin();

	// room
	bool		SetUp_Room();
	void		MainLoop_Room();
	void		Draw_Room();
	void		OnLButtonDown_Room();
	void		OnMouseMove_Room();
	void		OnLButtonUp_Room();
	void		OnRButtonDown_Room();

};
