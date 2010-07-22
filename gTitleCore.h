//------------------------------------------------------------------------------------
//	gTitleCore Class
//
//	2010. 07. 16	CoderK
//
//	타이틀 모드 -> 플레이어 몇명 -> 캐릭터 선택 -> 수강신청
//------------------------------------------------------------------------------------
#pragma once
#include "gImage.h"
#include "gCoreIF.h"
#include "gImgButton.h"
#include "const.h"

//#define PLAYERSEL			// 플레이어 수 정할 수 있냐

enum eTITLE_BTN
{
	ETB_START,
	ETB_EXIT,
	ETB_END,
};

enum eTITLEMODE
{
	ETM_TITLE,
	ETM_PLAYERSEL,			// 플레이어 몇명 할거냐
	ETM_CHARSEL,			// 각자 캐릭터고르자
	ETM_SUGANG,				// 수강신청
};

enum ePLAYERSEL
{
	EPS_PLAYER,				// 사람
	EPS_COM,				// 컴퓨터
	EPS_NONE,				// 안해
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
	int			m_nSel;		// 선택된넘

	eTITLEMODE	m_eMode;

	bool		SetUp();
	void		MainLoop();
	void		Draw();

	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
};
