#include "RoomCore.h"
#include "MainWin.h"
#include "PlayerContainer.h"
#include "ChannelContainer.h"
#include "SubmitCore.h"
#include "ChannelCore.h"
#include "const.h"

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


int gRoomCore::FindPlayerIndexInTheRoom(char* szID,int nRoomIndex)
{
	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
	{
		if(strcmp(m_rooms[nRoomIndex].szRoomMaxPlayer[i],szID)==0)
			return i;
	}
	return -1;
}

char* gRoomCore::FindPlayerszIDInTheRoom(int nInRoomIndex , int nRoomIndex)
{
	return m_rooms[nRoomIndex].szRoomMaxPlayer[nInRoomIndex];
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
		if(m_rooms[index].szRoomMaxPlayer[i][0] != '\0') 
			continue;
		strcpy(m_rooms[index].szRoomMaxPlayer[i],szID);
		m_rooms[index].nNowPlayer++;
		break;
	}
	// 방에 못들어가도 에러처리는 없으니. isFullRoom을 애용하길.
}	


void gRoomCore::ExitTheRoom (char* szID)	// 방장을 빼내면 방이 파괴됨.
{
	
	for(int i = 0 ; i < MAXROOM ; i++) {
		for(int j = 0 ; j < ROOMMAXPLAYER ; j++)
		{
			if(strcmp(m_rooms[i].szRoomMaxPlayer[j],szID)!=0) continue;
			if(m_rooms[i].nNowPlayer<=1) {	// 이상하게 유연한 타이핑
				DeleteTheRoom(i);
				SendRoomListCauseChange(i/MAXROOMFORPAGE);
				return ;
			}
			else {
				memset(m_rooms[i].szRoomMaxPlayer[j],0,sizeof(char)*IDLENGTH);
				m_rooms[i].nNowPlayer--;

				if(j==m_rooms[i].nMakerIndex) {
					ChangeMakerToFirstUser(i);
				}

				SendRoomRefreshCauseChange(i);

				SendRoomListCauseChange(i/MAXROOMFORPAGE);

				return;
			}
		}
	}
}


void gRoomCore::FindPlayersFromIDs_RMP(int roomIndex,PLAYER* getPlayerlist) {
	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	for(int j = 0 ; j < ROOMMAXPLAYER ; j++) {
		if(m_rooms[roomIndex].szRoomMaxPlayer[j][0]=='\0') {
			memset(&getPlayerlist[j],0,sizeof(PLAYER));
			getPlayerlist[j].classtype = CLASS_NONE;
		}
		else {
			getPlayerlist[j] = gPC->GetPlayerFromID(m_rooms[roomIndex].szRoomMaxPlayer[j]);
		}
	}
}

void gRoomCore::FindClasstypeFromIDs_RMP(int roomIndex,CLASSTYPE* getClasstype) {
	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	for(int j = 0 ; j < ROOMMAXPLAYER ; j++) {
		if(m_rooms[roomIndex].szRoomMaxPlayer[j][0]=='\0') {
			getClasstype[j] = CLASS_NONE;
		}
		else {
			getClasstype[j] = gPC->GetClassType(m_rooms[roomIndex].szRoomMaxPlayer[j]);
		}
	}
}


bool gRoomCore::ChangeMakerToFirstUser(int roomIndex) 
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	for(int i = 0 ; i < ROOMMAXPLAYER ; i++) {
		if(m_rooms[roomIndex].szRoomMaxPlayer[i][0]!='\0') {
			m_rooms[roomIndex].nMakerIndex = i;
			gPC->PutBoolReady(m_rooms[roomIndex].szRoomMaxPlayer[i],false);
			return true;
		}
	}
	return false;
}


void gRoomCore::DeleteTheRoom (int index)
{
	m_isRoom[index] = false;
	memset(&(m_rooms[index]),0,sizeof(ROOM));

//	SendRoomListCauseChange(i/MAXROOMFORPAGE);
}


//////////////////////////////////////////////////////////////////////////
/// connection function
//////////////////////////////////////////////////////////////////////////

