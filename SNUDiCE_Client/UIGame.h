//------------------------------------------------------------------------------------
//	gUIGame Class
//
//	2010. 09. 24	CoderK
//
//	���Ӹ���� �������̽�
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

	UIIMG_SUBINFO,		// ������, ������Ȳ
	UIIMG_SUBWND,		// �������

	UIIMG_PINFO,		// ���ϴ�

	UIIMG_NUMBER,		// ���� 1 ~ 8 ��ŷǥ�ÿ�����

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

	UIT_SUBINFO,		// ������, ������Ȳ
	UIT_SUBWND,			// �������

	UIT_PINFO,			// ���ϴ�

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

	bool		m_bShowSubWnd;				// ������� ������
	int			m_nSubSel;					// ������� ���� �����ֳ�

	int			m_nCurPInfo;				// ���ϴ� pinfo, cursor
	int			m_nMaxPInfo;

private:
	RECT		m_rcBarDest, m_rcBarSour;
	int			m_rankIdx[ROOMMAXPLAYER];	// ��ŷ�ε���

public:
	bool		IsUIRange(int x, int y);

	void		SetRankList();
	void		FirstInit();


	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();
	
	bool		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
};
