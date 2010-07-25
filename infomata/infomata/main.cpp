#include "main.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
//HINSTANCE g_hInst;
LPSTR lpszClass="First";
gContainer container;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
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
	ShowWindow(hWnd,nCmdShow);
	
	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush,OldBrush;
	HBRUSH S8Brush[8];
	
	
	switch(iMessage) {
	case WM_CREATE:
		container.init();
		return 0;

	
	case WM_LBUTTONDOWN:
		container.LClick(LOWORD(lParam),HIWORD(lParam));
		InvalidateRect(hWnd,NULL,TRUE);
		return 0;

	case WM_RBUTTONDOWN:
		container.RClick();
		return 0;

	case WM_PAINT:
		RECT tempRC;
		hdc = BeginPaint(hWnd,&ps);
		
		for(int j = 0; j < none ; j++)
			S8Brush[j]=CreateSolidBrush(RGB(j*31,0,0));
		OldBrush=(HBRUSH)SelectObject(hdc,S8Brush[0]);
		for(int i = 0 ; i < DAILY ; i++) {
			for(int j = 0 ; j < none ; j++) {
				SelectObject(hdc,S8Brush[j]);
				tempRC = container.index_valueToRect(i,container.m_gstream[i].m_standardLoad[j]);
				Rectangle(hdc,tempRC.left,tempRC.top,tempRC.right,tempRC.bottom);
				//DeleteObject(S8Brush[0]);
			}
		}
		
		SelectObject(hdc,OldBrush);	

		EndPaint(hWnd,&ps);
		return 0;

	case WM_DESTROY:
		for(int j = 0 ; j < none ; j++)
			DeleteObject(S8Brush[j]);
		PostQuitMessage(0);
		return 0;

	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

