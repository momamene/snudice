//------------------------------------------------------------------------------------
//	gMainWin Class													MainWin -> Server
//
//	2010. 08. 04	CoderK
//
//	������ ���� ����.
//	���� �¾� �� ������ ����.
//-------------------i-----------------------------------------------------------------
#pragma once
#include <windows.h>
#include <ddraw.h>
//#include "networkconst.h"
#include "network.h"

//#define FULLSCREEN		//	define Ǯ���� �����ϸ鼭 fullscreen üũ

#define BIT				32
#define	WNDSIZEW		640
#define WNDSIZEH		480
#define GAMENAME		"SNU Dice"
#define WNDSTYLE		(WS_CAPTION | WS_SYSMENU)
//#define BEEPHACKREG		"Control Panel\\Sound"
//#define BEEPHACKREG2	"AppEvents\\Schemes\\Apps\\.Default\\.Default\\.Current"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ProcessClient(LPVOID arg);
DWORD WINAPI Run(LPVOID prc);

class gMainWin  
{
public:
	static gMainWin		*GetIF();			// Use Singleton
	
	gMainWin();
	virtual ~gMainWin();
	SOCKET		m_listen_sock;
	
public:
	HINSTANCE	m_hInst;
	//HWND		m_hWnd;
	BOOL		m_Keys[256];				// keyboard
	RECT		m_rcScr;					// screen ��� ����
	bool		m_bActive;					// ����(������)�� Ȱ��ȭ �Ǿ��ֳ�
	
//	eCOREMODE	m_eCoreMode;				// ������ � ����
	
	//	direct x
	/*
	LPDIRECTDRAW			m_lpDD;
	LPDIRECTDRAWSURFACE		m_lpDDPrimary;
	LPDIRECTDRAWSURFACE		m_lpDDBack;
	*/
	bool		Send(DWORD type, DWORD size, void *buf, SOCKET sock);
	void		Recv(PK_DEFAULT *pk, SOCKET	sock);

	bool		SetUp(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow);
	void		Release();
	//DWORD WINAPI	Run(LPVOID prc);
	//void		MoveWindow();
	void		Exit();
	
private:
	char		m_szTempReg[128];	
	
public:
	//bool		DisableBeep();
	//bool		EnableBeep();
	//bool		SetUpDirect();
	void		MainLoop();
};

 