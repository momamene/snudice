//------------------------------------------------------------------------------------
//	gTitleCore Class
//
//	2010. 07. 16	CoderK
//
//	Ÿ��Ʋ ��� -> �÷��̾� ��� -> ĳ���� ���� -> ������û
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
	ETM_CHARSEL,			// ���� ĳ���Ͱ���
	ETM_SUGANG,				// ������û
};

enum ePLAYERSEL
{
	EPS_PLAYER,				// ���
	EPS_COM,				// ��ǻ��
	EPS_NONE,				// ����
};

class gImage;
class gTitleCore : public gCoreIF
{
public:
	static gTitleCore	*GetIF();

	gTitleCore();
	virtual ~gTitleCore();
public:
	// prev next button
	gImgButton	m_ImgBtnPrev;
	gImgButton	m_ImgBtnNext;

	// title
	gImage		m_ImgTitle;
	gImgButton	m_ImgBtn[ETB_END];

	// player
	gImage		m_ImgPlayer;
	gImage		m_ImgMode;
	gImage		m_ImgNP[MAXPLAYER];
	gImage		m_ImgCheck;
	ePLAYERSEL	m_ePlayer[MAXPLAYER];

	// sel
	gImage		m_ImgSel;
	gImgButton	m_ImgID[CHARNUM];
	int			m_nSel;		// ���õȳ�

	eTITLEMODE	m_eMode;

	bool		SetUp();
	void		MainLoop();
	void		Draw();

	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
};
