//------------------------------------------------------------------------------------
//	gGameCore Class
//
//	2010. 09. 23	CoderK
//
//	���� ���Ӹ��
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

public:

	bool		PreTransMsg(MSG &msg);

	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();

	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();

	void		pk_movestart_rep(PK_MOVESTART_REP *rep);
	void		pk_nextturn_rep(PK_NEXTTURN_REP *rep);

	void		Start(int spacor);
	void		Start(int spacor,int conPosX,int conPosY);
	void		StepStart();
	void		StepOn();
	void		StepEnd();
	void		End();

	void		SendMoveAsk();
private:
	void		MainLoopMouse();

};
