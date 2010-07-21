#include "main.h"
#include "Childs.h" // Childs ���� main header file
#include "left.h"

// �ϵ� �ڵ��� ����
int mode; // �̰� ���(new,edit)
TILE tempBmpKind;

// ������ �ڵ�
HWND hWndMain, hC1, hC2;
LPCTSTR lpszClass=TEXT("Map Tool");


// �ϵ� �ڵ��� ���� ������ ����


hSeries H;
//

HWND hMDlg;

XY befConPoint;
int eramoregetta;
Savor savor;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	static HBRUSH hRedBrush, hBlueBrush, hGreenBrush;

	// ������ �귯���� �̸��� �ٲ�ų� �������� �ʾƾ� ��
	hRedBrush=CreateSolidBrush(RGB(192,192,0));
	hGreenBrush=CreateSolidBrush(RGB(255,255,255));
//	hBlueBrush=CreateSolidBrush(RGB(0,0,255));

	// ���� ������ Ŭ����
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=NULL;
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	// ���� ���ϵ� Ŭ����
	WndClass.hbrBackground=hRedBrush;
	WndClass.lpfnWndProc=ChildLeftProc;
	WndClass.lpszClassName=TEXT("ChildLeft");
	RegisterClass(&WndClass);

	// ���� ���ϵ� Ŭ����
	WndClass.hbrBackground=hGreenBrush;
	WndClass.lpfnWndProc=ChildRightProc;
	WndClass.lpszClassName=TEXT("ChildRight");
	RegisterClass(&WndClass);

	// ���� ������ ����
	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	hWndMain=hWnd;
	
	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	DeleteObject(hRedBrush);
	DeleteObject(hBlueBrush);
//	DeleteObject(hGreenBrush);
	return (int)Message.wParam;
}

