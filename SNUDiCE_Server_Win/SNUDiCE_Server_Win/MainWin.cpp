#include "MainWin.h"
#include "MysqlDB.h"

#include "LoginCore.h"
#include "MessageCore.h"
#include "ChannelCore.h"
#include "RoomCore.h"
#include "SubmitCore.h"

#include "PlayerContainer.h"
#include "ChannelContainer.h"

#include "SubjectContainer.h"
#include "TileContainer.h"
#include "GamePlayerContainer.h"

#include "time.h"
#include "ItemContainer.h"
#include "Charinfo.h"
		

static gMainWin	s_MainWin;		// for singleton

gMainWin::gMainWin()
{
	gMysql::GetIF()->init();
}

gMainWin::~gMainWin()
{

}

gMainWin* gMainWin::GetIF()
{
	return &s_MainWin;
}

void gMainWin::SetUpWindow(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	WNDCLASS WndClass;
	m_hInst	= hInstance;

	memset(&WndClass, 0, sizeof(WndClass));

	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance		= hInstance;
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;
	WndClass.lpszClassName	= WNDNAME;
	WndClass.lpszMenuName	= NULL;
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	m_hWnd = CreateWindow(WNDNAME, WNDNAME, WNDSTYLE,
		CW_USEDEFAULT, CW_USEDEFAULT, WNDSIZEW, WNDSIZEH,
		NULL, (HMENU)NULL, hInstance, NULL);


	RECT	rcWin = {0, 0, WNDSIZEW, WNDSIZEH};
	AdjustWindowRect(&rcWin, WNDSTYLE, false);
	SetWindowPos(m_hWnd, NULL, 0, 0,
		rcWin.right - rcWin.left, rcWin.bottom - rcWin.top,
		SWP_NOMOVE | SWP_NOZORDER);

	MoveWindow(m_hWnd, 0, 0, WNDSIZEW, WNDSIZEH, false);

	ShowWindow(m_hWnd, nCmdShow);
}

bool gMainWin::SetUpWinsock()
{
	int		retVal;

	// Winsock 초기화
	WSADATA	wsa;

	if(WSAStartup(WINSOCK_VERSION_2_2, &wsa) != 0)	// WSAStartup은 리턴값만으로 오류를 처리한다.
	{
		MessageBox(NULL, "WinSock 초기화 실패", "Error", MB_OK);
		return false;
	}

	// socket()
	m_listen_sock = socket(AF_INET, SOCK_STREAM, 0);	// af ; 주소체계, type ; 소켓타입, protocol ; 프로토콜
	// AF_INET, SOCK_STREAM -> TCP	; 신뢰성, 연결형 프로토콜
	//			SOCK_DGRAM	-> UDP	; 비신뢰, 비연결	"

	if(m_listen_sock == INVALID_SOCKET)
		err_quit("socket()");

	// bind()
	SOCKADDR_IN		serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family		= AF_INET;					//hton ; host bytes to network bytes(Big Endian)
	serverAddr.sin_port			= htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr	= inet_addr(SERVER_IP);
	retVal = bind(m_listen_sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));


	gMysql::GetIF()->init();

	if(retVal == SOCKET_ERROR)
		err_quit("bind()");

	// listen()
	retVal = listen(m_listen_sock, SOMAXCONN);
	if(retVal == SOCKET_ERROR)
		err_quit("listen()");

	return true;

}



bool gMainWin::SetUp(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	SetUpWindow(hInstance,lpszCmdParam,nCmdShow);
	if(!SetUpWinsock())
		return false;

	if(!gLoginCore::GetIF()->SetUp())
		return false;

	// a
	if(!gMessageCore::GetIF()->SetUp())
		return false;
//	if(!gChannelCore::GetIF()->SetUp()) // SetUp 이 필요 없었던 경우.
//		return false;

	if(!gRoomCore::GetIF()->SetUp())
		return false;

	if(!gPlayerContainer::GetIF()->SetUp())
		return false;

	if(!gChannelContainer::GetIF()->SetUp())
		return false;

	// a
	if(!gPlayerContainer::GetIF()->SetUp())
		return false;

	// b
//	if(!gSubjectContainer::GetIF()->SetUp()) // SetUp 이 필요 없었던 경우.
//		return false;
	if(!gTileContainer::GetIF()->Setup())
		return false;

	if(!gSubmitCore::GetIF()->SetUp())
		return false;

	if(!gGamePlayerContainer::GetIF()->SetUp())
		return false;

	if(!gItemContainer::GetIF()->SetUp())
		return false;

	if(!gCharinfo::GetIF()->SetUp())
		return false;
	

	//로그파일을 만듭니다.
	logFile = fopen(LOG_FILE_NAME , "w+");

	for (int i = 0 ; i < MAXROOM ; i++)
		InitializeCriticalSection(&crit[i]);
	
	return true;
}

