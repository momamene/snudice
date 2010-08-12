#include "MainWin.h"
#include <windows.h>

LPSTR lpszClass="server windows version";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	gMainWin	*main = gMainWin::GetIF();
	DWORD trashDWORD;
	
	if(!main->SetUp(hInstance, lpszCmdParam, nCmdShow))
	{
		return 0;
		//main->Exit();
		/*
		if(main->m_hWnd == NULL)
			return 0;
		else
		{
			main->Exit();
			return 0;
		}
		*/
	}

	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	//g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);

	RECT	rcWin = {0, 0, WNDSIZEW, WNDSIZEH};
	AdjustWindowRect(&rcWin, WNDSTYLE, false);
	SetWindowPos(hWnd, NULL, 0, 0,
		rcWin.right - rcWin.left, rcWin.bottom - rcWin.top,
		SWP_NOMOVE | SWP_NOZORDER);

	MoveWindow(hWnd,0,0,WNDSIZEW,WNDSIZEH,false);

//	main->MoveWindow();
	ShowWindow(hWnd, nCmdShow);

//	ShowWindow(hWnd,nCmdShow);
	
	// int		retValue; 
	// retValue = main->Run();

	HANDLE			hThread;
	DWORD			dwThreadID;
	hThread = CreateThread(NULL, 0, Run, &trashDWORD, 0, &dwThreadID);

	if(hThread == NULL) {
		OutputDebugString("Thread failed\n");
	}
	else {
		CloseHandle(hThread);
	
		while(GetMessage(&Message,0,0,0)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	main->Release();

	return Message.wParam;
	//return retValue;
	
}