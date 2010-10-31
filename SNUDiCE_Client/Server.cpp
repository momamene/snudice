#include "Server.h"
#include "MainWin.h"
#include "Util.h"
#include "stringconst.h"
#include "PopUp.h"
#include "LoginCore.h"
#include "BattleNetCore.h"
#include "RoomCore.h"
#include "SubmitCore.h"
#include "GameCore.h"
#include "Chat.h"
#include "UIGame.h"

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

	return true;
}

bool gServer::Send(WORD type, WORD size, void *buf)
{
	if(!s_sock)
		return false;

	char *temp = (char*)buf;

	m_pkDefault.dwProtocol = type;

	if(size)
		memcpy(m_pkDefault.strPacket, temp, size);

	m_pkDefault.dwSize = PK_HEADER_SIZE + size;

	int		r1 = 0, r2 = 0;
	int		fail_count = 0;

	while(true)
	{
		r2 = send(s_sock, (char*)&m_pkDefault, m_pkDefault.dwSize, 0);

		if(r2 != SOCKET_ERROR)
			r1 += r2;

		if(r1 == m_pkDefault.dwSize)
			break;

		fail_count++;

		if(fail_count > 10)
			return false;
	}
	return true;
}

void gServer::Receive(LPARAM lParam)
{
	if(!SocketErrorMessage(lParam))
		return;

	char	szBuf[256];
//	int		retVal;

	switch( WSAGETSELECTEVENT(lParam) )
	{
		case FD_CONNECT:
			wsprintf(szBuf, "[Connect] %s : %d\n",
				inet_ntoa(s_serverAddr.sin_addr), ntohs(s_serverAddr.sin_port));
			gUtil::DebugMsg(szBuf);
			m_bConnect = true;
			break;
		case FD_READ:
			ReadPacket();
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
}

void gServer::ReadPacket()
{
	int		r1 = 0, r2 = 0;
	int		fail_count = 0;

	r2 = recv(s_sock, (char*)&m_pkDefault, PK_HEADER_SIZE, 0);
	if(r2 == SOCKET_ERROR)
		return;
	if(r2 == 0)
		return;

	r1 += PK_HEADER_SIZE;

	while(true)
	{
		r2 = recv(s_sock, m_pkDefault.strPacket, m_pkDefault.dwSize - PK_HEADER_SIZE, 0);

		if(r2 != SOCKET_ERROR)
			r1 += r2;

		if(r1 == m_pkDefault.dwSize)
			break;

		fail_count++;

		if(fail_count > 10)
			break;
	}

	if(fail_count <= 10)
		Recv();
}

void gServer::Recv()
{
	switch(m_pkDefault.dwProtocol)
	{
		case PL_LOGIN_REP:
			gLoginCore::GetIF()->pk_login_rep((PK_LOGIN_REP*)m_pkDefault.strPacket);
			break;

		case PL_MESSAGE_REP:
			gChat::GetIF()->pk_message_rep((PK_MESSAGE_REP*)m_pkDefault.strPacket);
			break;

		case PL_CHANNELREFRESH_REP:
			gBattleNetCore::GetIF()->pk_channelrefresh_rep((PK_CHANNELREFRESH_REP*)m_pkDefault.strPacket);
			break;
		case PL_CHANNELCHANGE_REP:
			gBattleNetCore::GetIF()->pk_channelchange_rep((PK_CHANNELCHANGE_REP*)m_pkDefault.strPacket);
			break;

		case PL_ROOMMAKER_REP:
			gRoomCore::GetIF()->pk_roommake_rep((PK_ROOMMAKER_REP*)m_pkDefault.strPacket);
			break;

		case PL_ROOMLIST_REP:
			gRoomCore::GetIF()->pk_roomlist_rep((PK_ROOMLIST_REP*)m_pkDefault.strPacket);
			break;

		case PL_ROOMJOIN_REP:
			gRoomCore::GetIF()->pk_roomjoin_rep((PK_ROOMJOIN_REP*)m_pkDefault.strPacket);
			break;
			//방나가고돌아오기수정
		case PL_ROOMBACK_REP:
			gRoomCore::GetIF()->pk_roomback_rep((PK_ROOMBACK_REP*)m_pkDefault.strPacket);
			break;

		case PL_ROOMREFRESH_REP:
			gRoomCore::GetIF()->pk_roomrefresh_rep((PK_ROOMREFRESH_REP*)m_pkDefault.strPacket);
			break;

		case PL_GAMESTART_REP:
			gRoomCore::GetIF()->pk_gamestart_rep((PK_GAMESTART_REP*)m_pkDefault.strPacket);
			break;

		case PL_SUBMIT_REP:
			gSubmitCore::GetIF()->pk_submit_rep((PK_SUBMIT_REP*)m_pkDefault.strPacket);
			break;
		case PL_SUBMITREADY_REP:
			gSubmitCore::GetIF()->pk_submitready_rep((PK_SUBMITREADY_REP*)m_pkDefault.strPacket);
			break;
		case PL_MAINGAMESTART_REP:
			gSubmitCore::GetIF()->pk_maingametart_rep((PK_MAINGAMESTART_REP*)m_pkDefault.strPacket);
			break;

		case PL_MOVESTART_REP:
			gGameCore::GetIF()->pk_movestart_rep((PK_MOVESTART_REP*)m_pkDefault.strPacket);
			break;

		case PL_BUSMOVECHOOSE_REP:
			gGameCore::GetIF()->pk_busmovechoose_rep((PK_BUSMOVECHOOSE_REP*)m_pkDefault.strPacket);
			break;
		case PL_BUSMOVESTART_REP:
			gGameCore::GetIF()->pk_busmovestart_rep((PK_BUSMOVESTART_REP*)m_pkDefault.strPacket);
			break;

		case PL_GAMEPLAYERINFO_REP:
			gGameCore::GetIF()->pk_gameplayerinfo_rep((PK_GAMEPLAYERINFO_REP*)m_pkDefault.strPacket);
			break;

		case PL_POPINFO_REP:
			gGameCore::GetIF()->pk_popinfo_rep((PK_POPINFO_REP*)m_pkDefault.strPacket);
			break;

		case PL_NEXTTURN_REP:
			gGameCore::GetIF()->pk_nextturn_rep((PK_NEXTTURN_REP*)m_pkDefault.strPacket);
			break;

		case PL_GAMEEND_REP:
			gGameCore::GetIF()->pk_gameend_rep((PK_GAMEEND_REP*)m_pkDefault.strPacket);
			break;

		case PL_ITEMUSE_REP:
			gUIGame::GetIF()->pk_itemuse_rep((PK_ITEMUSE_REP*)m_pkDefault.strPacket);
			break;

		case PL_WARPSTART_REP:
			gGameCore::GetIF()->pk_warpstart_rep((PK_WARPSTART_REP*)m_pkDefault.strPacket);
			break;

		case PL_WARPLISTSTART_REP:
			gGameCore::GetIF()->pk_warpliststart_rep((PK_WARPLISTSTART_REP*)m_pkDefault.strPacket);
			break;

		case PL_INFOCHANGE_REP:
			gUIGame::GetIF()->pk_infochange_rep((PK_INFOCHANGE_REP*)m_pkDefault.strPacket);
			break;
		
	}
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
//	int		retVal;
	
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