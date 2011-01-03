//------------------------------------------------------------------------------------
//	gTopUI Class
//
//	2010. 09. 04	CoderK
//
//	화면 맨 위쪽에 있는 부분의 UI
//------------------------------------------------------------------------------------
#pragma once
#include "MainWin.h"
#include "Image.h"
#include "ImgButton.h"

enum TOPUIBTN
{
	TOP_BACK,			// 뒤로가기
	TOP_OPTION,			// 옵션
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
	RC_OPTION,		// m_uimode 에 쓰임
	RC_END,			// == NONE, 아무 모드도 아님
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

	void			OnLButtonDown_Back();		// 뒤로 가기 버튼

	bool			Restore();
};
