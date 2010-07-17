//------------------------------------------------------------------------------------
//	gMouse Class
//
//	2010. 07. 16	CoderK
//
//	마우스 관련 처리
//	특이하게 CoreIF 상속. WndProc에서 마우스 관련 명령 받으면, 해당 코어에 맞게 함수호출
//------------------------------------------------------------------------------------
#pragma once
#include "gCoreIF.h"

class gMouse : public gCoreIF
{
public:
	static gMouse	*GetIF();

	gMouse();
	virtual ~gMouse();
public:
	int			m_nPosX;		// 마우스 x, y 좌표
	int			m_nPosY;

	bool		SetUp();
	void		MainLoop();
	void		Draw();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();

};