// ���� �������� �޽��� ���ν���
// plz 'return' unitification
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
		HANDLE hFile;
	DWORD dw;

	RECT crt;

	// findfile
	OPENFILENAME OFN;
	TCHAR lpstrFile[MAX_PATH]="";
	TCHAR szDefault[MAX_PATH];

	switch (iMessage) {
	case WM_CREATE:
		hC1=CreateWindow(TEXT("ChildLeft"),NULL,WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN 
			// n
			| WS_HSCROLL | WS_VSCROLL,
			// n
			0,0,0,0,hWnd,(HMENU)0,g_hInst,NULL);
		hC2=CreateWindow(TEXT("ChildRight"),NULL,WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			0,0,0,0,hWnd,(HMENU)0,g_hInst,NULL);
		if(!IsWindow(hMDlg)){
			hMDlg=CreateDialog(g_hInst,MAKEINTRESOURCE(IDD_DIALOG1),hWnd,AboutDlgProc);
			ShowWindow(hMDlg,SW_SHOW);
		}
		for(int i = 0 ; i < LINEX ; i++) {
			for (int j = 0; j <LINEY ; j++) {
				bmpKind[i][j].init(i,j);
		
			}
		}
		mode=1;
		tempBmpKind.tileType=TY_CLASS;
		//changed1=0;
		//changed2=0;
		//message=0;


			return 0;
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED) {
			
			//MoveWindow(hWnd,10,10,800,500,TRUE);
			GetClientRect(hWnd,&crt);
			MoveWindow(hC1,0,0,crt.right-200,crt.bottom,TRUE);
			MoveWindow(hC2,crt.right-200,0,200,crt.bottom, TRUE);
		}
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
//		case 2: (??)
//			GetWindowText(hEdit,str,256);
//			SendMessage(hList,LB_ADDSTRING,0,(LPARAM)str);


	
		case ID_FILE_SAVE40002:  // �������� ǥ���� �Ǿ�� ���ٵ�
				GetCurrentDirectory(MAX_PATH, szDefault);

			memset(&OFN,0,sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = TEXT("xy ����\0*.xy\0");
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile=MAX_PATH;
			OFN.lpstrDefExt		= "xy";
		//	OFN.lpfnHook		= HookProcCenterDialog;
			OFN.lpstrInitialDir	= szDefault;
			if(GetOpenFileName(&OFN)!=0) {

				hFile=CreateFile(lpstrFile,GENERIC_WRITE,0,NULL,
					CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
				savor.Save();
				WriteFile(hFile,&savor.count,sizeof(int),&dw,NULL);
				for(int i = 0 ; i < savor.count ; i++)
					WriteFile(hFile,&savor.bmpKindSavor[i],sizeof(TILE),&dw,NULL);
				//for(int i = 0 ; i < LINEX ; i++)
				//	ReadFile(hFile,bmpKind[i],sizeof(TILE)*LINEY,&dw,NULL);

				CloseHandle(hFile);
			}
			else {}
//			WriteFile(hFile,bmpKind,((sizeof)int*LINEX*LINEY),&dw);
			break;

		case ID_FILE_LOAD:
			GetCurrentDirectory(MAX_PATH, szDefault);

			memset(&OFN,0,sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = TEXT("xy ����\0*.xy\0");
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile=MAX_PATH;
			OFN.lpstrDefExt		= "xy";
		//	OFN.lpfnHook		= HookProcCenterDialog;
			OFN.lpstrInitialDir	= szDefault;
			if(GetOpenFileName(&OFN)!=0) {

				hFile=CreateFile(lpstrFile,GENERIC_READ,0,NULL,
					OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
				if(hFile!=INVALID_HANDLE_VALUE) {
					memset(&savor,0,sizeof(savor));
					ReadFile(hFile,&savor.count,sizeof(int),&dw,NULL);
					for(int i = 0 ; i < savor.count ; i++)
						ReadFile(hFile,&savor.bmpKindSavor[i],sizeof(TILE),&dw,NULL); // �̷� ����...
					savor.Load();
					//for(int i = 0 ; i < LINEX ; i++)
					//	ReadFile(hFile,bmpKind[i],sizeof(TILE)*LINEY,&dw,NULL);
					CloseHandle(hFile);
					InvalidateRect(hWnd,NULL,TRUE); // â�� �ٸ��� �� �Ǵ��� ����� ������ ������ �� ����
				}
			else {}
			break;
			}
		}
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

BOOL CALLBACK AboutDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	// Dlg ������ ���� �ʿ�

	HDC				hdc;
	PAINTSTRUCT		ps;

	switch (iMessage) {
	case WM_INITDIALOG:
		SetTimer(hDlg,1,500,NULL);
		return TRUE;
	case WM_TIMER:
		InvalidateRect(hDlg,NULL,TRUE);
		if(minimap) ShowWindow(hDlg,1);
		else ShowWindow(hDlg,0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		/*
		case IDOK:
			EndDialog(hDlg,IDOK);
			return TRUE;
			*/
		case IDCANCEL:
			//EndDialog(hDlg,IDCANCEL);
			minimap=0;
			SendMessage(H.hButton[1],BM_SETCHECK,BST_UNCHECKED,0);
			ShowWindow(hDlg,FALSE);
			return TRUE;
		}
		break;
	case WM_PAINT:
		int n = 10;
		hdc = BeginPaint(hDlg, &ps);
		for(int i = 0 ; i < LINEX ; i++) {
			for(int j = 0 ; j < LINEY ; j++) { 
				if(bmpKind[i][j].tileType==TY_CLASS) {
					if(i%2==0)	DrawBitmap(hdc,WIDEX*i/2/n,FULLY*j/n,MyBitmap[0],n);
					else	DrawBitmap(hdc,LEFTX/n+MIDDLEX/n+WIDEX*(i-1)/2/n,HALFY/n+FULLY*j/n,MyBitmap[0],n);
				}
				else if (bmpKind[i][j].tileType==TY_ITEM) {
					if(i%2==0)	DrawBitmap(hdc,WIDEX*i/2/n,FULLY*j/n,MyBitmap[1],n);
					else	DrawBitmap(hdc,LEFTX/n+MIDDLEX/n+WIDEX*(i-1)/2/n,HALFY/n+FULLY*j/n,MyBitmap[1],n);
				}
				else if (bmpKind[i][j].tileType==TY_STAMINA) {
					if(i%2==0)	DrawBitmap(hdc,WIDEX*i/2/n,FULLY*j/n,MyBitmap[2],n);
					else	DrawBitmap(hdc,LEFTX/n+MIDDLEX/n+WIDEX*(i-1)/2/n,HALFY/n+FULLY*j/n,MyBitmap[2],n);
				}
				else if (bmpKind[i][j].tileType==TY_BUS) {
					if(i%2==0)	DrawBitmap(hdc,WIDEX*i/2/n,FULLY*j/n,MyBitmap[3],n);
					else	DrawBitmap(hdc,LEFTX/n+MIDDLEX/n+WIDEX*(i-1)/2/n,HALFY/n+FULLY*j/n,MyBitmap[3],n);
				}
				else if (bmpKind[i][j].tileType==TY_MAINGATE) {
					if(i%2==0)	DrawBitmap(hdc,WIDEX*i/2/n,FULLY*j/n,MyBitmap[4],n);
					else	DrawBitmap(hdc,LEFTX/n+MIDDLEX/n+WIDEX*(i-1)/2/n,HALFY/n+FULLY*j/n,MyBitmap[4],n);
				}
			}
		}
		//char  buf[1000];
		//wsprintf(buf, "%d %d %d %d",nowConPoint.x,nowConPoint.y,mode,bmpKind[2][3].ptPos.x);
		//TextOut(hdc, 0, 0, buf, strlen(buf));

		EndPaint(hDlg, &ps);	
		/* //�ƴ� �׳� KillTimer �� �߿����� ������? ������ ���ؼ��� �ϴ�
	case WM_DESTROY:
		KillTimer(hDlg,1);
		PostQuitMessage(0);
		return 0;
		*/
	}
	return FALSE;
}

		RECT			crt2;
		XY ttemp1,ttemp2;	


// ���� ���ϵ��� �޽��� ���ν���
LRESULT CALLBACK ChildLeftProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static HWND hList, hEdit,hBtn;
	TCHAR str[256];

	HDC				hdc;
	PAINTSTRUCT		ps;

	// ȭ�� ���������� �Ѹ��� �׹���

	switch (iMessage) {
	case WM_CREATE:
		// n
		xPos=0;
		yPos=0;
		// n


		MyBitmap[0]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1));
		MyBitmap[1]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP2));
		MyBitmap[2]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP3));
		MyBitmap[3]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP4));
		MyBitmap[4]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP5));
		
		memset(bmpKind,0,sizeof(int)*LINEX*LINEY);
		tempBmpKind.init(-1,-1);
		tempBmpKind.tileType = TY_CLASS;
		nowPoint.put(0,0);
		

		return 0;
	case WM_SIZE:
		// �� ���⼱ �ǰ� ���⼱ �ȵɱ�?
		// ���������� xMax�� ���� ������ �ִ� ���� ������ �ڸ����� �׷���..(MIDDLEX���� ��)
		xMax=(LINEX/2+LINEX%2)*WIDEX-LOWORD(lParam)-MIDDLEX; 
		yMax=LINEY*FULLY-HIWORD(lParam)+HALFY;
		SetScrollRange(hWnd,SB_VERT,0,yMax,TRUE);
		SetScrollPos(hWnd,SB_VERT,0,TRUE);
		SetScrollRange(hWnd,SB_HORZ,0,xMax,TRUE);
		SetScrollPos(hWnd,SB_HORZ,0,TRUE);

	//	MoveWindow(hList,10,10,190,HIWORD(lParam)-20,TRUE);
