#include "MainWin.h"
#include "const.h"
#include "Mouse.h"
#include "Dice.h"
#include "LoginCore.h"
#include "BattleNetCore.h"
#include "SubmitCore.h"
#include "GameCore.h"
#include "RoomCore.h"
#include "Server.h"
#include "Util.h"
#include "PopUp.h"
#include "Chat.h"
#include "ChannelUI.h"
#include "TopUI.h"
#include "PlayerContainer.h"
#include "ItemContainer.h"
#include "Map.h"
#include "UIGame.h"
#include "networkconst.h"
#include "resource.h"

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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

bool gMainWin::SetUp(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	// Initialize
	memset(this, 0, sizeof(gMainWin));

	char	szBuf[128];
	wsprintf(szBuf, "%s Ver %s", GAMENAME, SNUDICE_VERSION);
	
	m_hInst	= hInstance;
	// Make Window
	WNDCLASS	WndClass;
	memset(&WndClass, 0, sizeof(WNDCLASS));
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance		= hInstance;
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;
	WndClass.lpszClassName	= szBuf;
	WndClass.lpszMenuName	= NULL;
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	ShowCursor(FALSE);

#ifdef FULLSCREEN
	m_hWnd = CreateWindow(szBuf, szBuf, WS_POPUP, 
						CW_USEDEFAULT, CW_USEDEFAULT, WNDSIZEW, WNDSIZEH,
						NULL, (HMENU)NULL, hInstance, NULL);
#else
	m_hWnd = CreateWindow(szBuf, szBuf, WNDSTYLE, 
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

	if(!SetUpDirect())
		return false;

	if(!gMouse::GetIF()->SetUp())
		return false;

	if(!gMap::GetIF()->Setup())
		return false;

	if(!gItemContainer::GetIF()->SetUp())
		return false;

	if(!m_ImgBack.Load(BACKBUFFERIMG))
		return false;

	if(!gPopUp::GetIF()->SetUp())
		return false;

	if(!gLoginCore::GetIF()->SetUp())
		return false;

	if(!gBattleNetCore::GetIF()->SetUp())
		return false;

	if(!gSubmitCore::GetIF()->SetUp())
		return false;

	if(!gTopUI::GetIF()->SetUp())
		return false;

	if(!gRoomCore::GetIF()->SetUp())
		return false;

	if(!gGameCore::GetIF()->SetUp())
		return false;

	if(!gChat::GetIF()->SetUp())
		return false;

	if(!gPlayerContainer::GetIF()->SetUp())
		return false;

	if(!gServer::GetIF()->SetUp())
		return false;

	if(!gDice::GetIF()->SetUp())
		return false;

	if(!gUIGame::GetIF()->SetUp())
		return false;

	ShowWindow(m_hWnd, nCmdShow);

	if(!DisableBeep())
		return false;

	// Set Coremode

	m_eCoreMode = ECM_LOGIN;

	srand(NULL);

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
	m_ImgBack.Release();
	gServer::GetIF()->Release();
	gPopUp::GetIF()->Release();
	gMouse::GetIF()->Release();
	gLoginCore::GetIF()->Release();
	gBattleNetCore::GetIF()->Release();
	gRoomCore::GetIF()->Release();
	gSubmitCore::GetIF()->Release();
	gGameCore::GetIF()->Release();
	gPlayerContainer::GetIF()->Release();
	gTopUI::GetIF()->Release();
	gDice::GetIF()->Release();
	gUIGame::GetIF()->Release();
	gItemContainer::GetIF()->Release();
	SAFE_RELEASE(m_lpDDBack);
	SAFE_RELEASE(m_lpDDPrimary);
	SAFE_RELEASE(m_lpDD);
	EnableBeep();
}


int gMainWin::Run()
{
	MSG		Msg;

	// Mainloop of game
	while(true)
	{
		// 메시지 큐에 메시지 있으면 처리
		if(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			// ALT 막기
			if(Msg.message == WM_SYSKEYDOWN)
				continue;
			if(Msg.message == WM_QUIT)
				break;

			switch(m_eCoreMode)
			{
				case ECM_LOGIN:
					if(gLoginCore::GetIF()->PreTransMsg(Msg))
						continue;
					break;
				case ECM_BATTLENET:
					if(gBattleNetCore::GetIF()->PreTransMsg(Msg))
						continue;
					break;
				case ECM_ROOMMAKE: case ECM_ROOMJOIN: case ECM_ROOM:
					if(gRoomCore::GetIF()->PreTransMsg(Msg))
						continue;
					break;
				case ECM_SUBMIT:
					break;
				case ECM_GAME:
					if(gGameCore::GetIF()->PreTransMsg(Msg))
						continue;
					break;
			}

			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else	// 메시지 큐에 메시지 없을 때
		{
			MainLoop();
		}
	}
	return Msg.wParam;
}

void gMainWin::MainLoop()
{
	//if(!m_bActive)
	//	return;

	m_ImgBack.Draw();

	switch(m_eCoreMode)
	{
		case ECM_LOGIN:
			gLoginCore::GetIF()->MainLoop();
			break;
		case ECM_BATTLENET:
			gBattleNetCore::GetIF()->MainLoop();
			break;
		case ECM_ROOMMAKE: case ECM_ROOMJOIN: case ECM_ROOM:
			gRoomCore::GetIF()->MainLoop();
			break;
		case ECM_SUBMIT:
			gSubmitCore::GetIF()->MainLoop();
			break;
		case ECM_GAME:
			gGameCore::GetIF()->MainLoop();
			break;
	}
	gMouse::GetIF()->MainLoop();

	// backbuffer 에 그려진 것들을 출력
#ifdef FULLSCREEN
	m_lpDDPrimary->Flip(NULL, DDFLIP_WAIT);
#else
	m_lpDDPrimary->Blt(&m_rcScr, m_lpDDBack, NULL, DDBLT_WAIT, NULL);
#endif
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	gMainWin	*mw		= gMainWin::GetIF();
	gMouse		*mouse	= gMouse::GetIF();

	switch(iMsg)
	{
#ifndef FULLSCREEN
		case WM_MOVE:
			mw->MoveWindow();
		break;
#endif
		// keyboard
		case WM_KEYDOWN:
			if(!mw->m_bActive)
				return 0;

			mw->m_Keys[wParam] = true;
			return 0;
		case WM_KEYUP:
			if(!mw->m_bActive)
				return 0;

			mw->m_Keys[wParam] = false;
			return 0;

		// mouse
		case WM_LBUTTONDOWN:
			if(!mw->m_bActive)
				return 0;

			mouse->m_nPosX = LOWORD(lParam);
			mouse->m_nPosY = HIWORD(lParam);
			mouse->OnLButtonDown();
			return 0;
		case WM_LBUTTONUP:
			if(!mw->m_bActive)
				return 0;

			mouse->m_nPosX = LOWORD(lParam);
			mouse->m_nPosY = HIWORD(lParam);
			mouse->OnLButtonUp();
			return 0;
		case WM_RBUTTONDOWN:
			if(!mw->m_bActive)
				return 0;

			mouse->m_nPosX = LOWORD(lParam);
			mouse->m_nPosY = HIWORD(lParam);
			mouse->OnRButtonDown();
			return 0;
		case WM_MOUSEMOVE:
			mouse->m_nPosX = LOWORD(lParam);
			mouse->m_nPosY = HIWORD(lParam);

			if(!mw->m_bActive)
				return 0;

			mouse->OnMouseMove();
			return 0;

		// active
		case WM_ACTIVATE:
			switch(LOWORD(wParam))
			{
				case WA_ACTIVE: case WA_CLICKACTIVE:
					mw->m_bActive = true;
					ShowCursor(FALSE);
					break;
				case WA_INACTIVE:
					mw->m_bActive = false;
					ShowCursor(TRUE);
					break;
			}
			return 0;

		// network
		case WM_SOCKET:
			gServer::GetIF()->Receive(lParam);
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
		MessageBox(m_hWnd, "DirectDraw : Interface 생성 실패", "Error", MB_OK);
		return false;
	}
#ifdef FULLSCREEN
	if(FAILED(m_lpDD->SetCooperativeLevel(m_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN)))
	{
		MessageBox(m_hWnd, "DirectDraw : Cooperative Level 설정 실패", "Error", MB_OK);
		return false;
	}
	
	if(FAILED(m_lpDD->SetDisplayMode(WNDSIZEW, WNDSIZEH, BIT)))
	{
		MessageBox(m_hWnd, "DirectDraw : 디스플레이 변경 실패", "Error", MB_OK);
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
		MessageBox(m_hWnd, "DirectDraw : Primary Surface 생성 실패", "Error", MB_OK);
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
		MessageBox(m_hWnd, "DirectDraw : Cooperative Level 설정 실패", "Error", MB_OK);
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
		MessageBox(m_hWnd, "DirectDraw : Primary Surface 생성 실패", "Error", MB_OK);
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
		MessageBox(m_hWnd, "DirectDraw : BackBuffer Surface 생성 실패", "Error", MB_OK);
		return false;
	}
#endif

	// Create the clipper using the DirectDraw object 

	LPDIRECTDRAWCLIPPER		lpDDClipper;
	m_lpDD->CreateClipper(0, &lpDDClipper, NULL); 

	// Assign your window's HWND to the clipper 
	lpDDClipper->SetHWnd(0, m_hWnd); 

	// Attach the clipper to the primary surface 
	m_lpDDPrimary->SetClipper(lpDDClipper); 
	
	return true;
}

bool gMainWin::DisableBeep()
{
	// sound beep음 해제		- Registry 이용.
	HKEY		key;
	DWORD		dwDisp;
	
	if(RegCreateKeyEx(HKEY_CURRENT_USER, BEEPHACKREG, 0, NULL,
		REG_OPTION_VOLATILE, KEY_WRITE, NULL, &key, &dwDisp) != ERROR_SUCCESS)
		return false;
	
	if(RegSetValueEx(key, "Beep", 0, REG_SZ, (LPBYTE)"no", 3) != ERROR_SUCCESS)
		return false;
	
	RegCloseKey(key);
	
	// sound beep음... edit control 이넘이더라.
	// %SystemRoot%\media\Windows XP Ding.wav
	
	if(RegCreateKeyEx(HKEY_CURRENT_USER, BEEPHACKREG2, 0, NULL,
		REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &dwDisp) != ERROR_SUCCESS)
		return false;
	
	dwDisp = 128;
	
	if(RegQueryValueEx(key, NULL, 0, NULL, 
		(LPBYTE)m_szTempReg, &dwDisp) != ERROR_SUCCESS)
		return false;
	
	RegCloseKey(key);
	
	if(RegCreateKeyEx(HKEY_CURRENT_USER, BEEPHACKREG2, 0, NULL,
		REG_OPTION_VOLATILE, KEY_WRITE, NULL, &key, &dwDisp) != ERROR_SUCCESS)
		return false;
	
	if(RegSetValueEx(key, NULL, 0, REG_EXPAND_SZ, (LPBYTE)"", 1) != ERROR_SUCCESS)
		return false;
	
	RegCloseKey(key);

	return true;
}

bool gMainWin::EnableBeep()
{
	// sound beep음 해제 복구	- Registry 이용.
	HKEY		key;
	DWORD		dwDisp;
	
	if(RegCreateKeyEx(HKEY_CURRENT_USER, BEEPHACKREG, 0, NULL,
		REG_OPTION_VOLATILE, KEY_WRITE, NULL, &key, &dwDisp) != ERROR_SUCCESS)
		return false;
	
	if(RegSetValueEx(key, "Beep", 0, REG_SZ, (LPBYTE)"yes", 4) != ERROR_SUCCESS)
		return false;
	
	RegCloseKey(key);
	
	if(RegCreateKeyEx(HKEY_CURRENT_USER, BEEPHACKREG2, 0, NULL,
		REG_OPTION_VOLATILE, KEY_WRITE, NULL, &key, &dwDisp) != ERROR_SUCCESS)
		return false;
	
	if(RegSetValueEx(key, "", 0, REG_EXPAND_SZ, (LPBYTE)m_szTempReg, strlen(m_szTempReg) + 1) != ERROR_SUCCESS)
		return false;
	
	RegCloseKey(key);

	return true;
}