//------------------------------------------------------------------------------------
//	gSubmitCore Class
//
//	2010. 09. 23	CoderK
//
//	������û
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
	gImgButton		m_BtnClass[CLASSNUM];
	int				m_nSelected;				// ���콺 hover�� ����

public:
	bool			SetUp();
	void			MainLoop();
	void			Draw();
	void			Release();
	
	void			OnLButtonDown();
	void			OnLButtonUp();
	void			OnMouseMove();
	void			OnRButtonDown();
};
