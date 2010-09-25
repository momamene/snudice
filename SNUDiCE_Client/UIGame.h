//------------------------------------------------------------------------------------
//	gUIGame Class
//
//	2010. 09. 24	CoderK
//
//	게임모드의 인터페이스
//------------------------------------------------------------------------------------
#pragma once
#include "networkconst.h"
#include "Image.h"
#include "ImgButton.h"

enum UIIMAGE
{
	UIIMG_MAININFO,
	UIIMG_BAROUTLINE,
	UIIMG_BARGUAGE,

	UIIMG_SUBINFO,		// 아이템, 수강현황
	UIIMG_SUBWND,		// 수강편람

	UIIMG_PINFO,		// 우하단

	UIIMG_END,
};

enum UIBTN
{
	UIBTN_ITEMCARD,
	UIBTN_SUBJECT,
	UIBTN_SUBPREV,
	UIBTN_SUBNEXT,

	UIBTN_DICE,

	UIBTN_END,
};

enum UITYPE
{
	UIT_MAININFO,

	UIT_SUBINFO,		// 아이템, 수강현황
	UIT_SUBWND,			// 수강편람

	UIT_PINFO,			// 우하단

	UIT_DICE,

	UIT_END,
};


class gUIGame
{
public:
	static gUIGame *GetIF();

	gUIGame(void);
	~gUIGame(void);

public:
	gImage		m_ImgUI[UIIMG_END];
	gImgButton	m_BtnUI[UIBTN_END];
	RECT		m_rcPos[UIT_END];

	bool		m_bShowSubWnd;				// 수강편람 윈도우
	int			m_nSubSel;					// 수강편람 누구 보고있나

private:
	RECT		m_rcBarDest, m_rcBarSour;

public:
	bool		IsUIRange(int x, int y);


	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();
	
	bool		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
};
