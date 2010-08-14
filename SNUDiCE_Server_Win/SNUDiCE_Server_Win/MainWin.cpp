#include "MainWin.h"
#include "LoginCore.h"
#include "PlayerContainer.h"

/*
#include "const.h"
#include "Mouse.h"
#include "LoginCore.h"
#include "Server.h"
#include "Util.h"
#include "PopUp.h"
*/

DWORD WINAPI ProcessClient(LPVOID arg);				// server <-> client �� ���. ������
static void err_quit(char *msg);					// ���� �Լ� ���� ����� ����
static void err_display(char *msg);					// ���� �Լ� ���� ���

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
	// Set Up Window

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

	m_hWnd=CreateWindow(WNDNAME, WNDNAME, WNDSTYLE,
		CW_USEDEFAULT, CW_USEDEFAULT, WNDSIZEW, WNDSIZEH,
		NULL, (HMENU)NULL, hInstance, NULL);


	RECT	rcWin = {0, 0, WNDSIZEW, WNDSIZEH};
	AdjustWindowRect(&rcWin, WNDSTYLE, false);
	SetWindowPos(m_hWnd, NULL, 0, 0,
		rcWin.right - rcWin.left, rcWin.bottom - rcWin.top,
		SWP_NOMOVE | SWP_NOZORDER);

	MoveWindow(m_hWnd, 0, 0, WNDSIZEW, WNDSIZEH, false);

	ShowWindow(m_hWnd, nCmdShow);


	// Setup winsock2

	int		retVal;

	// Winsock �ʱ�ȭ
	WSADATA	wsa;

	if(WSAStartup(WINSOCK_VERSION_2_2, &wsa) != 0)	// WSAStartup�� ���ϰ������� ������ ó���Ѵ�.
	{
		MessageBox(NULL, "WinSock �ʱ�ȭ ����", "Error", MB_OK);
		return false;
	}

	// socket()
	m_listen_sock = socket(AF_INET, SOCK_STREAM, 0);	// af ; �ּ�ü��, type ; ����Ÿ��, protocol ; ��������
													// AF_INET, SOCK_STREAM -> TCP	; �ŷڼ�, ������ ��������
													//			SOCK_DGRAM	-> UDP	; ��ŷ�, �񿬰�	"

	if(m_listen_sock == INVALID_SOCKET)
		err_quit("socket()");

	// bind()
	SOCKADDR_IN		serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family		= AF_INET;					//hton ; host bytes to network bytes(Big Endian)
	serverAddr.sin_port			= htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr	= inet_addr(SERVER_IP);
	retVal = bind(m_listen_sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	
	if(retVal == SOCKET_ERROR)
		err_quit("bind()");

	// listen()
	retVal = listen(m_listen_sock, SOMAXCONN);
	if(retVal == SOCKET_ERROR)
		err_quit("listen()");

	// setup another class
	if(!gLoginCore::GetIF()->SetUp())
		return false;

	if(!gPlayerContainer::GetIF()->SetUp())
		return false;

	return true;
}

