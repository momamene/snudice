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
#include "Image.h"

enum MOUSEMODE
{
	MM_DEFAULT1,
	MM_DEFAULT2,
	MM_END,
};

class gMouse : public Core
{
public:
	static gMouse	*GetIF();

	gMouse();
	virtual ~gMouse();
public:
	gImage		m_ImgMouse;
	int			m_nPosX;		// ���콺 x, y ��ǥ
	int			m_nPosY;
	MOUSEMODE	m_modeMouse;

	bool		m_bShow;

	// overriding
	void		SetShow(bool show);
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();
	
	bool		Restore();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
	// end overriding

};
