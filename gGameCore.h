//------------------------------------------------------------------------------------
//	gGameCore Class
//
//	2010. 07. 17	CoderK
//
//	���� ���� ���. �ֻ��� ������ �׷� ����
//------------------------------------------------------------------------------------
#pragma once
#include "gCoreIF.h"
#include "tileContainer.h"
#include "gPlayer.h"

#define MAXFRAMECOUNT 60	// �����غ��� �߿��� ����. �����⸦ ����!
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
	int m_minimapOn;	// 0 , 1, 2, 3 (1,2) �� �� On, (3,0) �� �� Off
	int m_spacor;
	int m_xPos;			// read-only ���� ������ ����?
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
	void		PutScreenPos(int x, int y);		// ����� PutScreenPos


	
	
private:
	// MainLoop�� ��������
	void MainLoopMouse();
	void MainLoopMove();
	void MainLoopKeyboard();

	void OnLButtonDownSubmit();
};