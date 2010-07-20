//------------------------------------------------------------------------------------
//	gInterface Class
//
//	2010. 07. 20	CoderK
//
//	게임 모드의 인터페이스 처리
//------------------------------------------------------------------------------------
#pragma once
#include "gCoreIF.h"
#include "gImage.h"
#include "gImgButton.h"

enum eMENU_BTN
{
	EBTN_SUGANG,
	EBTN_ITEMCARD,
	EBTN_SYSTEM,
	EBTN_END
};

enum eMENUMODE
{
	EMM_SUGANG,
	EMM_ITEMCARD,
	EMM_SYSTEM,
	EMM_END
};

class gInterface : public gCoreIF
{
public:
	static gInterface	*GetIF();

	gInterface();
	virtual ~gInterface();
public:
	gImage		m_ImgMenuback;
	gImgButton	m_BtnMenu[EBTN_END];
	gImage		m_ImgMenu[EMM_END];
	eMENUMODE	m_eMenuMode;

	bool		SetUp();
	void		MainLoop();
	void		Draw();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
};

