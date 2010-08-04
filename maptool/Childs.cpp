#include "main.h"
#include "Childs.h" // Childs 전용 main header file
#include "left.h"

// 하드 코딩의 절정
int mode; // 이건 모드(new,edit)
TILE tempBmpKind;

// 윈도우 핸들
HWND hWndMain, hC1, hC2;
LPCTSTR lpszClass=TEXT("Map Tool");


// 하드 코딩의 절정 오른쪽 인자


hSeries H;
//

HWND hMDlg;

XY befConPoint;
int eramoregetta;
Savor savor;
SavorPREV savorprev;
void shift (int x,int y);
void savorshiftor();

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	static HBRUSH hRedBrush, hBlueBrush, hGreenBrush;

	// 이제는 브러쉬의 이름이 바뀌거나 존재하지 않아야 함
	hRedBrush=CreateSolidBrush(RGB(192,192,0));
	hGreenBrush=CreateSolidBrush(RGB(255,255,255));
//	hBlueBrush=CreateSolidBrush(RGB(0,0,255));

	// 메인 윈도우 클래스
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

	// 왼쪽 차일드 클래스
	WndClass.hbrBackground=hRedBrush;
	WndClass.lpfnWndProc=ChildLeftProc;
	WndClass.lpszClassName=TEXT("ChildLeft");
	RegisterClass(&WndClass);

	// 위쪽 차일드 클래스
	WndClass.hbrBackground=hGreenBrush;
	WndClass.lpfnWndProc=ChildRightProc;
	WndClass.lpszClassName=TEXT("ChildRight");
	RegisterClass(&WndClass);

	// 메인 윈도우 생성
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

// 메인 윈도우의 메시지 프로시저
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
		tempBmpKind.tileType=(ETILETYPE)0;
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


	
		case ID_FILE_SAVE40002:  // 저장으로 표현이 되어야 할텐데
				GetCurrentDirectory(MAX_PATH, szDefault);

			memset(&OFN,0,sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = TEXT("xy 파일\0*.xy\0");
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
				savor.count=0;
				//for(int i = 0 ; i < LINEX ; i++)
				//	ReadFile(hFile,bmpKind[i],sizeof(TILE)*LINEY,&dw,NULL);

				CloseHandle(hFile);
			}
			else {
				MessageBox(hWnd,"좆망.","알림",MB_OK);
			}
//			WriteFile(hFile,bmpKind,((sizeof)int*LINEX*LINEY),&dw);
			break;

		case ID_FILE_LOAD:
			GetCurrentDirectory(MAX_PATH, szDefault);

			memset(&OFN,0,sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = TEXT("xy 파일\0*.xy\0");
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile=MAX_PATH;
			OFN.lpstrDefExt		= "xy";
		//	OFN.lpfnHook		= HookProcCenterDialog;
			OFN.lpstrInitialDir	= szDefault;
			if(GetOpenFileName(&OFN)!=0) {

				hFile=CreateFile(lpstrFile,GENERIC_READ,0,NULL,
					OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
				if(hFile!=INVALID_HANDLE_VALUE) {
					/*
					memset(&savorprev,0,sizeof(savorprev));
					ReadFile(hFile,&savorprev.count,sizeof(int),&dw,NULL);
					for(int i = 0 ; i < savorprev.count ; i++)
						ReadFile(hFile,&savorprev.bmpKindSavor[i],sizeof(TILEPREV),&dw,NULL); // 이런 고도의...
					savorshiftor();
					*/
					memset(&savor,0,sizeof(savor));
					ReadFile(hFile,&savor.count,sizeof(int),&dw,NULL);
					for(int i = 0 ; i < savor.count ; i++)
						ReadFile(hFile,&savor.bmpKindSavor[i],sizeof(TILE),&dw,NULL); // 이런 고도의...
					savor.Load();
					savor.count=0;
				
					//for(int i = 0 ; i < LINEX ; i++)
					//	ReadFile(hFile,bmpKind[i],sizeof(TILE)*LINEY,&dw,NULL);
					CloseHandle(hFile);
					//InvalidateRect(hWnd,NULL,TRUE); // 창이 다른데 왜 되는지 기분은 좋지만 이해할 수 없군
				}
			else {
				MessageBox(hWnd,"좆망.","알림",MB_OK);
			}
			break;
			}
		case 40004:
			shift(2,0);
			break;
		case 40005:
			shift(0,1);
			break;
		case 40006:
			shift(-2,0);
			break;
		case 40007:
			shift(0,-1);
			break;
		}
		InvalidateRect(hWnd,NULL,TRUE);
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}





BOOL CALLBACK AboutDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	// Dlg 정교한 수정 필요
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
		hdc = BeginPaint(hDlg, &ps);
		globalPaint (hdc,0,0,10);
		EndPaint(hDlg, &ps);	

		break;
	}
	return FALSE;
}

		RECT			crt2;
		XY ttemp1,ttemp2;	


