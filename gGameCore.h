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
#include "gPlayer.h"

#define MAXFRAMECOUNT 180
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
	int m_minimapOn;	// 0 , 1, 2, 3 (1,2) 일 때 On, (3,0) 일 때 Off
	int m_spacor;
	int m_xPos;			// read-only 같은 설정은 없나?
	int m_yPos;
	int m_frameCount;

	// temp
	//gPlayer a;
	


public:
	eGAMEMODE	m_eMode;

	bool		SetUp();
	void		MainLoop();
	void		Draw();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
	void		PutScreenPos(int x, int y);		

private:
	// MainLoop의 떨거지들
	void gGameCore::MainLoopMouse();
	void gGameCore::MainLoopKeyboard();
};