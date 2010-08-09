//------------------------------------------------------------------------------------
//	gLoginCore Class
//
//	2010. 08. 04	CoderK
//
//	�α��� ���. ������ ����.
//------------------------------------------------------------------------------------
#pragma once
#include <windows.h>
#include "Core.h"
#include "Image.h"
#include "ImgButton.h"
#include "Edit.h"
#include "networkconst.h"

enum eLOGINBTN
{
	ELB_CONNECT,		// ����

// 	ELB_START,			// ����
// 	ELB_EXIT,			// ����
	ELB_END,
};

class gLoginCore : Core
{
public:
	static gLoginCore	*GetIF();
	
	gLoginCore();
	virtual ~gLoginCore();

public:
	gImage		m_ImgBack;			// title ���
	gImgButton	m_Btn[ELB_END];
	gEdit		m_EditID;
	gEdit		m_EditPW;

public:
	// overridng from Core �������̽�
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
	// end overridng

	bool		PreTransMsg(MSG &msg);

public:
	void		pk_login_rep(PK_LOGIN_REP *rep);
};