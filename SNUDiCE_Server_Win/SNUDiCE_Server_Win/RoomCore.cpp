#include "RoomCore.h"
#include "MainWin.h"
#include "PlayerContainer.h"

static gRoomCore s_RoomCore;

gRoomCore *gRoomCore::GetIF()
{
	return &s_RoomCore;
}

bool gRoomCore::SetUp()
{
//	for(int i = 0 ; i < MAXROOMNUM ; i++)
//		m_isRoom[i] = false;
	memset(m_isRoom,0,sizeof(bool)*MAXROOM);
	memset(m_rooms,0,sizeof(ROOM)*MAXROOM);
	return true;
}

void gRoomCore::Release()
{

}

//////////////////////////////////////////////////////////////////////////
/// private function
//////////////////////////////////////////////////////////////////////////

int gRoomCore::FindFirstEmptyRoom ()
{
	for(int i = 0 ; i < MAXROOM ; i++)
	{
		if(!m_isRoom[i]) return i;
	}
	return -1;
}

int gRoomCore::FindTheRoom(char* szRoomName)
{
	for(int i = 0 ;  i < MAXROOM ; i++)
	{
		if(m_isRoom[i]) {
			if(strcmp(szRoomName,m_rooms[i].szRoomName)==0) return i;
		}
	}
	return -1;
}

bool gRoomCore::isFullRoom (int index)
{
	if(m_isRoom[index] && m_rooms[index].nNowPlayer >= m_rooms[index].nMaxPlayer) return true;
	else return false;
}

void gRoomCore::EnterTheRoom (int index,char* szID)
{
	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
	{
		if(m_rooms[index].szRoomMaxPlayer[i]!=NULL) continue;
		strcpy(m_rooms[index].szRoomMaxPlayer[i],szID);
		m_rooms[index].nNowPlayer++;
	}
	// �濡 ������ ����ó���� ������. isFullRoom�� �ֿ��ϱ�.
}	

void gRoomCore::ExitTheRoom (char* szID)	// ������ ������ ���� �ı���.
{
	for(int i = 0 ; i < MAXROOM ; i++) {
		for(int j = 0 ; j < ROOMMAXPLAYER ; j++)
		{
			if(strcmp(m_rooms[i].szRoomMaxPlayer[j],szID)!=0) continue;
			if(j==0) {
				DeleteTheRoom(i);
				return ;
			}
			else {
				memset(m_rooms[i].szRoomMaxPlayer[j],0,sizeof(char)*IDLENGTH);
				m_rooms[i].nNowPlayer--;
				return;
			}
		}
	}
}


void gRoomCore::DeleteTheRoom (int index)
{
	m_isRoom[index] = false;
	memset(&(m_rooms[index]),0,sizeof(ROOM));
}

/*
void gRoomCore::Put(int i,ROOM* room)
{
	m_rooms[i].isGaming = room->isGaming;
	m_rooms[i].nMaxPlayer = room->nMaxPlayer;
	m_rooms[i].nNowPlayer = room->nNowPlayer;
	strcpy(m_rooms[i].szRoomName,room->szRoomName);
	strcpy(m_rooms[i].szRoomPass,room->szRoomPass);
}
*/


//////////////////////////////////////////////////////////////////////////
/// connection function
//////////////////////////////////////////////////////////////////////////

void gRoomCore::pk_roommaker_ask(PK_DEFAULT *pk, SOCKET sock)
{
	PK_ROOMMAKER_ASK		ask;		//from client
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_ROOMMAKER_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_ROOMMAKER_ASK] %s\t message : %s\n", inet_ntoa(clientAddr.sin_addr), ask.room.szRoomName);
	OutputDebugString(buf);



	PK_ROOMMAKER_REP	rep;

	int emptyRoom = FindFirstEmptyRoom();

	if(FindTheRoom(ask.room.szRoomName)!=-1) {
		rep.result = ERM_USINGNAME;
		OutputDebugString("[PK_ROOMMAKER_REP] �ߺ��̳׿�.\n");
	}
	else if(emptyRoom == -1) {	// �������� �Ҵ�� ���� ��� ���ǰ� �ִ� ��Ȳ
		OutputDebugString("���� ������ּż� �����մϴ�. \n");
		rep.result = ERM_USINGNAME;
	}
	else {
		// �̰��� �� ����� �Լ��� ���� �� �� ����� �Լ��� �ϴ� ����̳� �ϰ� ����.
		// Put �Լ��� �־��ٰ� ���� ������ �ֳ� ����
		m_isRoom[emptyRoom] = true;
		m_rooms[emptyRoom] = ask.room;
		gPC->PutMode(ask.szID,ECM_ROOM);
		gPC->PutCoreFlag(ask.szID,emptyRoom);
		rep.result = ERM_SUCCESS;
		OutputDebugString("[PK_ROOMMAKER_REP] ����! \n");
	}

	gMainWin::GetIF()->Send(PL_ROOMMAKER_REP, sizeof(rep), &rep, sock);
}


void gRoomCore::pk_roomlist_ask(PK_DEFAULT *pk, SOCKET sock)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	PK_ROOMLIST_ASK ask;

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_ROOMLIST_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_ROOMLIST_ASK] %s\t player : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	OutputDebugString(buf);


	PK_ROOMLIST_REP	rep;

	gPC->PutMode(ask.szID,ECM_ROOMJOIN);
	gPC->PutCoreFlag(ask.szID,ask.nPage);

	rep.nPage = ask.nPage;
	for(int i = 0 ; i < MAXROOMFORPAGE ; i++)
	{
		rep.roomlist[i] = m_rooms[i+ask.nPage*MAXROOMFORPAGE];
	}

	gPC->SendSelect(PL_ROOMLIST_REP,sizeof(PK_ROOMLIST_REP),&rep,ECM_ROOMJOIN,ask.nPage);
	//gMainWin::GetIF()->Send(PL_ROOMLIST_REP, sizeof(rep), &rep, sock);
}


void gRoomCore::pk_roomjoin_ask(PK_DEFAULT *pk, SOCKET sock)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	PK_ROOMJOIN_ASK ask;

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_ROOMJOIN_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_ROOMJOIN_ASK] %s\t player : %d %d\n", inet_ntoa(clientAddr.sin_addr), ask.nPage, ask.nIdx);
	OutputDebugString(buf);

	PK_ROOMJOIN_REP rep;
	int nPage;
	
	nPage = ask.nPage*MAXROOMFORPAGE + ask.nIdx;
	if(strcmp(m_rooms[nPage].szRoomPass,ask.szPass)!=0)
	{
		rep.result = ERJ_PASSWRONG;
	}
	else if(m_rooms[nPage].nNowPlayer == m_rooms[nPage].nMaxPlayer) // ���� �� ����
	{
		rep.result = ERJ_FULL;
	}
	else 
	{
		rep.result = ERJ_SUCCESS;
		gPC->PutMode(ask.szID,ECM_ROOM);
		gPC->PutCoreFlag(ask.szID,nPage);
		EnterTheRoom(nPage,ask.szID); 
		rep.joinroom = m_rooms[nPage]; 
	}

	// ���� �÷��̾�Ը� ����.
	//gMainWin::GetIF()->Send(PL_ROOMJOIN_REP, sizeof(rep), &rep, sock);
	// �濡 �ִ� ��� �÷��̾�� ����.
	gPC->SendSelect(PL_ROOMJOIN_REP,sizeof(PK_ROOMJOIN_REP),&rep,ECM_ROOM,nPage);
}
