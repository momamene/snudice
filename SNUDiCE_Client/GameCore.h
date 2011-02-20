//------------------------------------------------------------------------------------
//	gGameCore Class
//
//	2010. 09. 23	CoderK
//
//	메인 게임모드
//	m_bScrolling에서 Scroll 관련 함수 군과 m_bScrolling은 서버에 의해 싱크로되지 않음
//  단, 이벤트는 항상 1초.
//------------------------------------------------------------------------------------
#pragma once
#include "networkconst.h"
#include "Core.h"
#include "Image.h"

#define SLEEPTIMEMAX			20000	//최대 잠수 시간:10초 

enum BUSMOVE
{
	BUS_COME,
	BUS_BOARD,
	BUS_START,
	BUS_SCROLLSTART,
	BUS_SCROLLEND,
	BUS_COME2,
	BUS_BOARD2,
	BUS_START2,
};

enum WARP
{
	WARP_DISAPPEAR,
	WARP_SCROLLSTART,
	WARP_SCROLLEND,
	WARP_APPEAR,
};

enum WARPLIST
{
	WARPLIST_DISAPPEAR,
	WARPLIST_SCROLLSTART,
	WARPLIST_SCROLLEND,
	WARPLIST_APPEAR,
};

class gGameCore : Core
{
public:
	static gGameCore *GetIF();

	gGameCore(void);
	~gGameCore(void);

public:
	int			m_nTurn;		// 누구 턴
	int			m_nGameTurn;	// 전체적으로 몇 턴 지났냐.

	int			m_spacor;
	bool		m_bMoved;		// 해당 턴에 움직엿냐, 즉 movestart_ask 보냇으면 true
	bool		m_bMoving;		// 움직이는 중이냐
	bool		m_bScrolling;	// 스크롤하는 중이냐, m_bMoving과 충돌될 우려가 있다.

	bool		m_bBusSel;		// 버스 이동 선택모드
	bool		m_bBusing;		// 버스로 움직이는 중이냐
	gImage		m_ImgBus;
	int			m_curframe;		// 버스 프레임
//	POINT		m_ptBusPos;		// 버스 출력 위치

	bool		m_bWarping;
	bool		m_bWarpingList;

	int			m_remain;

	bool		m_bBreak;					// 깨졌냐
	int			m_nCoupleDebuffRemain;		// 커플 깨지고 디버프 남은 턴 수

	bool		m_bPrevInNokdu;				// 내 플레이어가 녹두에 있었나
											// 녹두 -> !녹두,  !녹두 -> 녹두 파악 위하여.
//
//private:
	BUSMOVE		m_busmode;
	int			m_buspos;			// 버스 도착 장소
	int			m_turnTime;			// 잠수시간 측정
	int			m_turnTime_Bus;		// 버스선택 잠수시간 측정
	int			m_turnTime_CoupleAsk;	//커플 묻기

	WARP		m_warp;
	int			m_warpCharIdx;
	int			m_warpDest;

	WARPLIST	m_warplist;
	int			m_warplistDest[ROOMMAXPLAYER];


public:

	bool		PreTransMsg(MSG &msg);

	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();

	void		Clear(int newTurn = 0);

	bool		Restore();

	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();

	void		pk_movestart_rep(PK_MOVESTART_REP *rep);
	void		pk_nextturn_rep(PK_NEXTTURN_REP *rep);
	void		pk_busmovechoose_rep(PK_BUSMOVECHOOSE_REP *rep);
	void		pk_busmovestart_rep(PK_BUSMOVESTART_REP *rep);
	void		pk_gameplayerinfo_rep(PK_GAMEPLAYERINFO_REP *rep);
	void		pk_gameend_rep(PK_GAMEEND_REP *rep);
	void		pk_warpstart_rep(PK_WARPSTART_REP *rep);
	void		pk_warpliststart_rep(PK_WARPLISTSTART_REP* rep);
	void		pk_askcouple_rep(PK_ASKCOUPLE_REP* rep);
	void		pk_movestartcouple_rep(PK_MOVESTART_REP *rep);
	void		pk_busmovestartcouple_rep(PK_BUSMOVESTART_REP *rep);
	void		pk_exit_rep(PK_EXIT_REP *rep);

	void		Start(int spacor);
	void		Start(int spacor,int conPosX,int conPosY);
	void		StepStart();
	void		StepOn();
	void		StepEnd();
	void		End(bool Abnormal_End = 0);

	void		SetDiceGuageMode();			// 주사위 굴리기 전에 게이지
	void		SendMoveAsk(float fRate = -1.0f);
private:
	void		MainLoopMouse();

	void		ScrollStart(int nPos);
	void		ScrollOn();
	void		ScrollEnd();

	void		DrawBus();
	void		DrawWarp();
	void		DrawWarpList();
	void		BusComeStart(int nPos);
};