/*
		SCROLLINFO si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL| SIF_DISABLENOSCROLL;
		si.nMin =0;
		si.nMax = yMax;
		si.nPage=HIWORD(lParam);
		si.nPos = yPos;
		SetScrollInfo(hWnd,SB_VERT,&si,TRUE);

		si.nMax=xMax;
		si.nPage=LOWORD(lParam);
		si.nPos=xPos;
		SetScrollInfo(hWnd,SB_HORZ,&si,TRUE);
*/		
		return 0;

	case WM_LBUTTONDOWN:

//		nowConPoint.put(nowConPoint.absToCon(nowConPoint.put(LOWORD(lParam),HIWORD(lParam))));
		nowPoint.put(xPos+LOWORD(lParam),yPos+HIWORD(lParam));
		nowConPoint.putCon(xPos+LOWORD(lParam),yPos+HIWORD(lParam));
				// ���ٷ� �ٱ�� ������ ���� �Լ��� ����� �Ǿ���.
		if(mode==1){
			befConPoint = H.bfAI(befConPoint,nowConPoint);
			bmpKind[nowConPoint.x][nowConPoint.y].tileType = tempBmpKind.tileType;
			H.hEditChanger(bmpKind[nowConPoint.x][nowConPoint.y]);
			// �ϴ� Ÿ�ϸ� ��������
			InvalidateRect(hWnd,NULL,TRUE);
		}
		else if(mode==2){ // �� ����. Ÿ�̸ӷ� ������ �����ؾ� �ϳ�. �� �ذ�!
			H.hEditChanger(bmpKind[nowConPoint.x][nowConPoint.y]);
			InvalidateRect(hC2,NULL,TRUE);
		} 
		return 0;

	case WM_RBUTTONDOWN:
		hahaha(hWnd);



	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		
		GetClientRect(hWnd,&crt2);
	
		//int starti,endi,startj,endj;

		crt2.left = crt2.left + xPos;
		crt2.top = crt2.top + yPos;
		crt2.right = crt2.right + xPos;
		crt2.bottom = crt2.bottom + yPos;
		
		//ttemp1.x = crt2.left;
		//ttemp1.y = crt2.top;
		ttemp1.putCon(crt2.left,crt2.top);
		ttemp2.putCon(crt2.right,crt2.bottom);
		//ttemp2 = {crt2.right,crt2.bottom};
		//ttemp2.absToCon();

		if(ttemp1.x>=1) ttemp1.x--;
		else ttemp1.x=0;
		if(ttemp1.y>=1) ttemp1.y--;
		else ttemp1.y=0;
		if(ttemp2.x<=LINEX) ttemp2.x++;
		else ttemp2.x=LINEX;		
		if(ttemp2.y<=LINEY) ttemp2.y++;
		else ttemp2.y=LINEY;
		char  buf[1000];
		for(int i = ttemp1.x ; i < ttemp2.x ; i++) {
			for(int j = ttemp1.y ; j < ttemp2.y ; j++) {
				wsprintf(buf,"%d %d",i,j);
				if(bmpKind[i][j].tileType==TY_CLASS) {
					if(i%2==0){						
						DrawBitmap(hdc,-xPos+WIDEX*i/2,-yPos+FULLY*j,MyBitmap[0]);
						
					}
					else DrawBitmap(hdc,-xPos+LEFTX+MIDDLEX+WIDEX*(i-1)/2,-yPos+HALFY+FULLY*j,MyBitmap[0]);
				}
				else if (bmpKind[i][j].tileType==TY_ITEM) {
					if(i%2==0)	DrawBitmap(hdc,-xPos+WIDEX*i/2,-yPos+FULLY*j,MyBitmap[1]);
					else	DrawBitmap(hdc,-xPos+LEFTX+MIDDLEX+WIDEX*(i-1)/2,-yPos+HALFY+FULLY*j,MyBitmap[1]);
				}
				else if (bmpKind[i][j].tileType==TY_STAMINA) {
					if(i%2==0)	DrawBitmap(hdc,-xPos+WIDEX*i/2,-yPos+FULLY*j,MyBitmap[2]);
					else	DrawBitmap(hdc,-xPos+LEFTX+MIDDLEX+WIDEX*(i-1)/2,-yPos+HALFY+FULLY*j,MyBitmap[2]);
				}
				else if (bmpKind[i][j].tileType==TY_BUS) {
					if(i%2==0)	DrawBitmap(hdc,-xPos+WIDEX*i/2,-yPos+FULLY*j,MyBitmap[3]);
					else	DrawBitmap(hdc,-xPos+LEFTX+MIDDLEX+WIDEX*(i-1)/2,-yPos+HALFY+FULLY*j,MyBitmap[3]);
				}
				else if (bmpKind[i][j].tileType==TY_MAINGATE) {
					if(i%2==0)	DrawBitmap(hdc,-xPos+WIDEX*i/2,-yPos+FULLY*j,MyBitmap[4]);
					else	DrawBitmap(hdc,-xPos+LEFTX+MIDDLEX+WIDEX*(i-1)/2,-yPos+HALFY+FULLY*j,MyBitmap[4]);
				}
				else{
					continue;
				}
				if(i%2==0){
				TextOut(hdc,-xPos+WIDEX*i/2+LEFTX,-yPos+FULLY*j,buf,strlen(buf));
				TextOut(hdc,-xPos+WIDEX*i/2+LEFTX,-yPos+FULLY*j+20,bmpKind[i][j].college,strlen(bmpKind[i][j].college));
				TextOut(hdc,-xPos+WIDEX*i/2+LEFTX,-yPos+FULLY*j+40,bmpKind[i][j].building,strlen(bmpKind[i][j].building));
				TextOut(hdc,-xPos+WIDEX*i/2+LEFTX,-yPos+FULLY*j+60,bmpKind[i][j].subject,strlen(bmpKind[i][j].subject));
				}
				if(i%2==1){
				TextOut(hdc,-xPos+WIDEX*i/2+LEFTX,-yPos+FULLY*j+HALFY,buf,strlen(buf));
				TextOut(hdc,-xPos+WIDEX*i/2+LEFTX,-yPos+FULLY*j+HALFY+20,bmpKind[i][j].college,strlen(bmpKind[i][j].college));
				TextOut(hdc,-xPos+WIDEX*i/2+LEFTX,-yPos+FULLY*j+HALFY+40,bmpKind[i][j].building,strlen(bmpKind[i][j].building));
				TextOut(hdc,-xPos+WIDEX*i/2+LEFTX,-yPos+FULLY*j+HALFY+60,bmpKind[i][j].subject,strlen(bmpKind[i][j].subject));
				}
			}
		}
		
		wsprintf(buf, "%d %d %d %d %d %d",nowConPoint.x,nowConPoint.y,ttemp1.x,ttemp1.y,ttemp2.x,ttemp2.y);
