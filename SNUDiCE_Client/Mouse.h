//------------------------------------------------------------------------------------
//	gMouse Class
//
//	2010. 08. 04	CoderK
//
//	���콺 ���� ó��
//	Ư���ϰ� Core ���. WndProc���� ���콺 ���� ��� ������, �ش� �ھ �°� �Լ�ȣ��
//------------------------------------------------------------------------------------
#pragma once
#include "Core.h"

class gMouse : public Core
{
public:
	static gMouse	*GetIF();

	gMouse();
	virtual ~gMouse();
public:
	int			m_nPosX;		// ���콺 x, y ��ǥ
	int			m_nPosY;

	// overriding
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
	// end overriding

};