void gRoomCore::pk_roommaker_ask(PK_DEFAULT *pk, SOCKET sock)
{
	PK_ROOMMAKER_ASK		ask;		//from client
	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	gChannelCore *gCC = gChannelCore::GetIF();
	gChannelContainer *gCCt = gChannelContainer::GetIF();

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_ROOMMAKER_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_ROOMMAKER_ASK] %s\t message : %s\n", inet_ntoa(clientAddr.sin_addr), ask.room.szRoomName);
	gMainWin::GetIF()->LogWrite(buf);


	PK_ROOMMAKER_REP	rep;
	
	int emptyRoom = FindFirstEmptyRoom();

	if(FindTheRoom(ask.room.szRoomName)!=-1) {
		rep.result = ERM_USINGNAME;
		gMainWin::GetIF()->LogWrite("[PK_ROOMMAKER_REP] 중복이네요.\n");
	}
	else if(emptyRoom == -1) {	// 정적으로 할당된 방이 모두 사용되고 있는 상황
		gMainWin::GetIF()->LogWrite("많이 사랑해주셔서 감사합니다. \n");
		rep.result = ERM_USINGNAME;
	}
	else {

		int befCoreFlag = gPC->GetCoreFlag(ask.szID);
	
		m_isRoom[emptyRoom] = true;
		m_rooms[emptyRoom] = ask.room;
		gPC->PutMode(ask.szID,ECM_ROOM);
		gPC->PutCoreFlag(ask.szID,emptyRoom);
		gCCt->DeletePlayer(ask.szID); 
		rep.result = ERM_SUCCESS;
		rep.room = m_rooms[emptyRoom];
		FindPlayersFromIDs_RMP(emptyRoom,rep.playerlist);	// 추가 코드
		wsprintf(buf,"[PK_ROOMMAKER_REP] Index : %d 성공! \n",emptyRoom);
		gMainWin::GetIF()->LogWrite(buf);

		gCC->pk_channelrefresh_rep(befCoreFlag);
		SendRoomListCauseChange(emptyRoom/MAXROOMFORPAGE);

	}
	gMainWin::GetIF()->Send(PL_ROOMMAKER_REP, sizeof(rep), &rep, sock);

}


void gRoomCore::pk_roomlist_ask(PK_DEFAULT *pk, SOCKET sock)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	gChannelCore *gCC = gChannelCore::GetIF();

	PK_ROOMLIST_ASK ask;

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_ROOMLIST_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_ROOMLIST_ASK] %s\t player : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	gMainWin::GetIF()->LogWrite(buf);

	if(ask.nPage==0||isRoomInPage(ask.nPage)) {
		gPC->PutMode(ask.szID,ECM_ROOMJOIN);
		gPC->PutCoreFlag(ask.szID,ask.nPage);

		SendRoomListCauseChange(ask.nPage);
	}
}


void gRoomCore::pk_charselect_ask(PK_DEFAULT *pk, SOCKET sock)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	PK_CHARSELECT_ASK ask;

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_CHARSELECT_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_CHARSELECT_ASK] %s\t player : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	gMainWin::GetIF()->LogWrite(buf);

	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	if(nRoomIndex<0) return;
	else if(!gPC->isClasstypeExistedInRoom(nRoomIndex,ask.classtype)) {
#ifdef CRITICAL_SECTION_GOGO
		EnterCriticalSection(&gMainWin::GetIF()->crit[nRoomIndex]);
#endif	
		gPC->PutClassType(ask.szID,ask.classtype);
		SendRoomRefreshCauseChange(nRoomIndex);

#ifdef CRITICAL_SECTION_GOGO
		LeaveCriticalSection(&gMainWin::GetIF()->crit[nRoomIndex]);
#endif
	}
}


void gRoomCore::pk_gameready_ask(PK_DEFAULT *pk, SOCKET sock)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	PK_GAMEREADY_ASK ask;

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_GAMEREADY_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_GAMEREADY_ASK] %s\t player : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	gMainWin::GetIF()->LogWrite(buf);


	gPC->PutBoolReady(ask.szID,ask.bReady);
	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	if(nRoomIndex<0) return;
	else if (gPC->GetClassType(ask.szID)!=CLASS_NONE) {
		SendRoomRefreshCauseChange(nRoomIndex);
	}
}


