//------------------------------------------------------------------------------------
//	gLoginCore Class
//
//	2010. 08. 04	CoderK
//
//	로그인 모드. 게임의 시작.
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
	ELB_CONNECT,		// 접속

// 	ELB_START,			// 시작
// 	ELB_EXIT,			// 종료
	ELB_END,
};

class gLoginCore : Core
{
public:
	static gLoginCore	*GetIF();
	
	gLoginCore();
	virtual ~gLoginCore();

public:
	gImage		m_ImgBack;			// title 배경
	gImage		m_ImgLogBox;
	gImgButton	m_Btn[ELB_END];
	gEdit		m_EditID;
	gEdit		m_EditPW;

public:
	// overridng from Core 인터페이스
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