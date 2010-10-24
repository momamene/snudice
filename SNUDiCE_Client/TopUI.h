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

#define TOP_FILE_BACK			".\\Data\\Interface\\top_back.img"
#define TOP_POS_BACK_X			0
#define TOP_POS_BACK_Y			0
#define TOP_POS_BACK_W			640
#define TOP_POS_BACK_H			60

#define TOP_BTN_BACK_FILE			".\\Data\\Interface\\top_btn_back.img"
#define TOP_BTN_SIZEW			30
#define TOP_BTN_SIZEH			30
#define TOP_BTN_POS_X			595
#define TOP_BTN_POS_Y			15
#define TOP_BTN_TERM_X			40

enum TOPUIBTN
{
	TOP_BACK,			// 뒤로가기
	TOP_END,
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

	gImgButton		m_Btn[TOP_END];

public:
	bool			SetUp();
	void			Draw();
	void			Release();

	bool			PointInUI(int x, int y);
	void			OnLButtonDown(int x, int y);
	void			OnMouseMove(int x, int y);

	void			OnLButtonDown_Back();		// 뒤로 가기 버튼

	bool			Restore();
};