void gRoomCore::pk_gamestart_ask(PK_DEFAULT *pk, SOCKET sock)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	PK_GAMESTART_ASK ask;

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_GAMESTART_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_GAMESTART_ASK] %s\t player : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	gMainWin::GetIF()->LogWrite(buf);

	PK_GAMESTART_REP rep;

	CLASSTYPE ctype = gPC->GetClassType(ask.szID);
	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	// sangwoo temp
	gPC->PutBoolReady(ask.szID,true);
	bool bTemp = gPC->isAllReadyInRoom(nRoomIndex);
	gPC->PutBoolReady(ask.szID,false);
	// end
	int nNowPlayer = m_rooms[nRoomIndex].nNowPlayer;

	BYTE temp_subject[CLASSNUM][CLASSSEAT];
	for(int i = 0 ; i < CLASSNUM ; i++)
	{
		temp_subject[i][0] = -1;
		temp_subject[i][1] = -1;
		temp_subject[i][2] = NOSEAT;
 	}

	if(ctype==-1) {
		rep.result = EGS_NOREADY;
		gMainWin::GetIF()->Send(PL_GAMESTART_REP, sizeof(rep), &rep, sock);
	}
	else if (!bTemp) {
		rep.result = EGS_NOREADYUSER;
		gMainWin::GetIF()->Send(PL_GAMESTART_REP, sizeof(rep), &rep, sock);

	}
	else if(nNowPlayer==1) {
		rep.result = EGS_ONEUSER;
		gMainWin::GetIF()->Send(PL_GAMESTART_REP, sizeof(rep), &rep, sock);
	}

	else {
		m_rooms[nRoomIndex].isGaming = true;
		SendRoomListCauseChange(nRoomIndex/MAXROOMFORPAGE);
		gSubmitCore::GetIF()->pk_gamestart_rep(nRoomIndex);
	}
}



void gRoomCore::pk_roomjoin_ask(PK_DEFAULT *pk, SOCKET sock)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	gChannelContainer *gCCt = gChannelContainer::GetIF();
	gChannelCore *gCC = gChannelCore::GetIF();

	PK_ROOMJOIN_ASK ask;

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_ROOMJOIN_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_ROOMJOIN_ASK] %s\t nPage : %d nIdx : %d\n", inet_ntoa(clientAddr.sin_addr), ask.nPage, ask.nIdx);
	gMainWin::GetIF()->LogWrite(buf);

	PK_ROOMJOIN_REP rep;
	int nRoomIndex;
	
	nRoomIndex = ask.nPage*MAXROOMFORPAGE + ask.nIdx;
	if (!m_isRoom[nRoomIndex]) {
		rep.result = ERJ_NOROOM;
		gMainWin::GetIF()->Send(PL_ROOMJOIN_REP, sizeof(rep), &rep, sock);
	}
	else if(m_rooms[nRoomIndex].isPass && strcmp(m_rooms[nRoomIndex].szRoomPass,ask.szPass)!=0) // 너무 대충한 것 같은 느낌의 pass확인
	{
		rep.result = ERJ_PASSWRONG;
		gMainWin::GetIF()->Send(PL_ROOMJOIN_REP, sizeof(rep), &rep, sock);
	}
	//else if(m_rooms[nPage].nNowPlayer == m_rooms[nPage].nMaxPlayer) // 방이 꽉 차면
	else if(isFullRoom(nRoomIndex))
	{
		rep.result = ERJ_FULL;
		gMainWin::GetIF()->Send(PL_ROOMJOIN_REP, sizeof(rep), &rep, sock);
	}
	else // 논리적으로 rep와 rep2의 중복이...
	{
		int befCoreFlag = gPC->GetCoreFlag(ask.szID); 
		int befChannelNum = gCCt->FindPlayer(ask.szID);

		EnterTheRoom(nRoomIndex,ask.szID); 

		

		SendRoomListCauseChange(befCoreFlag);	// 채널의 정보를 갱신
		SendRoomRefreshCauseChange(nRoomIndex); // 방 내부의 정보를 갱신

		PLAYER l_playerlist[ROOMMAXPLAYER];
		FindPlayersFromIDs_RMP(nRoomIndex,l_playerlist);

		rep.result = ERJ_SUCCESS;
		gPC->PutMode(ask.szID,ECM_ROOM);
		gPC->PutCoreFlag(ask.szID,nRoomIndex);
		gCCt->DeletePlayer(ask.szID);

		gCC->pk_channelrefresh_rep(befChannelNum);
		
		rep.joinroom = m_rooms[nRoomIndex]; 
		memcpy(&rep.playerlist,&l_playerlist,sizeof(PLAYER)*ROOMMAXPLAYER);

		wsprintf(buf,"[PK_ROOMJOIN_REP] %s\t \n", inet_ntoa(clientAddr.sin_addr));
		gMainWin::GetIF()->LogWrite(buf);
		gMainWin::GetIF()->Send(PL_ROOMJOIN_REP, sizeof(rep), &rep, sock);

	}
}


