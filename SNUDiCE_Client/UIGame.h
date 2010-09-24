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
	UIIMG_END,
};

enum UITYPE
{
	UIT_MAININFO,
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
	RECT		m_rcPos[UIT_END];

public:
	bool		IsUIRange(int x, int y);


	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
};
