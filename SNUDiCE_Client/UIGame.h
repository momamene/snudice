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

	UIIMG_POPINFO1,		// ��ǳ�� info ����
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

	bool		m_bPopInfo;					// ��ǳ�� ����

	bool		m_bItem;					// ������ ����

private:
	RECT		m_rcBarDest, m_rcBarSour;
	int			m_rankIdx[ROOMMAXPLAYER];	// ��ŷ�ε���

	// ��ǳ�� info ����
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