// 왼쪽 차일드의 메시지 프로시저
LRESULT CALLBACK ChildLeftProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static HWND hList, hEdit,hBtn;
	TCHAR str[256];


	HDC				hdc;
	PAINTSTRUCT		ps;

	// 화면 제한적으로 뿌리는 그무언가

	switch (iMessage) {
	case WM_CREATE:
		// n
		xPos=0;
		yPos=0;
		// n

		
		MyBitmap[0]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1));
		MyBitmap[1]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP2));
		MyBitmap[2]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP4));
		MyBitmap[3]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP6));
		MyBitmap[4]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP7));
		MyBitmap[5]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP3));
		MyBitmap[6]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP9));
		MyBitmap[7]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP11));
		MyBitmap[8]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP12));
		//MyBitmap[9]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP12));
		memset(bmpKind,0,sizeof(int)*LINEX*LINEY);
		tempBmpKind.init(-1,-1);
		tempBmpKind.tileType = TY_CLASS;
		nowPoint.put(0,0);
		

		return 0;
	case WM_SIZE:
		// 왜 여기선 되고 저기선 안될까?
		// 수학적으로 xMax의 값에 문제가 있는 것은 오히려 자명하지 그래서..(MIDDLEX값을 뺌)
		xMax=(LINEX/2+LINEX%2)*WIDEX-LOWORD(lParam)-MIDDLEX;
		if(LINEX%2==0) xMax += MIDDLEX + LEFTX;
		yMax=LINEY*FULLY-HIWORD(lParam)+HALFY;
		SetScrollRange(hWnd,SB_VERT,0,yMax,TRUE);
		SetScrollPos(hWnd,SB_VERT,0,TRUE);
		SetScrollRange(hWnd,SB_HORZ,0,xMax,TRUE);
		SetScrollPos(hWnd,SB_HORZ,0,TRUE);

		return 0;

	case WM_LBUTTONDOWN:

		nowPoint.put(xPos+LOWORD(lParam),yPos+HIWORD(lParam));
		nowConPoint.putCon(xPos+LOWORD(lParam),yPos+HIWORD(lParam));
				// 한줄로 줄기는 했지만 뭔가 함수가 웃기게 되었군.
		if(mode==1){
			befConPoint = H.bfAI(befConPoint,nowConPoint);
			bmpKind[nowConPoint.x][nowConPoint.y].tileType = tempBmpKind.tileType;
			H.hEditChanger(bmpKind[nowConPoint.x][nowConPoint.y]);
			// 일단 타일만 저장하자
			InvalidateRect(hWnd,NULL,TRUE);
		}
		else if(mode==2){ // 개 막장. 타이머로 정보를 전송해야 하나. 를 해결!
			H.hEditChanger(bmpKind[nowConPoint.x][nowConPoint.y]);
			InvalidateRect(hC2,NULL,TRUE);
		} 
		return 0;

	case WM_RBUTTONDOWN:
		hahaha(hWnd);



	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		globalPaint (hdc,-xPos,-yPos,1);
		EndPaint(hWnd, &ps);	

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


