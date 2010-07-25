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
	
	
	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		POINT tempPT;
		int index;

		tempPT.x = LOWORD(lParam);
		tempPT.y = HIWORD(lParam);
		index = container.absToIndex(tempPT);
		container.m_gstream[index].m_st_standardLoad++;
		InvalidateRect(hWnd,NULL,TRUE);
		return 0;

	case WM_PAINT:
		RECT tempRC;

		hdc = BeginPaint(hWnd,&ps);
			
			MyBrush=CreateSolidBrush(RGB(255,0,0));
			OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
		
		for(int i = 0 ; i < DAILY ; i++) {
			tempRC = container.index_valueToRect(i,container.m_gstream[i].m_st_standardLoad);
			Rectangle(hdc,tempRC.left,tempRC.top,tempRC.right,tempRC.bottom);
		}
		
		SelectObject(hdc,OldBrush);	

		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

