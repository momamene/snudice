//------------------------------------------------------------------------------------
//	gTitleCore Class
//
//	2010. 08. 04	CoderK
//
//	타이틀 모드
//------------------------------------------------------------------------------------
#pragma once
#include "Core.h"
#include "Image.h"
#include "ImgButton.h"

enum eTITLEBTN
{
	ETB_START,			// 시작
	ETB_EXIT,			// 종료
	ETB_END,
};

class gTitleCore : Core
{
public:
	static gTitleCore	*GetIF();
	
	gTitleCore();
	virtual ~gTitleCore();

public:
	gImage		m_ImgBack;			// title 배경
	gImgButton	m_Btn[ETB_END];

public:
	// overridng from Core 인터페이스
	bool		SetUp();
	bool		MainLoop();
	void		Draw();
	void		Release();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
	// end overridng
};