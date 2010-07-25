//------------------------------------------------------------------------------------
//	gGameCore Class
//
//	2010. 07. 17	CoderK
//
//	메인 게임 모드. 주사위 굴리고 그런 게임
//------------------------------------------------------------------------------------
#pragma once
#include "gImage.h"
#include "gImgButton.h"
#include "gCoreIF.h"
#include "tileContainer.h"
#include "gPlayer.h"

#define MAXFRAMECOUNT 60	// 생각해보니 중요한 변수. 빠르기를 결정!

enum eGAMEMODE
{
	EGM_CHARSEL,			// 캐릭터 고르기
	EGM_SUBMIT,				// 수강신청
	EGM_GAME,
};

class gGameCore : public gCoreIF
{
public:
	static gGameCore	*GetIF();

	gGameCore();
	virtual ~gGameCore();

public:
	eGAMEMODE	m_gMode;

	//	char select
	gImage		m_ImgSelBack;
	gImage		m_ImgWho;				// Player n  표시
	gImage		m_ImgOutline;			// 아웃라인
	gImgButton	m_BtnStart;				// 시작버튼
	gImgButton	m_ImgID[CHARNUM];
	int			m_nSelected[CHARNUM];	// 골라졌냐  -1 no , 0 -> 1p
	int			m_nSel;					// 선택된넘
	int			m_nPlayer;				// 누구차례냐


	int			m_minimapOn;	// 0 , 1, 2, 3 (1,2) 일 때 On, (3,0) 일 때 Off
	int			m_spacor;
	int			m_xPos;			// read-only 같은 설정은 없나?
	int			m_yPos;
	int			m_frameCount;

	int			m_turnN;
	int			m_turnPlayer;

	int			m_selectSubject;

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

	void		SetPlayerIndex(int nP = 0);				// 1p 2p 3p면 1p 를 시작 index로 셋팅
private:
	bool		SetUp_CharSelect();

	// MainLoop의 떨거지들
	void		MainLoopMouse();
	void		MainLoopMove();
	void		MainLoopKeyboard();

	void		OnLButtonDownSubmit();

	void		OnLButtonDown_CharSel();
	void		OnMouseMove_CharSel();

	void		Draw_CharSelect();
};