//		wsprintf(buf, "%d %d %d %d %d %d",nowConPoint.x,nowConPoint.y,crt2.left,crt2.top,crt2.right,crt2.bottom);

		TextOut(hdc, 0, 0, buf, strlen(buf));

		EndPaint(hWnd, &ps);	
		//SendMessage(hMDlg,WM_PAINT,0,0);

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 2:
			GetWindowText(hEdit,str,256);
			SendMessage(hList,LB_ADDSTRING,0,(LPARAM)str);
			
		}
		return 0;

	// n
	case WM_HSCROLL:
		xInc = 0;
		switch(LOWORD(wParam)){
		case SB_LINELEFT:
			xInc=-1;
			break;
		case SB_LINERIGHT:
			xInc=1;
			break;
		case SB_PAGELEFT:
			xInc=-20;
			break;
		case SB_PAGERIGHT:
			xInc=20;
			break;
		case SB_THUMBTRACK:
			xInc=HIWORD(wParam)-xPos;
			break;
		}
		if(xPos+xInc < 0 ) 
			xInc = -xPos;
		if(xPos+xInc > xMax)
			xInc = xMax-xPos;

		xPos=xPos+xInc;
		ScrollWindow(hWnd,-xInc,0,NULL,NULL);
		SetScrollPos(hWnd,SB_HORZ,xPos,TRUE);
				InvalidateRect(hWnd,NULL,TRUE);

		return 0;

	
	case WM_VSCROLL:
		yInc = 0;
		switch(LOWORD(wParam)){
		case SB_LINELEFT:
			yInc=-1;
			break;
		case SB_LINERIGHT:
			yInc=1;
			break;
		case SB_PAGELEFT:
			yInc=-20;
			break;
		case SB_PAGERIGHT:
			yInc=20;
			break;
		case SB_THUMBTRACK:
			yInc=HIWORD(wParam)-yPos;
			break;
		}
		if(yPos+yInc < 0 ) 
			yInc = -yPos;
		if(yPos+yInc > yMax)
			yInc = yMax-yPos;

		yPos=yPos+yInc;
		ScrollWindow(hWnd,0,-yInc,NULL,NULL);
		SetScrollPos(hWnd,SB_VERT,yPos,TRUE);
				InvalidateRect(hWnd,NULL,TRUE);

		return 0;

	}

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}


