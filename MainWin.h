//------------------------------------------------------------------------------------
//	gMainWin Class
//
//	2010. 07. 16	CoderK
//
//	���� �¾� �� ������ ����.
//------------------------------------------------------------------------------------
#pragma once
#include <windows.h>
#include <ddraw.h>

//#define FULLSCREEN		//	define Ǯ���� �����ϸ鼭 fullscreen üũ

enum eMAINCORE
{
	EMC_TITLE,		// title mode
	EMC_GAME,		// game mode
};

class gMainWin  
{
public:
	static gMainWin		*GetIF();			// Use Singleton

	gMainWin();
	virtual ~gMainWin();
public:
	HWND		m_hWnd;
	BOOL		m_Keys[256];				// keyboard
	RECT		m_rcScr;					// screen
	eMAINCORE	m_eCoreMode;
	bool		m_bActive;

	//	direct x
	LPDIRECTDRAW			m_lpDD;
	LPDIRECTDRAWSURFACE		m_lpDDPrimary;
	LPDIRECTDRAWSURFACE		m_lpDDBack;

	bool		SetUp(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow);
	void		Release();
	int			Run();
	void		MainLoop();
	void		MoveWindow();
	void		Exit();

private:
	bool		SetUpDirect();
};

 