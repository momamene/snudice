#include "Server.h"
#include "MainWin.h"
#include "Util.h"
#include "stringconst.h"
#include "PopUp.h"

static SOCKET		s_sock = NULL;
static SOCKADDR_IN	s_serverAddr;

gServer::gServer()
{
	
}

gServer::~gServer()
{
	
}

static gServer	s_Server;

gServer *gServer::GetIF()
{
	return &s_Server;
}

bool gServer::SetUp()
{
	char		szBuf[256];
	int			retVal;

	m_bConnect = false;

	WSADATA		wsa;
	if(WSAStartup(WINSOCK_VERSION_2_2, &wsa) != 0)
		return false;

	s_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(s_sock == INVALID_SOCKET)
	{
		gUtil::DebugMsg("socket 생성 실패\n");
		return false;
	}

 	retVal = WSAAsyncSelect(s_sock, gMainWin::GetIF()->m_hWnd, WM_SOCKET,
 								FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
 	if(retVal == SOCKET_ERROR)
 	{
 		gUtil::DebugMsg("WSAAsyncSelect() Failed\n");
 		EndSocket();
 		return false;
 	}

	s_serverAddr.sin_family			= AF_INET;
	s_serverAddr.sin_port			= htons(SERVER_PORT);
	s_serverAddr.sin_addr.s_addr	= inet_addr(SERVER_IP);
	
	retVal = connect(s_sock, (SOCKADDR*)&s_serverAddr, sizeof(s_serverAddr));

	// 비동기 connect는 바로 return 되면서 WSAEWOULDBLOCK 에러 발생시킨다.
	if( retVal == SOCKET_ERROR && WSAEWOULDBLOCK != WSAGetLastError() )
	{
		wsprintf(szBuf, "[Connect Error!] %s : %d\n", SERVER_IP, SERVER_PORT);
		gUtil::DebugMsg(szBuf);
		EndSocket();
		return false;
	}

// 	wsprintf(szBuf, "[Connect] %s : %d\n",
// 				inet_ntoa(s_serverAddr.sin_addr), ntohs(s_serverAddr.sin_port));
// 	gUtil::DebugMsg(szBuf);

	return m_bConnect;
}

void gServer::Send()
{
	char	szBuf[256] = " aa ";

	send(s_sock, szBuf, strlen(szBuf), 0);
}

void gServer::Receive(LPARAM lParam)
{
	if(!SocketErrorMessage(lParam))
		return;

	char	szBuf[256];
	int		retVal;

	switch( WSAGETSELECTEVENT(lParam) )
	{
		case FD_CONNECT:
			wsprintf(szBuf, "[Connect] %s : %d\n",
				inet_ntoa(s_serverAddr.sin_addr), ntohs(s_serverAddr.sin_port));
			gUtil::DebugMsg(szBuf);
			m_bConnect = true;
			break;
		case FD_READ:
			break;
		case FD_WRITE:
			break;
		case FD_CLOSE:
			wsprintf(szBuf, "[Close] %s : %d\n",
				inet_ntoa(s_serverAddr.sin_addr), ntohs(s_serverAddr.sin_port));
			gUtil::DebugMsg(szBuf);
			m_bConnect = false;
			break;
	}


// 	char	szBuf[256];
// 	int		retVal;
// 
// 	retVal = recv(s_sock, szBuf, 256, 0);
// 	szBuf[retVal] = '\0';
// 	gUtil::DebugMsg(szBuf);

}

void gServer::ReConnect()
{
	char	szBuf[256];
	int		retVal;

	retVal = connect(s_sock, (SOCKADDR*)&s_serverAddr, sizeof(s_serverAddr));
	
	if( retVal == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK )
	{
		EndSocket();
		wsprintf(szBuf, "socket connect faild: %d\n", WSAGetLastError());
		gUtil::DebugMsg(szBuf);
		return ;
	}
	wsprintf(szBuf, "socket [re]connect because: %d\n", WSAGetLastError());
	gUtil::DebugMsg(szBuf);
}

void gServer::Release()
{
	EndSocket();
}

//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//	Private
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
void gServer::EndSocket()
{
	if(s_sock)
	{
		shutdown(s_sock, 0x02);		// SD_BOTH 는 뭘까?
		closesocket(s_sock);
		s_sock = NULL;
	}
}

bool gServer::SocketErrorMessage(LPARAM lParam)
{
	char	szBuf[256];
	int		retVal;
	
	if( WSAGETSELECTERROR(lParam) )
	{
		m_bConnect = false;

		if( ( WSAGETSELECTERROR(lParam) == WSAECONNREFUSED ) ||		// 10061 :Connection refused. 서버 프로그램이 실행 X
			( WSAGETSELECTERROR(lParam) == WSAENETUNREACH ) ||		// 10051 :Network is unreachable.
			( WSAGETSELECTERROR(lParam) == WSAETIMEDOUT ) )//||		// 10060 :Connection timed out.
		{
			gPopUp::GetIF()->SetPopUp(ECLK_CANCEL, EPOP_RECONNECT, STR_1, STR_2);

 			return false;
		}
		EndSocket();
		if( WSAGETSELECTERROR(lParam) == WSAECONNABORTED)			// 10053 :서버가 종료됨.. 아마도
		{
			gUtil::DebugMsg("서버와의 연결이 끊김\n");
			gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_DISCONNECT, STR_3);
			return false;
		}
		else
			wsprintf(szBuf, "WM_SOCKET error: %d\n", WSAGETSELECTERROR(lParam));
		gUtil::DebugMsg(szBuf);
		return false;
	}
	return true;
}