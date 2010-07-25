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

#define MAXFRAMECOUNT 60	// �����غ��� �߿��� ����. �����⸦ ����!

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

	gGameCore();
	virtual ~gGameCore();

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

	void		SetPlayerIndex(int nP = 0);				// 1p 2p 3p�� 1p �� ���� index�� ����
private:
	bool		SetUp_CharSelect();

	// MainLoop�� ��������
	void		MainLoopMouse();
	void		MainLoopMove();
	void		MainLoopKeyboard();

	void		OnLButtonDownSubmit();

	void		OnLButtonDown_CharSel();
	void		OnMouseMove_CharSel();

	void		Draw_CharSelect();
};