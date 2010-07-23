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

#define MAXFRAMECOUNT 60	// 생각해보니 중요한 변수. 빠르기를 결정!
enum eGAMEMODE
{
	EGM_SUBMIT,
	EGM_GAME,
};

class gGameCore : public gCoreIF
{
public:
	static gGameCore	*GetIF();
	eGAMEMODE m_gMode;

//	gGameCore();
//	virtual ~gGameCore();
	int m_minimapOn;	// 0 , 1, 2, 3 (1,2) 일 때 On, (3,0) 일 때 Off
	int m_spacor;
	int m_xPos;			// read-only 같은 설정은 없나?
	int m_yPos;
	int m_frameCount;

	int m_turnN;
	int m_turnPlayer;

	int m_selectSubject;

	//int		m_selectSubject;
	//int		m_selectTurn;
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
	void		PutScreenPos(int x, int y);		// 상우의 PutScreenPos


	
	
private:
	// MainLoop의 떨거지들
	void MainLoopMouse();
	void MainLoopMove();
	void MainLoopKeyboard();

	void OnLButtonDownSubmit();
};