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

enum UIIMAGE
{
	UIIMG_MAININFO,
	UIIMG_BAROUTLINE,
	UIIMG_BARGUAGE,

	UIIMG_SUBINFO,		// ������, ������Ȳ
	UIIMG_SUBWND,		// �������

	UIIMG_PINFO,		// ���ϴ�

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

	UIT_SUBINFO,		// ������, ������Ȳ
	UIT_SUBWND,			// �������

	UIT_PINFO,			// ���ϴ�

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

	bool		m_bShowSubWnd;				// ������� ������
	int			m_nSubSel;					// ������� ���� �����ֳ�

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
