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

//#define MAXFRAMECOUNT 30	// 생각해보니 중요한 변수. 빠르기를 결정!
// 우리집 컴터가 하도 느림. 한 4배 차이나는 듯.

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

	int			m_minimapOn;			// 0 , 1, 2, 3 (1,2) 일 때 On, (3,0) 일 때 Off
	int			m_spacor;

	// m_xPos, m_yPos 는 Draw되는 시작 시점을 의미한다.
	int			m_xPos;					// read-only 같은 설정은 없나?
	int			m_yPos;
	int			m_frameCount;			// frameCount는 Timer 기능을 가지는 것으로, gTimer class에 의해 대체될 운명이다.

	int			m_turnN;				// 몇턴인가?
	int			m_turnPlayer;			// 누구 차례인가?

	int			m_selectSubject;		// submit에서 선택된 과목이 m_selectSubject이다. (index, 혹은 maptool에서 flag2값)

	//int		m_selectSubject;
	//int		m_selectTurn;
	// temp
	//gPlayer a;

	// 무엇에 쫓기는가
	int			m_busMode;
	
	int			m_masterState;	// 0이면 아무것도 아님 (기본값), 1이면 움직인 다음에도 턴이 넘어가지 않음.

	int			m_tempNextMode;
	
public:
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();

	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();

	void		PutScreenPos(int x, int y);				// 상우의 PutScreenPos 좌표는 절대값입니다.

	void		SetPlayerIndex(int nP = 0);				// 1p 2p 3p면 1p 를 시작 index로 셋팅
private:


	void		startTurnAuto();
	void		SetUp_Submit();

	// MainLoop의 떨거지들
	void		MainLoopMouse();
	void		MainLoopKeyboard();
	void		MainLoopMouseSubmit();	// submit 
	// MainLoop의 떨거지인 MainLoopMove와 그들의 떨거지들
	void		MainLoopMove();
	void		MainLoopMoveSetup(int spacor=0);
	void		MainLoopMoveOn(int a);
	void		MainLoopMoveStepEnd();
	void		MainLoopMoveStepStart();
	void		MainLoopMoveEnd();
	
	// OnLButtonDown
	void		OnLButtonDownSubmit();
	void		OnLButtonDownBus();
	void		PlayerPosSet();

	// 기타 중요 colony
	void		nextTurnAuto();
	int			nextPlayer(int turnPlayer);

	// CharSelect Colony
	bool		SetUp_CharSelect();
	void		OnLButtonDown_CharSel();
	void		OnMouseMove_CharSel();
	void		Draw_CharSelect();
	
	
};