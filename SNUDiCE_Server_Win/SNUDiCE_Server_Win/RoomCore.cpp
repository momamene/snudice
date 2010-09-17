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
	// 방에 못들어가도 에러처리는 없으니. isFullRoom을 애용하길.
}	

void gRoomCore::ExitTheRoom (char* szID)	// 방장을 빼내면 방이 파괴됨.
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
		OutputDebugString("[PK_ROOMMAKER_REP] 중복이네요.\n");
	}
	else if(emptyRoom == -1) {	// 정적으로 할당된 방이 모두 사용되고 있는 상황
		OutputDebugString("많이 사랑해주셔서 감사합니다. \n");
		rep.result = ERM_USINGNAME;
	}
	else {
		// 이것이 방 만들기 함수로 들어가야 좀 더 깔끔한 함순데 일단 기억이나 하고 있자.
		// Put 함수로 넣었다가 지운 흔적이 있네 ㅇㅇ
		m_isRoom[emptyRoom] = true;
		m_rooms[emptyRoom] = ask.room;
		gPC->PutMode(ask.szID,ECM_ROOM);
		gPC->PutCoreFlag(ask.szID,emptyRoom);
		rep.result = ERM_SUCCESS;
		OutputDebugString("[PK_ROOMMAKER_REP] 성공! \n");
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
	else if(m_rooms[nPage].nNowPlayer == m_rooms[nPage].nMaxPlayer) // 방이 꽉 차면
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

	// 들어온 플레이어에게만 보냄.
	//gMainWin::GetIF()->Send(PL_ROOMJOIN_REP, sizeof(rep), &rep, sock);
	// 방에 있는 모든 플레이어에게 보냄.
	gPC->SendSelect(PL_ROOMJOIN_REP,sizeof(PK_ROOMJOIN_REP),&rep,ECM_ROOM,nPage);
}
