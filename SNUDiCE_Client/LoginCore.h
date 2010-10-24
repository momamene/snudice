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
	gImage		m_ImgLogBox;
	gImgButton	m_Btn[ELB_END];
	gEdit		m_EditID;
	gEdit		m_EditPW;

public:
	// overridng from Core �������̽�
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();

	bool		Restore();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
	// end overridng

	void		ClearEdit();

	bool		PreTransMsg(MSG &msg);
private:
	void		SendLogin();

public:
	void		pk_login_rep(PK_LOGIN_REP *rep);
};