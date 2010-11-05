//------------------------------------------------------------------------------------
//	gGameCore Class
//
//	2010. 09. 23	CoderK
//
//	���� ���Ӹ��
//	m_bScrolling���� Scroll ���� �Լ� ���� m_bScrolling�� ������ ���� ��ũ�ε��� ����
//  ��, �̺�Ʈ�� �׻� 1��.
//------------------------------------------------------------------------------------
#pragma once
#include "networkconst.h"
#include "Core.h"
#include "Image.h"

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
	int			m_nTurn;		// ���� ��
	int			m_spacor;
	bool		m_bMoved;		// �ش� �Ͽ� ��������, �� movestart_ask �������� true
	bool		m_bMoving;		// �����̴� ���̳�
	bool		m_bScrolling;	// ��ũ���ϴ� ���̳�, m_bMoving�� �浹�� ����� �ִ�.

	bool		m_bBusSel;		// ���� �̵� ���ø��
	bool		m_bBusing;		// ������ �����̴� ���̳�
	gImage		m_ImgBus;
	int			m_curframe;		// ���� ������
//	POINT		m_ptBusPos;		// ���� ��� ��ġ

	bool		m_bWarping;
	bool		m_bWarpingList;



	PK_NEXTTURN_REP		m_pkNext;
	int			m_nKeepStart;
	bool		m_bNextTurnKeep;	// �� �ѱ�°� Keep. true�� keep �ص״� ���߿� ó��

private:
	BUSMOVE		m_busmode;
	int			m_buspos;			// ���� ���� ���

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
	void		pk_warpstart_rep(PK_WARPSTART_REP *rep);
	void		pk_warpliststart_rep(PK_WARPLISTSTART_REP* rep);

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

	void		DrawBus();
	void		DrawWarp();
	void		DrawWarpList();
	void		BusComeStart(int nPos);

};
