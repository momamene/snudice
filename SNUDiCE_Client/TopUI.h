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

class gTopUI
{
public:
	static gTopUI	*GetIF();

	gTopUI(void);
	~gTopUI(void);

public:
	RECT		m_rcPos;
	gImage		m_ImgBack;

public:
	bool		SetUp();
	void		Draw();
	void		Release();

	bool		Restore();
};