// 수정사항

void gRoomCore::pk_roomback_ask(PK_DEFAULT *pk, SOCKET sock)
{

	gRoomCore *gRC = gRoomCore::GetIF();
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	PK_ROOMBACK_ASK ask;

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_ROOMBACK_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_ROOMBACK_ASK] %s\n", inet_ntoa(clientAddr.sin_addr) );
	gMainWin::GetIF()->LogWrite(buf);


	int nRoomIndex = gPC->GetCoreFlag(ask.szID);	//	방의 index를 획득

	m_rooms[nRoomIndex].isGaming = false;
	gPC->PutMode(ask.szID ,ECM_ROOM);	//서버에서룸상태변경
	gPC->PutBoolReady(ask.szID,false);	//레디모드해제
	gPC->PutClassType(ask.szID , CLASS_NONE);

	//	패킷보낼준비
	PK_ROOMBACK_REP rep;
	rep.room = m_rooms[nRoomIndex];
	PLAYER l_playerlist[ROOMMAXPLAYER];
	FindPlayersFromIDs_RMP(nRoomIndex,l_playerlist);

	for(int j = 0 ; j < ROOMMAXPLAYER ; j++) {
		if(m_rooms[nRoomIndex].szRoomMaxPlayer[j][0]!='\0') {
			l_playerlist[j].bReady = false;
		}
	}

	memcpy(&rep.playerlist,&l_playerlist,sizeof(PLAYER)*ROOMMAXPLAYER);

	gPC->SendSelect(PL_ROOMBACK_REP,sizeof(PK_ROOMBACK_REP),&rep,ECM_ROOM,nRoomIndex);

}



//////////////////////////////////////////////////////////////////////////
/// ???
//////////////////////////////////////////////////////////////////////////


void gRoomCore::SendRoomListCauseChange(int nPage) {

	PK_ROOMLIST_REP		rep;
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	rep.nPage = nPage;

	for(int i = 0 ; i < MAXROOMFORPAGE ; i++)
	{
		rep.roomlist[i] = m_rooms[i+nPage*MAXROOMFORPAGE];
	}

	gPC->SendSelect(PL_ROOMLIST_REP,sizeof(PK_ROOMLIST_REP),&rep,ECM_ROOMJOIN,nPage);
}

void gRoomCore::SendRoomRefreshCauseChange(int nRoomIndex)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	PK_ROOMREFRESH_REP rep;
	
	rep.room = m_rooms[nRoomIndex];
	PLAYER l_playerlist[ROOMMAXPLAYER];
	FindPlayersFromIDs_RMP(nRoomIndex,l_playerlist);
	memcpy(&rep.playerlist,&l_playerlist,sizeof(PLAYER)*ROOMMAXPLAYER);
	gPC->SendSelect(PL_ROOMREFRESH_REP,sizeof(PK_ROOMREFRESH_REP),&rep,ECM_ROOM,nRoomIndex);
}


bool gRoomCore::isRoomInPage(int nPage) {
	for(int i = 0 ; i < MAXROOMFORPAGE ; i++) {
		if(m_isRoom[i+nPage*MAXROOMFORPAGE]) 
			return true;
	}
	return false;
}
