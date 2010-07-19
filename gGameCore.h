//------------------------------------------------------------------------------------
//	gGameCore Class
//
//	2010. 07. 17	CoderK
//
//	메인 게임 모드. 주사위 굴리고 그런 게임
//------------------------------------------------------------------------------------
#pragma once
#include "gCoreIF.h"
#include "tileContainer.h"

enum eGAMEMODE
{
	EGM_GAME,
};

class gGameCore : public gCoreIF
{
public:
	static gGameCore	*GetIF();

	gGameCore();
	virtual ~gGameCore();
	int m_xPos;
	int m_yPos;
	int m_minimapOn; // 0 , 1, 2, 3 (1,2) 일 때 On, (3,0) 일 때 Off
	int m_spacor;





public:
	eGAMEMODE	m_eMode;

	bool		SetUp();
	void		MainLoop();
	void		Draw();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
};