// ������ ���ϵ��� �޽��� ���ν���
LRESULT CALLBACK ChildRightProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HWND hbutton;

	int i;
	TCHAR str[128];
	TCHAR *Itmes[]={TEXT("CLASS"),TEXT("ITEM"),TEXT("STAMINA"),TEXT("BUS"),TEXT("MAINGATE"),TEXT("ERASE")};
	
	switch (iMessage) {
	case WM_CREATE:
		// Create�� �Լ���.
		
		hbutton=CreateWindow(TEXT("button"),TEXT("New"),WS_CHILD | WS_VISIBLE | 
			BS_AUTORADIOBUTTON | WS_GROUP,
			10,10,80,30,hWnd,(HMENU)101,g_hInst,NULL);
		SendMessage(hbutton,BM_SETCHECK,1,0);
		CreateWindow(TEXT("button"),TEXT("Edit"),WS_CHILD | WS_VISIBLE | 
			BS_AUTORADIOBUTTON,
			100,10,80,30,hWnd,(HMENU)102,g_hInst,NULL);

		H.hCombo = CreateWindow(TEXT("combobox"),NULL,WS_CHILD|WS_VISIBLE|
			CBS_DROPDOWNLIST,10,140,100,200,hWnd,(HMENU)100,g_hInst,NULL);
		for(i=0;i<6;i++) 
			SendMessage(H.hCombo,CB_ADDSTRING,0,(LPARAM)Itmes[i]);
			SendMessage(H.hCombo,CB_SETCURSEL,0,0);
		//CreateWindow(TEXT("static"),"������ǥ",WS_CHILD |WS_VISIBLE,10,170,100,25,
		//	hWnd,(HMENU)-1,g_hInst,NULL);
		H.hEdit[0] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_READONLY|
			ES_AUTOHSCROLL,10,190,80,20,hWnd,(HMENU)110,g_hInst,NULL);
		H.hEdit[1] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_READONLY|
			ES_AUTOHSCROLL,100,190,80,20,hWnd,(HMENU)111,g_hInst,NULL);
		
		H.hEdit[2] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_NUMBER|
			ES_AUTOHSCROLL,10,230,80,20,hWnd,(HMENU)112,g_hInst,NULL);
		H.hEdit[3] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_NUMBER|
			ES_AUTOHSCROLL,100,230,80,20,hWnd,(HMENU)113,g_hInst,NULL);
		H.hEdit[4] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_NUMBER|
			ES_AUTOHSCROLL,10,270,80,20,hWnd,(HMENU)114,g_hInst,NULL);
		H.hEdit[5] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_NUMBER|
			ES_AUTOHSCROLL,100,270,80,20,hWnd,(HMENU)115,g_hInst,NULL);
		H.hEdit[6] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_NUMBER|
			ES_AUTOHSCROLL,100,290,80,20,hWnd,(HMENU)116,g_hInst,NULL);
		H.hEdit[7] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_NUMBER|
			ES_AUTOHSCROLL,100,310,80,20,hWnd,(HMENU)117,g_hInst,NULL);
		H.hButton[0] = CreateWindow(TEXT("button"),"prev-next",WS_CHILD|WS_VISIBLE|BS_CHECKBOX,
			10,330,100,25,hWnd,(HMENU)130,g_hInst,NULL);
		H.hButton[1] = CreateWindow(TEXT("button"),"Minimap",WS_CHILD|WS_VISIBLE|BS_CHECKBOX,
			10,350,100,25,hWnd,(HMENU)131,g_hInst,NULL);

		H.hEdit[8] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|
			ES_AUTOHSCROLL,80,370,100,20,hWnd,(HMENU)118,g_hInst,NULL);
		H.hEdit[9] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|
			ES_AUTOHSCROLL,80,390,100,20,hWnd,(HMENU)119,g_hInst,NULL);
		H.hEdit[10] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|
			ES_AUTOHSCROLL,80,410,100,20,hWnd,(HMENU)120,g_hInst,NULL);



		prev_next = 0;
		minimap = 0;

		return 0;

	case WM_COMMAND:
		H.caseProcessor(LOWORD(wParam),HIWORD(wParam)); // �Ѵ� wParam�̾�?!
		InvalidateRect(hWnd,NULL,TRUE);
		return 0;

	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		// �����ϴ�. �׷���, static�� �׷��� ���� ������ �ƴ϶�� ������ ��.. �ٵ� �������
		TextOut(hdc,10,170,"���� ��ǥ",strlen("���� ��ǥ"));
		TextOut(hdc,10,210,"���� ��ǥ",strlen("���� ��ǥ"));
		TextOut(hdc,10,250,"���� ��ǥ",strlen("���� ��ǥ"));
		TextOut(hdc,10,290,"flag1",strlen("flag1"));
		TextOut(hdc,10,310,"flag2",strlen("flag2"));
		TextOut(hdc,10,370,"college",strlen("college"));
		TextOut(hdc,10,390,"building",strlen("building"));
		TextOut(hdc,10,410,"subject",strlen("subject"));

		//TextOut(hdc,10,330,"prev-next",strlen("prev-next"));
		//TextOut(hdc,10,350,"Minimap",strlen("Minimap"));

		//				wsprintf(str,"h %d",j);
		//		TextOut(hdc, 100, 290, str, strlen(str));
		//DrawBitmap(hdc,10,50,MyBitmap[0]);
		EndPaint(hWnd, &ps);
		return 0;

	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