void gMainWin::Release()
{
	fclose(logFile);
	for (int i = 0 ; i < MAXROOM ; i++)
		DeleteCriticalSection(&crit[i]);
	
	closesocket(m_listen_sock);
	WSACleanup();

	gLoginCore::GetIF()->Release();
	gPlayerContainer::GetIF()->Release();
	gMessageCore::GetIF()->Release();
	gChannelContainer::GetIF()->Release();
	gChannelCore::GetIF()->Release();
	gRoomCore::GetIF()->Release();
	gSubmitCore::GetIF()->Release();
	gGamePlayerContainer::GetIF()->Release();
	gCharinfo::GetIF()->Release();
}

bool gMainWin::MakeListenThread()
{

	HANDLE		hThread;
	DWORD		dwThreadID;

	hThread = CreateThread(NULL, 0, Listen, NULL, 0, &dwThreadID);

	if(hThread == NULL) {
		gMainWin::GetIF()->LogWrite("Thread failed\n");
		return false;
	}
	else {
		CloseHandle(hThread);
		return true;
	}
}

int gMainWin::Run()
{
	MSG			Msg;

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
	if(!m_bActive)
		return;
}

void gMainWin::Recv(PK_DEFAULT *pk, SOCKET sock)
{
#ifndef USE_LOG
	__try
	{
#endif

		switch(pk->dwProtocol)
		{
			case PL_LOGIN_ASK:
				gLoginCore::GetIF()->pk_login_ask(pk, sock);
				break;
			case PL_MESSAGE_ASK:
				gMessageCore::GetIF()->pk_message_ask(pk, sock);
				break;
			case PL_CHANNELCHANGE_ASK:
				gChannelCore::GetIF()->pk_channelchange_ask(pk,sock);
				break;
			case PL_ROOMMAKER_ASK:
				gRoomCore::GetIF()->pk_roommaker_ask(pk,sock);
				break;
			case PL_ROOMLIST_ASK:
				gRoomCore::GetIF()->pk_roomlist_ask(pk,sock);
				break;
			case PL_ROOMJOIN_ASK:
				gRoomCore::GetIF()->pk_roomjoin_ask(pk,sock);
				break;
			case PL_ROOMBACK_ASK:
				gRoomCore::GetIF()->pk_roomback_ask(pk,sock);
				break;
			case PL_CHARSELECT_ASK:
				gRoomCore::GetIF()->pk_charselect_ask(pk,sock);
				break;
			case PL_GAMEREADY_ASK:
				gRoomCore::GetIF()->pk_gameready_ask(pk,sock);
				break;
			case PL_GAMESTART_ASK:
				gRoomCore::GetIF()->pk_gamestart_ask(pk,sock);
				break;
			case PL_SUBMIT_ASK:
				gSubmitCore::GetIF()->pk_submit_ask(pk,sock);
				break;
			case PL_SUBMITREADY_ASK:
				gSubmitCore::GetIF()->pk_submitready_ask(pk,sock);
				break;
			case PL_SUBMITCOUNT_ASK :
				gSubmitCore::GetIF()->pk_submitcount_ask(pk,sock);
				break;
			case PL_MOVESTART_ASK:
				gGamePlayerContainer::GetIF()->pk_movestart_ask(pk,sock);
				break;
			case PL_MOVEEND_ASK: case PL_MOVEENDCOUPLE_ASK:
				gGamePlayerContainer::GetIF()->pk_moveend_ask(pk,sock);
				break;
			case PL_BUSMOVESELECT_ASK:
				gGamePlayerContainer::GetIF()->pk_busmoveselect_ask(pk,sock);
				break;
			case PL_BUSMOVEEND_ASK: case PL_BUSMOVEENDCOUPLE_ASK :
				gGamePlayerContainer::GetIF()->pk_busmoveend_ask(pk,sock);
				break;
			case PL_ITEMUSE_ASK:
				gGamePlayerContainer::GetIF()->pk_itemuse_ask(pk,sock);
				break;
			case PL_ITEMUSESTART_ASK:
				gGamePlayerContainer::GetIF()->pk_itemusestart_ask(pk,sock);
				break;
			case PL_INFOCHANGEEND_ASK:
				gGamePlayerContainer::GetIF()->pk_infochangeend_ask(pk,sock);
				break;
				/*
			case PL_WARPSTART_ASK:
				gGamePlayerContainer::GetIF()->pk_warpstart_ask(pk,sock);
				break;
				*/
			case PL_WARPEND_ASK:
				gGamePlayerContainer::GetIF()->pk_warpend_ask(pk,sock);
				break;
			case PL_WARPLISTEND_ASK:
				gGamePlayerContainer::GetIF()->pk_warplistend_ask(pk,sock);
				break;

			case PL_GOLOGIN_ASK :
				gGamePlayerContainer::GetIF()->pk_gologin_ask(pk,sock);
				break;
	/*	서버처리로 대체
			case PL_WHISPER_ASK:
				gMessageCore::GetIF()->pk_whisper_ask(pk, sock);
				break;
	*/
			case PL_ANSCOUPLE_ASK :
				gGamePlayerContainer::GetIF()->pk_anscouple_ask(pk,sock);
				break;

			case PL_BECOUPLEEND_ASK :
				gGamePlayerContainer::GetIF()->pk_becoupleend_ask(pk,sock);
				break;
				
			//친구처리
			case PL_FRIENDADD_ASK :
				gPlayerContainer::GetIF()->pk_friendadd_ask(pk, sock);
				break;
			case PL_FRIENDDELETE_ASK :
				gPlayerContainer::GetIF()->pk_frienddelete_ask(pk,sock);
				break;
			case PL_FRIENDWHISPER_ASK :
				gMessageCore::GetIF()->pk_friendwhisper_ask(pk,sock);
				break;
			case PL_FRIENDLIST_ASK :
				gMessageCore::GetIF()->pk_friendlist_ask(pk, sock);
				break;
			//
			case PL_GETPLAYERINFO_ASK :
				gPlayerContainer::GetIF()->pk_getplayerinfo_ask(pk , sock);
				break;
		}
#ifndef USE_LOG
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		gMainWin::GetIF()->LogWrite("축|서버폭팔|하");
		gMainWin::GetIF()->Release();
		exit(0);
	}
#endif

}

