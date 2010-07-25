//------------------------------------------------------------------------------------
//	gTitleCore Class
//
//	2010. 07. 16	CoderK
//
//	Ÿ��Ʋ ��� -> �÷��̾� ��� -> �����ھ��
//------------------------------------------------------------------------------------
#pragma once
#include "gImage.h"
#include "gCoreIF.h"
#include "gImgButton.h"
#include "const.h"

//#define PLAYERSEL			// �÷��̾� �� ���� �� �ֳ�

enum eTITLE_BTN
{
	ETB_START,
	ETB_EXIT,
	ETB_END,
};

enum eTITLEMODE
{
	ETM_TITLE,
	ETM_PLAYERSEL,			// �÷��̾� ��� �Ұų�
};

enum ePLAYERSEL
{
	EPS_PLAYER,				// ���
	EPS_COM,				// ��ǻ��
	EPS_NONE,				// ����
};

class gTitleCore : public gCoreIF
{
public:
	static gTitleCore	*GetIF();

	gTitleCore();
	virtual ~gTitleCore();
public:
	eTITLEMODE	m_eMode;

	// title
	gImage		m_ImgTitle;				// title ��� ���
	gImgButton	m_ImgBtn[ETB_END];

	// player
	gImgButton	m_ImgBtnPrev;
	gImgButton	m_ImgBtnNext;
	gImage		m_ImgPlayer;			// player select ��� ���
	gImage		m_ImgMode;
	gImage		m_ImgNP[MAXPLAYER];
	gImage		m_ImgCheck;
	ePLAYERSEL	m_ePlayer[MAXPLAYER];

public:
	bool		SetUp();
	void		MainLoop();
	void		Draw();

	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();

private:
	bool		SetUp_Title();
	bool		SetUp_PlayerSelect();

	void		Draw_Title();
	void		Draw_PlayerSelect();

	void		OnLButtonDown_Title();
	void		OnLButtonDown_PlayerSelect();

	void		OnMouseMove_Title();
	void		OnMouseMove_PlayerSelect();
};
