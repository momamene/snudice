#include "Server.h"


static gServer	s_Server;

static DWORD WINAPI ProcessClient(LPVOID arg);	// server <-> client 간 통신. 스레드
static void err_quit(char *msg);						// 소켓 함수 오류 출력후 종료
static void err_display(char *msg);					// 소켓 함수 오류 출력


gServer *gServer::GetIF()
{
	return &s_Server;
}

gServer::gServer()
{

}

gServer::~gServer()
{

}

bool gServer::SetUp(int argc, char *argv[])
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
	if(retVal == SOCKET_ERROR)
		err_quit("bind()");

	// listen()
	retVal = listen(m_listen_sock, SOMAXCONN);
	if(retVal == SOCKET_ERROR)
		err_quit("listen()");

	return true;
}

void gServer::Run()
{
	// 데이터 통신에 사용할 변수
	SOCKET			client_sock;
	SOCKADDR_IN		clientAddr;
	int				addrLen;
	int				retVal;
	char			szBuf[BUFFERSIZE + 1];		// 왜 + 1인가??
	HANDLE			hThread;
	DWORD			dwThreadID;

	printf("Server Start\n");

	while(true)
	{
		// accept()
		addrLen = sizeof(clientAddr);
		client_sock = accept(m_listen_sock, (SOCKADDR*)&clientAddr, &addrLen);
		if(client_sock == INVALID_SOCKET)
		{
			err_display("accept()");
			continue;
		}

		printf("\n[TCP Server] Client Connect : IP = %s\t Port = %d\n",
				inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		// make thread
		hThread = CreateThread(NULL, 0, ProcessClient,
								(LPVOID)client_sock, 0, &dwThreadID);

		if(hThread == NULL)
			printf("Thread failed\n");
		else
			CloseHandle(hThread);
	}
}

void gServer::Release()
{
	closesocket(m_listen_sock);
	WSACleanup();
}

//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//	private
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
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

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// client <-> server 간 통신.
DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET		client_sock = (SOCKET)arg;
	SOCKADDR_IN	clientAddr;
	char		szBuf[BUFFERSIZE + 1];
	int			addrLen;
	int			retVal;

	// 클라이언트 정보 얻기
	addrLen = sizeof(clientAddr);
	getpeername(client_sock, (SOCKADDR*)&clientAddr, &addrLen);

	while(true)
	{
		// 데이터 받기
		retVal = recv(client_sock, szBuf, BUFFERSIZE, 0);
		if(retVal == SOCKET_ERROR)
		{
			err_display("recv()");
			break;
		}
		else if(retVal == 0)
			break;

		// 받은 데이터 출력
		szBuf[retVal] = '\0';
		printf("[TCP/%s:%d] %s\n",
				inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), szBuf);

		// 데이터 보내기
		strcpy(szBuf, "aaaaa");
		retVal = send(client_sock, szBuf, strlen(szBuf), 0);
		if(retVal == SOCKET_ERROR)
		{
			err_display("send()");
			break;
		}
	}

	// closesocket
	closesocket(client_sock);
	printf("[TCP Server] Client Exit : IP = %s\t Port = %d\n",
			inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

	return 0;
}
