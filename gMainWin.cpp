#include "gMainWin.h"
#include "const.h"
#include "gTitleCore.h"
#include "gGameCore.h"
#include "gMouse.h"
#include "gCharManager.h"
#include "gInterface.h"
#include "gUtil.h"
#include "gPlayerManager.h"
#include "gPopUp.h"

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//------------------------------------------------------------------------------------
//	Constructor	/	Destructor
//------------------------------------------------------------------------------------

static gMainWin	s_MainWin;		// for singleton

gMainWin::gMainWin()
{

}

gMainWin::~gMainWin()
{

}

gMainWin* gMainWin::GetIF()
{
	return &s_MainWin;
}

//------------------------------------------------------------------------------------
//	SetUp
//------------------------------------------------------------------------------------
bool gMainWin::SetUp(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	// Initialize
	memset(this, 0, sizeof(gMainWin));

	// Make Window
	WNDCLASS	WndClass;
	memset(&WndClass, 0, sizeof(WNDCLASS));
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance		= hInstance;
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;
	WndClass.lpszClassName	= GAMENAME;
	WndClass.lpszMenuName	= NULL;
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

#ifdef FULLSCREEN
	m_hWnd = CreateWindow(GAMENAME, GAMENAME, WS_POPUP, 
						CW_USEDEFAULT, CW_USEDEFAULT, WNDSIZEW, WNDSIZEH,
						NULL, (HMENU)NULL, hInstance, NULL);
#else
	m_hWnd = CreateWindow(GAMENAME, GAMENAME, WNDSTYLE, 
						CW_USEDEFAULT, CW_USEDEFAULT, WNDSIZEW, WNDSIZEH,
						NULL, (HMENU)NULL, hInstance, NULL);

	// ReSize Window
	RECT	rcWin = {0, 0, WNDSIZEW, WNDSIZEH};
	AdjustWindowRect(&rcWin, WNDSTYLE, false);
	SetWindowPos(m_hWnd, NULL, 0, 0,
			rcWin.right - rcWin.left, rcWin.bottom - rcWin.top,
			SWP_NOMOVE | SWP_NOZORDER);

	MoveWindow();
#endif

	// Set core
	m_eCoreMode = EMC_TITLE;

	if(FAILED(SetUpDirect()))
		return false;


	// SetUp TitleCore 
	if(FAILED(gTitleCore::GetIF()->SetUp()))
	{
		MessageBox(m_hWnd, "TitleCore : Setup ����", "Error", MB_OK);
		return false;
	}

	// SetUp CharManager
	if(FAILED(gCharManager::GetIF()->SetUp()))
	{
		MessageBox(m_hWnd, "CharManager : Setup ����", "Error", MB_OK);
		return false;
	}

	// SetUp GameCore
	if(FAILED(gGameCore::GetIF()->SetUp()))
	{
		MessageBox(m_hWnd, "GameCore : Setup ����", "Error", MB_OK);
		return false;
	}

	// SetUp Interface
	if(FAILED(gInterface::GetIF()->SetUp()))
	{
		MessageBox(m_hWnd, "Interface : Setup ����", "Error", MB_OK);
		return false;
	}

	// SetUp PopUp
	if(FAILED(gPopUp::GetIF()->SetUp()))
	{
		MessageBox(m_hWnd, "PopUp : Setup ����", "Error", MB_OK);
		return false;
	}


	// font ����  gUtil
	gUtil::SetSize(12);

	ShowWindow(m_hWnd, nCmdShow);

	return true;
}

void gMainWin::MoveWindow()
{
	SetRect(&m_rcScr, 0, 0, WNDSIZEW, WNDSIZEH);
	ClientToScreen(m_hWnd, (POINT*)&m_rcScr);
	ClientToScreen(m_hWnd, (POINT*)&m_rcScr + 1);
}

void gMainWin::Release()
{
	gMouse::GetIF()->Release();
	gInterface::GetIF()->Release();
	gGameCore::GetIF()->Release();
	gTitleCore::GetIF()->Release();
	gCharManager::GetIF()->Release();
	gPlayerManager::GetIF()->Release();
	tileContainer::GetIF()->Release();
	gPopUp::GetIF()->Release();
	SAFE_RELEASE(m_lpDDBack);
	SAFE_RELEASE(m_lpDDPrimary);
	SAFE_RELEASE(m_lpDD);
}


