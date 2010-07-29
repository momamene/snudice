//------------------------------------------------------------------------------------
//	gGameCore Class
//
//	2010. 07. 17	CoderK
//
//	���� ���� ���. �ֻ��� ������ �׷� ����
//------------------------------------------------------------------------------------
#pragma once
#include "gImage.h"
#include "gImgButton.h"
#include "gCoreIF.h"
#include "tileContainer.h"
#include "gPlayer.h"

//#define MAXFRAMECOUNT 30	// �����غ��� �߿��� ����. �����⸦ ����!
// �츮�� ���Ͱ� �ϵ� ����. �� 4�� ���̳��� ��.

enum eGAMEMODE
{
	EGM_CHARSEL,			// ĳ���� ����
	EGM_SUBMIT,				// ������û
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
	gImage		m_ImgWho;				// Player n  ǥ��
	gImage		m_ImgOutline;			// �ƿ�����
	gImgButton	m_BtnStart;				// ���۹�ư
	gImgButton	m_ImgID[CHARNUM];
	int			m_nSelected[CHARNUM];	// �������  -1 no , 0 -> 1p
	int			m_nSel;					// ���õȳ�
	int			m_nPlayer;				// �������ʳ�


	int			m_minimapOn;	// 0 , 1, 2, 3 (1,2) �� �� On, (3,0) �� �� Off
	int			m_spacor;
	int			m_xPos;			// read-only ���� ������ ����?
	int			m_yPos;
	int			m_frameCount;

	int			m_turnN;
	int			m_turnPlayer;

	int			m_selectSubject;

	//int		m_selectSubject;
	//int		m_selectTurn;
	// temp
	//gPlayer a;

	// ������ �ѱ�°�
	int		m_busMode;
	
public:
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();

	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();

	void		PutScreenPos(int x, int y);		// ����� PutScreenPos

	void		SetPlayerIndex(int nP = 0);				// 1p 2p 3p�� 1p �� ���� index�� ����
private:


	void		startTurnAuto();
	void		SetUp_Submit();
	// MainLoop�� ��������
	void		MainLoopMouse();
	void		MainLoopMove();
	void		MainLoopKeyboard();
	void		MainLoopMouseSubmit();	// submit 

	// OnLButtonDown
	void		OnLButtonDownSubmit();
	void		OnLButtonDownBus();

	// ��Ÿ �߿� colony
	void		nextTurnAuto();
	
	// CharSelect Colony
	bool		SetUp_CharSelect();
	void		OnLButtonDown_CharSel();
	void		OnMouseMove_CharSel();
	void		Draw_CharSelect();
};