bool gMainWin::Send(DWORD type, DWORD size, void *buf ,char* szID)
{
	SOCKET sock;
	if(gPlayerContainer::GetIF()->FindSocketFromID(szID,&sock))
		return Send(type,size,buf,sock);
	else
		return false;
}

bool gMainWin::Send(DWORD type, DWORD size, void *buf, SOCKET sock)
{
	PK_DEFAULT		pk;

	if(!sock) {
		gMainWin::GetIF()->LogWrite("gMainWin::Send Sock fail error\n");
		return false;
	}
	char *temp = (char*)buf;

	pk.dwProtocol = type;

	if(size)
		memcpy(pk.strPacket, temp, size);

	pk.dwSize = PK_HEADER_SIZE + size;

	int		r1 = 0, r2 = 0;
	int		fail_count = 0;

	while(true)
	{
		r2 = send(sock, (char*)&pk + r1, pk.dwSize - r1, 0);

		if(r2 != SOCKET_ERROR)
			r1 += r2;

		if(r1 == pk.dwSize)
			break;

		fail_count++;

		if(fail_count > 10) {
			gMainWin::GetIF()->LogWrite("gMainWin::Send fail count error\n");
			return false;
		}
	}
	return true;
}




void gMainWin::Exit()
{
	SendMessage(m_hWnd, WM_DESTROY, 0, 0);
}


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//	private
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	gMainWin	*mw		= gMainWin::GetIF();

	PAINTSTRUCT ps;
	HDC hdc;

	switch(iMsg)
	{
	case WM_LBUTTONDOWN:
		InvalidateRect(hWnd,NULL,true);
		return 0;
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

		// active
	case WM_ACTIVATE:
		switch(LOWORD(wParam))
		{
		case WA_ACTIVE: 
		case WA_CLICKACTIVE:
			mw->m_bActive = true;
			break;
		case WA_INACTIVE:
			mw->m_bActive = false;
			break;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd,&ps);
		gPlayerContainer::GetIF()->Draw(hdc);
		EndPaint(hWnd,&ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}

void err_quit(char *msg)
{
	
	LPVOID	lpMsgBuf;


	
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(-1);
	
}

void err_display(char *msg)
{
	
	LPVOID	lpMsgBuf;
	char	buf [1024];


	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	sprintf(buf,"[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	gMainWin::GetIF()->LogWrite(buf);

	LocalFree(lpMsgBuf);
	
}

// client <-> server 간 통신.

void gMainWin::UserRelease(SOCKET client_sock,SOCKADDR_IN clientAddr) {
	char			clientID[IDLENGTH];

	char		buf[1024];
	int bTemp;

	bTemp = gPlayerContainer::GetIF()->DeletePlayer(client_sock, clientID);
	int channel = gChannelContainer::GetIF()->FindPlayer(clientID);

	
	if(bTemp) {
		gChannelContainer::GetIF()->DeletePlayer(clientID);
		gChannelCore::GetIF()->pk_channelrefresh_rep(channel);
		// sangwoo temp
		gMainWin::GetIF()->LogWrite("refresh for delete\n");
//		gChannelContainer::GetIF()->fullDebuger();
		// end
	}
	else {
		// 에러 처리.
		gMainWin::GetIF()->LogWrite("Exception in function ExitPlayer\n");
	}

	gRoomCore::GetIF()->ExitTheRoom(clientID);
	closesocket(client_sock);

	sprintf(buf,"[TCP Server] Client Exit : IP = %s\t Port = %d\n",
		inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	gMainWin::GetIF()->LogWrite (buf);
}


DWORD WINAPI ProcessClient(LPVOID arg)
{
	gMainWin *mw = gMainWin::GetIF();

	SOCKET			client_sock = (SOCKET)arg;

	SOCKADDR_IN		clientAddr;
	char			szBuf[BUFFERSIZE + 1];
	int				addrLen;
	int				retVal;
	PK_DEFAULT		pkDefault;

	srand((unsigned)time(NULL));



	// 클라이언트 정보 얻기
	addrLen = sizeof(clientAddr);
	getpeername(client_sock, (SOCKADDR*)&clientAddr, &addrLen);

	while(true)
	{
		int		r1 = 0, r2 = 0;
		int		fail_count = 0;
		
		retVal = recv(client_sock, (char*)&pkDefault, PK_HEADER_SIZE, 0);
		gMainWin::GetIF()->LogWrite("a.");
		if(retVal == SOCKET_ERROR)	// 임시방편
			break;
		//	continue;
		if(retVal == 0)		// 보통 종료할 때 이 메세지가 뜨던데?
			break;

		r1 += PK_HEADER_SIZE;

		while(true)
		{
			r2 = recv(client_sock, (char*)&pkDefault + r1, pkDefault.dwSize - r1, 0);
			gMainWin::GetIF()->LogWrite("b\n");
			
			if(r2 != SOCKET_ERROR)
				r1 += r2;
			
			if(r1 == pkDefault.dwSize)
				break;
			
			fail_count++;
			
			if(fail_count > 10)
				break;
		}

		if(fail_count <= 10)
			gMainWin::GetIF()->Recv(&pkDefault, client_sock);
	}

	// closesocket
	//mw->ExitPlayer(client_sock,clientID,clientAddr);

	mw->UserRelease(client_sock,clientAddr);
	return 0;
}

DWORD WINAPI Listen(LPVOID prc)
{
	gMainWin *gmainWin = gMainWin::GetIF();


	SOCKET			client_sock;
	SOCKADDR_IN		clientAddr;
	int				addrLen;
	//	int				retVal;
	char			szBuf[BUFFERSIZE + 1];		// 왜 + 1인가??
	HANDLE			hThread;
	DWORD			dwThreadID;

	ZeroMemory(&clientAddr, sizeof(SOCKADDR_IN));

	MSG		Msg;
	char	buf[1024];

	gMainWin::GetIF()->LogWrite("Server Start\n");

	while(true)
	{
		// accept()

		addrLen = sizeof(clientAddr);
		client_sock = accept(gmainWin->m_listen_sock, (SOCKADDR*)&clientAddr, &addrLen);

		if(client_sock == INVALID_SOCKET)
		{

			err_display("accept()");
			continue;
		}


		sprintf(buf,"\n[TCP Server] Client Connect : IP = %s\t Port = %d\n",
			inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		gMainWin::GetIF()->LogWrite(buf);

		// make thread
		hThread = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)client_sock, 0, &dwThreadID);

		if(hThread == NULL) 
			gMainWin::GetIF()->LogWrite("Thread failed\n");
		else
			CloseHandle(hThread);

	}
}

void gMainWin::LogWrite(char * buf)
{
	fprintf(logFile , "%s", buf);
}