// 오른쪽 차일드의 메시지 프로시저
LRESULT CALLBACK ChildRightProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HWND hbutton;

	int i;
	TCHAR str[128];
	/*
	enum ETILETYPE {
		TY_STAMINA,
		TY_ITEM,
		TY_GRASS,
		TY_DRINK,
		TY_BUS,
		TY_MAINGATE,
		TY_CLASS,
		TY_NONE
	};*/
	TCHAR *Itmes[]={TEXT("STAMINA"),TEXT("ITEM"),TEXT("DRINK"),TEXT("BUS"),TEXT("MAINGATE"),TEXT("MOUNTAIN"),TEXT("CLASS"),TEXT("ERASE")};
	
	switch (iMessage) {
	case WM_CREATE:
		// Create도 함수에.
		
		hbutton=CreateWindow(TEXT("button"),TEXT("New"),WS_CHILD | WS_VISIBLE | 
			BS_AUTORADIOBUTTON | WS_GROUP,
			10,10,80,30,hWnd,(HMENU)101,g_hInst,NULL);
		SendMessage(hbutton,BM_SETCHECK,1,0);
		CreateWindow(TEXT("button"),TEXT("Edit"),WS_CHILD | WS_VISIBLE | 
			BS_AUTORADIOBUTTON,
			100,10,80,30,hWnd,(HMENU)102,g_hInst,NULL);

		H.hCombo = CreateWindow(TEXT("combobox"),NULL,WS_CHILD|WS_VISIBLE|
			CBS_DROPDOWNLIST,10,140,100,200,hWnd,(HMENU)100,g_hInst,NULL);
		for(i=0;i<TY_NONE+1;i++) 
			SendMessage(H.hCombo,CB_ADDSTRING,0,(LPARAM)Itmes[i]);
			SendMessage(H.hCombo,CB_SETCURSEL,0,0);
		//CreateWindow(TEXT("static"),"현재좌표",WS_CHILD |WS_VISIBLE,10,170,100,25,
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
			H.hEdit[11] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_NUMBER|
				ES_AUTOHSCROLL,100,330,80,20,hWnd,(HMENU)121,g_hInst,NULL);

			H.hButton[0] = CreateWindow(TEXT("button"),"prev-next",WS_CHILD|WS_VISIBLE|BS_CHECKBOX,
				10,350,100,25,hWnd,(HMENU)130,g_hInst,NULL);
			H.hButton[1] = CreateWindow(TEXT("button"),"Minimap",WS_CHILD|WS_VISIBLE|BS_CHECKBOX,
				10,370,100,25,hWnd,(HMENU)131,g_hInst,NULL);

			H.hEdit[8] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|
				ES_AUTOHSCROLL,80,390,100,20,hWnd,(HMENU)118,g_hInst,NULL);
			H.hEdit[9] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|
				ES_AUTOHSCROLL,80,410,100,20,hWnd,(HMENU)119,g_hInst,NULL);
			H.hEdit[10] = CreateWindow (TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|
				ES_AUTOHSCROLL,80,430,100,20,hWnd,(HMENU)120,g_hInst,NULL);



		prev_next = 0;
		minimap = 0;

		return 0;

	case WM_COMMAND:
		H.caseProcessor(LOWORD(wParam),HIWORD(wParam)); // 둘다 wParam이야?!
		InvalidateRect(hWnd,NULL,TRUE);
		return 0;

	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		// 굴복하다. 그런데, static이 그렇게 좋은 생각이 아니라는 생각이 들어서.. 줄도 길어지고
		TextOut(hdc,10,170,"현재 좌표",strlen("현재 좌표"));
		TextOut(hdc,10,210,"이전 좌표",strlen("현재 좌표"));
		TextOut(hdc,10,250,"이후 좌표",strlen("현재 좌표"));
		TextOut(hdc,10,290,"flag1",strlen("flag1"));
		TextOut(hdc,10,310,"flag2",strlen("flag2"));
		TextOut(hdc,10,330,"flag3",strlen("flag3"));
		TextOut(hdc,10,390,"college",strlen("college"));
		TextOut(hdc,10,410,"building",strlen("building"));
		TextOut(hdc,10,430,"subject",strlen("subject"));


		EndPaint(hWnd, &ps);
		return 0;

	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}


void shift (int x,int y){
	for (int i = 0 ; i < LINEX ; i++){
		for (int j = 0 ; j < LINEY ; j++){
			if(i-x>=0&&j-y>=0&&i-x<LINEX&&j-y<LINEY) {
				//IntersectRect를 적용하려 하였으나...
				bmpKind2[i][j]=bmpKind[i-x][j-y];
				bmpKind2[i][j].ptPos.x += x;
				bmpKind2[i][j].ptPos.y += y;
				if(bmpKind2[i][j].prevTile.x+x>=0&&bmpKind2[i][j].prevTile.y+y>=0&&bmpKind2[i][j].prevTile.x+x<LINEX&&bmpKind2[i][j].prevTile.y+y<LINEY){
					bmpKind2[i][j].prevTile.x += x;
					bmpKind2[i][j].prevTile.y += y;
				}
				else{
					bmpKind2[i][j].prevTile.x = -1;
					bmpKind2[i][j].prevTile.y = -1;
				}
				if(bmpKind2[i][j].nextTile.x+x>=0&&bmpKind2[i][j].nextTile.y+y>=0&&bmpKind2[i][j].nextTile.x+x<LINEX&&bmpKind2[i][j].nextTile.y+y<LINEY){
					bmpKind2[i][j].nextTile.x += x;
					bmpKind2[i][j].nextTile.y += y;
				}
				else{
					bmpKind2[i][j].nextTile.x = -1;
					bmpKind2[i][j].nextTile.y = -1;
				}
			}
			else
				bmpKind2[i][j].init(i,j);
		}
	}
	for (int i = 0 ; i < LINEX ; i++ ){
		for(int j = 0 ; j < LINEY ; j++) {
			bmpKind[i][j] = bmpKind2[i][j];
		}
	}

}
void savorshiftor(){
	savor.count = savorprev.count;
	for(int i = 0 ; i < savorprev.count ; i++){
		savor.bmpKindSavor[i].tileType = savorprev.bmpKindSavor[i].tileType;
		savor.bmpKindSavor[i].nextTile = savorprev.bmpKindSavor[i].nextTile;
		savor.bmpKindSavor[i].prevTile = savorprev.bmpKindSavor[i].prevTile;
		savor.bmpKindSavor[i].ptPos = savorprev.bmpKindSavor[i].ptPos;
		strcpy(savor.bmpKindSavor[i].building,savorprev.bmpKindSavor[i].building);
		strcpy(savor.bmpKindSavor[i].college,savorprev.bmpKindSavor[i].college);
		strcpy(savor.bmpKindSavor[i].subject,savorprev.bmpKindSavor[i].subject);
		savor.bmpKindSavor[i].flag1 = savorprev.bmpKindSavor[i].flag1;
		savor.bmpKindSavor[i].flag2 = savorprev.bmpKindSavor[i].flag2;
	}
}