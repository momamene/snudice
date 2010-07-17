//------------------------------------------------------------------------------------
//	gMouse Class
//
//	2010. 07. 16	CoderK
//
//	���콺 ���� ó��
//	Ư���ϰ� CoreIF ���. WndProc���� ���콺 ���� ��� ������, �ش� �ھ �°� �Լ�ȣ��
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
	int			m_nPosX;		// ���콺 x, y ��ǥ
	int			m_nPosY;

	bool		SetUp();
	void		MainLoop();
	void		Draw();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();

};