int gMainWin::Run()
{
	MSG		Msg;

	// Mainloop of game
	while(true)
	{
		// �޽��� ť�� �޽��� ������ ó��
		if(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			//ALT ����
			if(Msg.message == WM_SYSKEYDOWN) continue;
			if(Msg.message == WM_QUIT) break;
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else	// �޽��� ť�� �޽��� ���� ��
		{
			MainLoop();
		}
	}
	return Msg.wParam;
}

void gMainWin::MainLoop()
{
	switch(m_eCoreMode)
	{
		case EMC_TITLE:
			gTitleCore::GetIF()->MainLoop();
			break;
		case EMC_GAME:
			gGameCore::GetIF()->MainLoop();
			break;
	}
	// backbuffer �� �׷��� �͵��� ���
if(!m_bActive) return;
#ifdef FULLSCREEN
	m_lpDDPrimary->Flip(NULL, DDFLIP_WAIT);
#else
	m_lpDDPrimary->Blt(&m_rcScr, m_lpDDBack, NULL, DDBLT_WAIT, NULL);
#endif
}

//------------------------------------------------------------------------------------
// window message -; Ű����, ���콺
//------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	gMainWin	*mw = gMainWin::GetIF();
	gMouse		*mouse = gMouse::GetIF();
	switch(iMsg)
	{
#ifndef FULLSCREEN
		case WM_MOVE:
			mw->MoveWindow();
		break;
#endif
		// keyboard
		case WM_KEYDOWN:
			mw->m_Keys[wParam] = true;
			return 0;
		case WM_KEYUP:
			mw->m_Keys[wParam] = false;
			return 0;
		// mouse
		case WM_LBUTTONDOWN:
			mouse->m_nPosX = LOWORD(lParam);
			mouse->m_nPosY = HIWORD(lParam);
			mouse->OnLButtonDown();
			return 0;
		case WM_LBUTTONUP:
			mouse->m_nPosX = LOWORD(lParam);
			mouse->m_nPosY = HIWORD(lParam);
			mouse->OnLButtonUp();
			return 0;
		case WM_RBUTTONDOWN:
			mouse->m_nPosX = LOWORD(lParam);
			mouse->m_nPosY = HIWORD(lParam);
			mouse->OnRButtonDown();
			return 0;
		case WM_MOUSEMOVE:
			mouse->m_nPosX = LOWORD(lParam);
			mouse->m_nPosY = HIWORD(lParam);
			mouse->OnMouseMove();
			return 0;
		// active
		case WM_ACTIVATE:
			switch(LOWORD(wParam))
			{
				case WA_ACTIVE: case WA_CLICKACTIVE:
					gMainWin::GetIF()->m_bActive = true;
					break;
				case WA_INACTIVE:
					gMainWin::GetIF()->m_bActive = false;
					break;
			}
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}

void gMainWin::Exit()
{
	SendMessage(m_hWnd, WM_DESTROY, 0, 0);
}

bool gMainWin::SetUpDirect()
{
	if(FAILED(DirectDrawCreate(NULL, &m_lpDD, NULL)))
	{
		MessageBox(m_hWnd, "DirectDraw : Interface ���� ����", "Error", MB_OK);
		return false;
	}
#ifdef FULLSCREEN
	if(FAILED(m_lpDD->SetCooperativeLevel(m_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN)))
	{
		MessageBox(m_hWnd, "DirectDraw : Cooperative Level ���� ����", "Error", MB_OK);
		return false;
	}
	
	if(FAILED(m_lpDD->SetDisplayMode(WNDSIZEW, WNDSIZEH, BIT)))
	{
		MessageBox(m_hWnd, "DirectDraw : ���÷��� ���� ����", "Error", MB_OK);
		return false;
	}
	
	// Primary Buffer
	DDSURFACEDESC	ddsd;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC));
	ddsd.dwSize				= sizeof(DDSURFACEDESC);
	ddsd.dwFlags			= DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps		= DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_SYSTEMMEMORY;
	ddsd.dwBackBufferCount	= 1;
	
	if(FAILED(m_lpDD->CreateSurface(&ddsd, &m_lpDDPrimary, NULL)))
	{
		MessageBox(m_hWnd, "DirectDraw : Primary Surface ���� ����", "Error", MB_OK);
		return false;
	}
	
	// Backbuffer
	DDSCAPS		ddsCaps;
	memset(&ddsCaps, 0, sizeof(DDSCAPS));
	ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
	
	m_lpDDPrimary->GetAttachedSurface(&ddsCaps, &m_lpDDBack);
#else
	if(FAILED(m_lpDD->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL)))
	{
		MessageBox(m_hWnd, "DirectDraw : Cooperative Level ���� ����", "Error", MB_OK);
		return false;
	}
	
	// Primary Buffer
	DDSURFACEDESC	ddsd;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC));
	ddsd.dwSize			= sizeof(DDSURFACEDESC);
	ddsd.dwFlags		= DDSD_CAPS;
	ddsd.ddsCaps.dwCaps	= DDSCAPS_PRIMARYSURFACE;
	
	if(FAILED(m_lpDD->CreateSurface(&ddsd, &m_lpDDPrimary, NULL)))
	{
		MessageBox(m_hWnd, "DirectDraw : Primary Surface ���� ����", "Error", MB_OK);
		return false;
	}
	
	// Back Buffer
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize			= sizeof(ddsd);
	ddsd.dwFlags		= DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY; //DDSCAPS_VIDEOMEMORY
	ddsd.dwWidth		= WNDSIZEW;
	ddsd.dwHeight		= WNDSIZEH;
	
	if(FAILED(m_lpDD->CreateSurface(&ddsd, &m_lpDDBack, NULL)))
	{
		MessageBox(m_hWnd, "DirectDraw : BackBuffer Surface ���� ����", "Error", MB_OK);
		return false;
	}
#endif
	
	return true;
}