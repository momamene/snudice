#include "Server.h"


static gServer	s_Server;

static DWORD WINAPI ProcessClient(LPVOID arg);	// server <-> client �� ���. ������
static void err_quit(char *msg);						// ���� �Լ� ���� ����� ����
static void err_display(char *msg);					// ���� �Լ� ���� ���


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

	return true;
}

void gServer::Run()
{
	// ������ ��ſ� ����� ����
	SOCKET			client_sock;
	SOCKADDR_IN		clientAddr;
	int				addrLen;
	int				retVal;
	char			szBuf[BUFFERSIZE + 1];		// �� + 1�ΰ�??
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

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// client <-> server �� ���.
DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET		client_sock = (SOCKET)arg;
	SOCKADDR_IN	clientAddr;
	char		szBuf[BUFFERSIZE + 1];
	int			addrLen;
	int			retVal;

	// Ŭ���̾�Ʈ ���� ���
	addrLen = sizeof(clientAddr);
	getpeername(client_sock, (SOCKADDR*)&clientAddr, &addrLen);

	while(true)
	{
		// ������ �ޱ�
		retVal = recv(client_sock, szBuf, BUFFERSIZE, 0);
		if(retVal == SOCKET_ERROR)
		{
			err_display("recv()");
			break;
		}
		else if(retVal == 0)
			break;

		// ���� ������ ���
		szBuf[retVal] = '\0';
		printf("[TCP/%s:%d] %s\n",
				inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), szBuf);

		// ������ ������
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
