//------------------------------------------------------------------------------------
//	gTitleCore Class
//
//	2010. 07. 16	CoderK
//
//	타이틀 모드
//------------------------------------------------------------------------------------
#pragma once
#include "gImage.h"
#include "gCoreIF.h"
#include "gImgButton.h"

enum eTITLE_BTN
{
	ETB_START,
	ETB_EXIT,
	ETB_END,
};

enum eTITLEMODE
{
	ETM_TITLE,
	ETM_CHARSEL,
};

class gImage;
class gTitleCore : public gCoreIF
{
public:
	static gTitleCore	*GetIF();

	gTitleCore();
	virtual ~gTitleCore();
public:
	gImage		m_ImgTitle;
	gImgButton	m_ImgBtn[ETB_END];

	eTITLEMODE	m_eMode;

	bool		SetUp();
	void		MainLoop();
	void		Draw();

	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
};