bool gMainWin::MakeListenThread()
{

	HANDLE		hThread;
	DWORD		dwThreadID;

	hThread = CreateThread(NULL, 0, Listen, NULL, 0, &dwThreadID);

	if(hThread == NULL) {
		OutputDebugString("Thread failed\n");
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
		// �޽��� ť�� �޽��� ������ ó��
		if(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			// ALT ����
			if(Msg.message == WM_SYSKEYDOWN)
				continue;
			if(Msg.message == WM_QUIT)
				break;

// 			switch(m_eCoreMode)
// 			{
// 			case ECM_LOGIN:
// 				if(gLoginCore::GetIF()->PreTransMsg(Msg))
// 					continue;
// 				break;
// 			case ECM_BATTLENET:
// 				if(gBattleNetCore::GetIF()->PreTransMsg(Msg))
// 					continue;
// 				break;
// 			}

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

void gMainWin::Release()
{
	closesocket(m_listen_sock);
	WSACleanup();
	gLoginCore::GetIF()->Release();
}


DWORD WINAPI Listen(LPVOID prc)
{
	gMainWin *gmainWin = gMainWin::GetIF();

	
	SOCKET			client_sock;
	SOCKADDR_IN		clientAddr;
	int				addrLen;
//	int				retVal;
	char			szBuf[BUFFERSIZE + 1];		// �� + 1�ΰ�??
	HANDLE			hThread;
	DWORD			dwThreadID;

	ZeroMemory(&clientAddr, sizeof(SOCKADDR_IN));

		MSG		Msg;
		char	buf[1024];

	OutputDebugString("Server Start\n");

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

		OutputDebugString(buf);

		// make thread
		hThread = CreateThread(NULL, 0, ProcessClient,
								(LPVOID)client_sock, 0, &dwThreadID);

		if(hThread == NULL) 
			OutputDebugString("Thread failed\n");
		else
			CloseHandle(hThread);

	}
}

void gMainWin::MainLoop()
{
	if(!m_bActive)
		return;
}

void gMainWin::Recv(PK_DEFAULT *pk, SOCKET sock)
{

	switch(pk->dwProtocol)
	{
		case PL_LOGIN_ASK:
			gLoginCore::GetIF()->pk_login_ask(pk, sock);
		break;

	}

}

bool gMainWin::Send(DWORD type, DWORD size, void *buf, SOCKET sock)
{
	PK_DEFAULT		pk;

	if(!sock)
		return false;
	
	char *temp = (char*)buf;
	
	pk.dwProtocol = type;
	
	if(size)
		memcpy(pk.strPacket, temp, size);
	
	pk.dwSize = PK_HEADER_SIZE + size;
	
	int		r1 = 0, r2 = 0;
	int		fail_count = 0;
	
	while(true)
	{
		r2 = send(sock, (char*)&pk, pk.dwSize, 0);
		
		if(r2 != SOCKET_ERROR)
			r1 += r2;
		
		if(r1 == pk.dwSize)
			break;
		
		fail_count++;
		
		if(fail_count > 10)
			return false;
	}
	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	gMainWin	*mw		= gMainWin::GetIF();

	switch(iMsg)
	{

		/*
		case WM_MOVE:
			mw->MoveWindow();
		break;
*/
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
			/*
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
			if(!mw->m_bActive)
				return 0;

			mouse->m_nPosX = LOWORD(lParam);
			mouse->m_nPosY = HIWORD(lParam);
			mouse->OnMouseMove();
			return 0;
			*/

		// active
		case WM_ACTIVATE:
			switch(LOWORD(wParam))
			{
				case WA_ACTIVE: case WA_CLICKACTIVE:
					mw->m_bActive = true;
					break;
				case WA_INACTIVE:
					mw->m_bActive = false;
					break;
			}
			return 0;

		// network
			/*
		case WM_SOCKET:
			gServer::GetIF()->Receive(lParam);
			return 0;
			*/
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


//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//	private
//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	OutputDebugString(buf);

	LocalFree(lpMsgBuf);
	
}

// client <-> server �� ���.

DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET			client_sock = (SOCKET)arg;
	SOCKADDR_IN		clientAddr;
	char			szBuf[BUFFERSIZE + 1];
	int				addrLen;
	int				retVal;
	PK_DEFAULT		pkDefault;


	char		buf[1024];

	// Ŭ���̾�Ʈ ���� ���
	addrLen = sizeof(clientAddr);
	getpeername(client_sock, (SOCKADDR*)&clientAddr, &addrLen);

	while(true)
	{
		int		r1 = 0, r2 = 0;
		int		fail_count = 0;
		
		retVal = recv(client_sock, (char*)&pkDefault, PK_HEADER_SIZE, 0);
		if(retVal == SOCKET_ERROR)
			continue;
		if(retVal == 0)
			break;

		r1 += PK_HEADER_SIZE;

		while(true)
		{
			r2 = recv(client_sock, pkDefault.strPacket, pkDefault.dwSize - PK_HEADER_SIZE, 0);
			
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
	gPlayerContainer::GetIF()->DeletePlayer(client_sock);
	closesocket(client_sock);
	
	sprintf(buf,"[TCP Server] Client Exit : IP = %s\t Port = %d\n",
			inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	OutputDebugString (buf);

	return 0;
}