//------------------------------------------------------------------------------------
//	gTitleCore Class
//
//	2010. 08. 04	CoderK
//
//	Ÿ��Ʋ ���
//------------------------------------------------------------------------------------
#pragma once
#include "Core.h"
#include "Image.h"
#include "ImgButton.h"

enum eTITLEBTN
{
	ETB_START,			// ����
	ETB_EXIT,			// ����
	ETB_END,
};

class gTitleCore : Core
{
public:
	static gTitleCore	*GetIF();
	
	gTitleCore();
	virtual ~gTitleCore();

public:
	gImage		m_ImgBack;			// title ���
	gImgButton	m_Btn[ETB_END];

public:
	// overridng from Core �������̽�
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