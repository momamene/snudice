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

class gGameCore : Core
{
public:
	static gGameCore *GetIF();

	gGameCore(void);
	~gGameCore(void);

public:
	int			m_nTurn;		// 누구 턴
	int			m_spacor;
	bool		m_bMoved;		// 해당 턴에 움직엿냐, 즉 movestart_ask 보냇으면 true
	bool		m_bMoving;		// 움직이는 중이냐
	bool		m_bScrolling;	// 스크롤하는 중이냐, m_bMoving과 충돌될 우려가 있다.
	bool		m_bBusSel;		// 버스 이동 선택모드
	bool		m_bBusing;		// 버스로 움직이는 중이냐

	PK_NEXTTURN_REP		m_pkNext;
	int			m_nKeepStart;
	bool		m_bNextTurnKeep;	// 턴 넘기는거 Keep. true면 keep 해뒀다 나중에 처리

public:

	bool		PreTransMsg(MSG &msg);

	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();

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
	void		pk_popinfo_rep(PK_POPINFO_REP *rep);
	void		pk_gameend_rep(PK_GAMEEND_REP *rep);

	void		Start(int spacor);
	void		Start(int spacor,int conPosX,int conPosY);
	void		StepStart();
	void		StepOn();
	void		StepEnd();
	void		End();

	void		SendMoveAsk();
private:
	void		MainLoopMouse();

	void		ScrollStart(int nPos);
	void		ScrollOn();
	void		ScrollEnd();

	void		BusStart(int spacor);
	void		BusStart(int spacor,int conPosX, int conPosY);
	void		BusStepStart();
	void		BusStepOn();
	void		BusStepEnd();
	void		BusEnd();

};
