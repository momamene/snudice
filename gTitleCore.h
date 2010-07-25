//------------------------------------------------------------------------------------
//	gTitleCore Class
//
//	2010. 07. 16	CoderK
//
//	타이틀 모드 -> 플레이어 몇명 -> 게임코어로
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
};

enum ePLAYERSEL
{
	EPS_PLAYER,				// 사람
	EPS_COM,				// 컴퓨터
	EPS_NONE,				// 안해
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
	gImage		m_ImgTitle;				// title 모드 배경
	gImgButton	m_ImgBtn[ETB_END];

	// player
	gImgButton	m_ImgBtnPrev;
	gImgButton	m_ImgBtnNext;
	gImage		m_ImgPlayer;			// player select 모드 배경
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
