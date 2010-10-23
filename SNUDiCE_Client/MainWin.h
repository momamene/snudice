//------------------------------------------------------------------------------------
//	gMainWin Class
//
//	2010. 08. 04	CoderK
//
//	������ ���� ����.
//	���� �¾� �� ������ ����.
//------------------------------------------------------------------------------------
#pragma once
#include <windows.h>
#include <ddraw.h>
#include "Image.h"
#include "networkconst.h"

//#define FULLSCREEN		//	define Ǯ���� �����ϸ鼭 fullscreen üũ

#define DEFAULT_FULLSCREEN		false

#define	WNDSIZEW		640
#define WNDSIZEH		480
#define GAMENAME		"SNUDiCE"
#define WNDSTYLE		(WS_CAPTION | WS_SYSMENU)
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
	RECT		m_rcScr;					// screen ��� ����
	bool		m_bActive;					// ����(������)�� Ȱ��ȭ �Ǿ��ֳ�
	
	gImage		m_ImgBack;					// �׻� �ڿ� ����̹���

	eCOREMODE	m_eCoreMode;				// ������ � ����

	// display
	bool		m_bFullScreen;
	BIT			m_bit;

	//	direct x
	LPDIRECTDRAW			m_lpDD;
	LPDIRECTDRAWSURFACE		m_lpDDPrimary;
	LPDIRECTDRAWSURFACE		m_lpDDBack;

	bool		SetUp(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow);
	bool		Restore();					// display �������� ���� ���̷�Ʈ ���ǽ� �����
	void		Release();

	bool		FullScreen(bool bfull);

	int			Run();
	void		MoveWindow();
	void		Exit();
	void		SendExit();	//�����߰��������ó������

private:
	char		m_szTempReg[128];
	bool		m_bRestore;

private:
	bool		DisableBeep();
	bool		EnableBeep();
	bool		SetUpDirect();
	void		MainLoop();
	void		ResizeWindow();
	bool		RestoreRes();				// bit �ٲ� ����.
};

 