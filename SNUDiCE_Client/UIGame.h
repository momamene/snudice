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
#include "ScrollBar.h"

enum UIIMAGE
{
	UIIMG_MAININFO,
	UIIMG_BAROUTLINE,
	UIIMG_BARGUAGE,

	UIIMG_SUBINFO,		// 아이템, 수강현황
	UIIMG_SUBWND,		// 수강편람

	UIIMG_PINFO,		// 우하단

	UIIMG_NUMBER,		// 숫자 1 ~ 8 랭킹표시에쓸거

	UIIMG_POPINFO1,		// 말풍선 info 정보
	UIIMG_POPINFO2,

	UIIMG_END,
};

enum UIBTN
{
	UIBTN_ITEMCARD,
	UIBTN_SUBJECT,
	UIBTN_SUBPREV,
	UIBTN_SUBNEXT,

	UIBTN_MENU,

	UIBTN_DICE,

	UIBTN_END,
};

enum UITYPE
{
	UIT_MAININFO,

	UIT_SUBINFO,		// 아이템, 수강현황
	UIT_SUBWND,			// 수강편람

	UIT_PINFO,			// 우하단

	UIT_MENU,

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
	gScrollbar	m_Scroll;

	bool		m_bShowSubWnd;				// 수강편람 윈도우
	int			m_nSubSel;					// 수강편람 누구 보고있나

	int			m_nCurPInfo;				// 우하단 pinfo, cursor
	int			m_nMaxPInfo;

	bool		m_bPopInfo;					// 말풍선 인포

	bool		m_bItem;					// 아이템 모드냐

private:
	RECT		m_rcBarDest, m_rcBarSour;
	int			m_rankIdx[ROOMMAXPLAYER];	// 랭킹인덱스

	// 말풍선 info 정보
	int			m_nTimer;
	int			m_nShowTime;
	PK_POPINFO_REP		m_popinfo;
	int			m_szID[IDLENGTH];

public:
	bool		IsUIRange(int x, int y);

	void		SetPopInfo(PK_POPINFO_REP *rep, int ms = 2000);

	void		SetRankList();
	void		FirstInit();


	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();

	bool		Restore();
	
	bool		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
};
