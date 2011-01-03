//------------------------------------------------------------------------------------
//	gTopUI Class
//
//	2010. 09. 04	CoderK
//
//	ȭ�� �� ���ʿ� �ִ� �κ��� UI
//------------------------------------------------------------------------------------
#pragma once
#include "MainWin.h"
#include "Image.h"
#include "ImgButton.h"

enum TOPUIBTN
{
	TOP_BACK,			// �ڷΰ���
	TOP_OPTION,			// �ɼ�
	TOP_END,
};

enum TOPOPTBTN
{
	OPT_OK,
	OPT_CANCEL,
	OPT_END,
};

enum TOPUIIMG
{
	IMG_OPTION,
	IMG_BAR,
	IMG_END,
};

enum TOPUIRANGE
{
	RC_OPTION,		// m_uimode �� ����
	RC_END,			// == NONE, �ƹ� ��嵵 �ƴ�
};

class gTopUI
{
public:
	static gTopUI	*GetIF();

	gTopUI(void);
	~gTopUI(void);


public:
	RECT			m_rcPos;
	gImage			m_ImgBack;

	gImage			m_Img[IMG_END];
	RECT			m_rc[RC_END];

	gImgButton		m_Btn[TOP_END];
	gImgButton		m_OptBtn[OPT_END];

	TOPUIRANGE		m_uimode;

public:
	bool			SetUp();
	void			Draw();

	void			Draw_Back();
	void			Draw_Option();

	void			Release();

	bool			PointInUI(int x, int y);
	void			OnLButtonDown(int x, int y);
	void			OnRButtonDown(int x, int y);
	void			OnMouseMove(int x, int y);

	void			OnLButtonDown_Back();		// �ڷ� ���� ��ư

	bool			Restore();
};
