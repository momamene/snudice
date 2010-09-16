//------------------------------------------------------------------------------------
//	gMainWin Class
//
//	2010. 08. 04	CoderK
//
//	윈도우 관련 정보.
//	각종 셋업 및 게임의 주축.
//------------------------------------------------------------------------------------
#pragma once
#include <windows.h>
#include <ddraw.h>
#include "networkconst.h"

//#define FULLSCREEN		//	define 풀었다 해제하면서 fullscreen 체크

#define BIT				32
#define	WNDSIZEW		640
#define WNDSIZEH		480
#define GAMENAME		"SNU Dice"
#define WNDSTYLE		(WS_CAPTION | WS_SYSMENU)
#define BEEPHACKREG		"Control Panel\\Sound"
#define BEEPHACKREG2	"AppEvents\\Schemes\\Apps\\.Default\\.Default\\.Current"


class gMainWin  
{
public:
	static gMainWin		*GetIF();			// Use Singleton

	gMainWin();
	virtual ~gMainWin();

public:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	BOOL		m_Keys[256];				// keyboard
	RECT		m_rcScr;					// screen 출력 영역
	bool		m_bActive;					// 게임(윈도우)가 활성화 되어있나

	eCOREMODE	m_eCoreMode;				// 게임이 어떤 모드냐

	//	direct x
	LPDIRECTDRAW			m_lpDD;
	LPDIRECTDRAWSURFACE		m_lpDDPrimary;
	LPDIRECTDRAWSURFACE		m_lpDDBack;

	bool		SetUp(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow);
	void		Release();
	int			Run();
	void		MoveWindow();
	void		Exit();

private:
	char		m_szTempReg[128];	

private:
	bool		DisableBeep();
	bool		EnableBeep();
	bool		SetUpDirect();
	void		MainLoop();
};

 