//------------------------------------------------------------------------------------
//	gSubmitCore Class
//
//	2010. 09. 23	CoderK
//
//	수강신청
//------------------------------------------------------------------------------------
#pragma once
#include "networkconst.h"
#include "Image.h"
#include "ImgButton.h"
#include "Core.h"

class gSubmitCore : Core
{
public:
	static gSubmitCore	*GetIF();

	gSubmitCore(void);
	~gSubmitCore(void);

public:
	gImage			m_ImgBack;

public:
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
};
