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
#include "Image.h"
#include "networkconst.h"

#define DEF_WHISPER

//#define DEF_ONLYONECLIENT		// 한 컴퓨터에서 클라이언트 하나만 켜지게

#define DEFAULT_FULLSCREEN		false

//#define DEF_FRAMEPRINT
#define DEF_FRAMECOUNT			60
#define DEF_FRAMETICK			(1000 / DEF_FRAMECOUNT)

#define	WNDSIZEW		640
#define WNDSIZEH		480
#define GAMENAME		"SNUDiCE"
#define WNDSTYLE		(WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX)
#define BEEPHACKREG		"Control Panel\\Sound"
#define BEEPHACKREG2	"AppEvents\\Schemes\\Apps\\.Default\\.Default\\.Current"

#define BACKBUFFERIMG	".\\Data\\Login\\backbuffer.img"

enum BIT
{
	BIT_16 = 16,
	BIT_32 = 32,
};

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
	
	gImage		m_ImgBack;					// 항상 뒤에 출력이미지

	gImage		m_ImgLogo1;					// SNUGDC & SmileGate
	gImage		m_ImgLogo2;					// Project N

	eCOREMODE	m_eCoreMode;				// 게임이 어떤 모드냐

	// display
	bool		m_bFullScreen;
	BIT			m_bit;

	//	direct x
	LPDIRECTDRAW			m_lpDD;
	LPDIRECTDRAWSURFACE		m_lpDDPrimary;
	LPDIRECTDRAWSURFACE		m_lpDDBack;

	bool		SetUp(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow);
	bool		Restore();					// display 변경으로 인한 다이렉트 서피스 재셋팅
	void		Release();

	bool		FullScreen(bool bfull);
	void		ResizeWindow();

	int			Run();
	void		MoveWindow();
	void		Exit();

private:
	char		m_szTempReg[128];
	bool		m_bRestore;

private:
	bool		DisableBeep();
	bool		EnableBeep();
	bool		SetUpDirect();
	void		MainLoop();
	bool		RestoreRes();				// bit 바뀔 때만.
};

 