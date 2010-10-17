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

	PK_NEXTTURN_REP		m_pkNext;
	int			m_nKeepStart;
	bool		m_bNextTurnKeep;	// �� �ѱ�°� Keep. true�� keep �ص״� ���߿� ó��

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
