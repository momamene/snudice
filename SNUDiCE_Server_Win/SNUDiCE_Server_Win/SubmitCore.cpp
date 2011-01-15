#include "SubmitCore.h"
#include "RoomCore.h"
#include "PlayerContainer.h"
#include "MainWin.h"
#include "GamePlayerContainer.h"

static gSubmitCore s_SubmitCore;

gSubmitCore *gSubmitCore::GetIF()
{
	return &s_SubmitCore;
}

bool gSubmitCore::SetUp() 
{
	for(int i = 0 ; i < MAXROOM ; i++)	{
		m_isValidSubmitSubject[i] = false;
	}
	return true;
}

void gSubmitCore::init(int nRoomIndex)
{
	gRoomCore* gRC = gRoomCore::GetIF();
	if(nRoomIndex < 0 || nRoomIndex >= MAXROOM) return;
	else {
		m_isValidSubmitSubject[nRoomIndex] = true;
		for(int i = 0 ; i < CLASSNUM ; i++) {
			m_submitSubject[nRoomIndex][i][0] = AVAILSEAT;
			m_submitSubject[nRoomIndex][i][1] = AVAILSEAT;
			m_submitSubject[nRoomIndex][i][2] = AVAILSEAT;
		}
		for(int i = 0 ; i < ROOMMAXPLAYER ; i++) {
			if(gRC->m_rooms[nRoomIndex].szRoomMaxPlayer[i][0] != '\0') { // 만약, 방에 있다면
				m_isFinishSubmitSubject[nRoomIndex][i] = false;
			}
			else {
				m_isFinishSubmitSubject[nRoomIndex][i] = true;
			}
			for(int j = 0 ; j < MAXSUBJECT ; j++) {
				m_submitSubjectPlayer[nRoomIndex][i][j] = AVAILSEAT;
			}
		}
	}
}

void gSubmitCore::pk_gamestart_rep(int nRoomIndex)
{
	gPlayerContainer* gPC = gPlayerContainer::GetIF();
	gSubmitCore::init(nRoomIndex);

	PK_GAMESTART_REP rep;

	rep.result = EGS_SUCCESS;
	memcpy(rep.subject,m_submitSubject[nRoomIndex],sizeof(BYTE)*CLASSNUM*CLASSSEAT);
	gPC->PutModeToModeForAll(ECM_ROOM,nRoomIndex,ECM_SUBMIT);
	gPC->SendSelect(PL_GAMESTART_REP,sizeof(PK_GAMESTART_REP),&rep,ECM_SUBMIT,nRoomIndex);

}

void gSubmitCore::putSubjectToPlayer(int nRoomIndex, int nInRoomIndex, int nSubjectIndex)
{
	for(int i = 0 ; i < MAXSUBJECT ; i++)
	{
		if(m_submitSubjectPlayer[nRoomIndex][nInRoomIndex][i]==AVAILSEAT)
		{
			m_submitSubjectPlayer[nRoomIndex][nInRoomIndex][i] = nSubjectIndex;
			break;
		}
	}
}

void gSubmitCore::pushSubjectToPlayer(int nRoomIndex,int nInRoomIndex,int nSubjectIndex)
{
	for(int i = 0 ; i < MAXSUBJECT ; i++)
	{
		if(m_submitSubjectPlayer[nRoomIndex][nInRoomIndex][i]==nSubjectIndex)
		{
			m_submitSubjectPlayer[nRoomIndex][nInRoomIndex][i] = AVAILSEAT;
			break;
		}
	}
}

bool gSubmitCore::isSubjectFull(int nRoomIndex,int nInRoomIndex)
{
	for(int i = 0 ; i < MAXSUBJECT ; i++)
	{
		if(m_submitSubjectPlayer[nRoomIndex][nInRoomIndex][i]==AVAILSEAT)
		{
			return false;
		}
	}
	return true;
}

bool gSubmitCore::isSubjectExisted(int nRoomIndex,int nInRoomIndex,int nSubjectIndex)
{
	for(int i = 0 ; i < MAXSUBJECT ; i++)
	{
		if(m_submitSubjectPlayer[nRoomIndex][nInRoomIndex][i]==nSubjectIndex)
		{
			return true;
		}
	}
	return false;
}

bool gSubmitCore::isFinishAllSubmit(int nRoomIndex)
{
	for(int i = 0 ; i < MAXSUBJECT ; i++)
	{
		if(!m_isFinishSubmitSubject[nRoomIndex][i])
		{
			return false;
		}
	}
	putFavorsameclass(nRoomIndex);
	return true;
}

void gSubmitCore::putFavorsameclass(int nRoomIndex)
{
	int		playeridx_A , playeridx_B;
	bool	sameChk;
	gGamePlayerContainer* gGPC = gGamePlayerContainer::GetIF();
	gCharinfo *gCI = gCharinfo::GetIF();
	gRoomCore *gRC = gRoomCore::GetIF();

	char buf[1024];

	CLASSTYPE classtype[ROOMMAXPLAYER];
	gRC->FindClasstypeFromIDs_RMP(nRoomIndex,classtype);
	
	int j,k;
	for(int i = 0 ; i < CLASSNUM ; i++)	{
		sameChk = false;
		for (j = 0; j < CLASSSEAT ; j++)	{
			if (m_submitSubject[nRoomIndex][i][j] == AVAILSEAT)	{
				sameChk = true;
				break;
			}
		}
		if (!sameChk)	{
			for (j = 0 ; j < CLASSSEAT ; j++)	{
				for (k = j+1 ; k < CLASSSEAT ; k++)	{
					playeridx_A = m_submitSubject[nRoomIndex][i][j];
					playeridx_B = m_submitSubject[nRoomIndex][i][k];

					if (gCI->getMale(classtype[playeridx_A])^gCI->getMale(classtype[playeridx_B]))	{
						wsprintf(buf,"[SameclassFavorup] : %s and %s\n",gGPC->m_GamePlayer[nRoomIndex][playeridx_A].szID , gGPC->m_GamePlayer[nRoomIndex][playeridx_B].szID );
						gMainWin::GetIF()->LogWrite(buf);
						gGPC->m_favor[nRoomIndex][playeridx_A].point[playeridx_B] += SAMECLASS_FAVORPOINT;
						gGPC->m_favor[nRoomIndex][playeridx_B].point[playeridx_A] += SAMECLASS_FAVORPOINT;
					}
				}
			}
		}
	}
}

bool gSubmitCore::putSubject(int nRoomIndex,int nInRoomIndex,int nSubjectIndex)
{
	if(!m_isValidSubmitSubject[nRoomIndex]) 
		return false;
	if(isSubjectFull(nRoomIndex,nInRoomIndex)) 
		return false;
	if(isSubjectExisted(nRoomIndex,nInRoomIndex,nSubjectIndex))
		return false;
	
	for(int i = 0 ; i < CLASSNUM ; i++)
	{
		if(m_submitSubject[nRoomIndex][nSubjectIndex][i]==NOSEAT) {
			return false;	//수강2개 수정
			continue;
		}
		else if(m_submitSubject[nRoomIndex][nSubjectIndex][i]==AVAILSEAT) {
			EnterCriticalSection(&gMainWin::GetIF()->crit[nRoomIndex]);	//공유자원 침범방지!
			
			m_submitSubject[nRoomIndex][nSubjectIndex][i] = nInRoomIndex;
			putSubjectToPlayer(nRoomIndex,nInRoomIndex,nSubjectIndex);
			
			LeaveCriticalSection(&gMainWin::GetIF()->crit[nRoomIndex]);
			return true;
		}
	}
	return false;
}

bool gSubmitCore::pushSubject(int nRoomIndex,int nInRoomIndex,int nSubjectIndex)
{
	for(int i = 0 ; i < CLASSNUM ; i++)
	{
		if(m_submitSubject[nRoomIndex][nSubjectIndex][i]==nInRoomIndex) {
			m_submitSubject[nRoomIndex][nSubjectIndex][i]=AVAILSEAT;
			pushSubjectToPlayer(nRoomIndex,nInRoomIndex,nSubjectIndex);
			return true;
		}
	}
	return false;
}

void gSubmitCore::pk_submit_ask(PK_DEFAULT *pk,SOCKET sock)
{

	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	PK_SUBMIT_ASK ask;

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_SUBMIT_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_SUBMIT_ASK] %s\t player : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	gMainWin::GetIF()->LogWrite(buf);

	PK_SUBMIT_REP rep;


	int nRoomIndex = gPlayerContainer::GetIF()->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRoomCore::GetIF()->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);
	if(m_isFinishSubmitSubject[nRoomIndex][nInRoomIndex]) {
		gMainWin::GetIF()->LogWrite("수강신청 할 수가 없어\n");
	}
	else if(ask.bSubmit) {
		if(!putSubject(nRoomIndex,nInRoomIndex,ask.nSubjectIdx)) {			// 수강신청 실패
			gMainWin::GetIF()->LogWrite("Error지만 괜찮은\n");						// 나중에 잘 되면 지워
		}
		else {
			memcpy(rep.subject,m_submitSubject[nRoomIndex],sizeof(BYTE)*CLASSNUM*CLASSSEAT);
			gPC->SendSelect(PL_SUBMIT_REP,sizeof(PK_SUBMIT_REP),&rep,ECM_SUBMIT,nRoomIndex);
		}
	}
	else {
		if(!isSubjectExisted(nRoomIndex,nInRoomIndex,ask.nSubjectIdx)) {	// 넌 듣지도 않은 걸 취소하려 했어.
			gMainWin::GetIF()->LogWrite("Error2지만 괜찮은\n");						// 나중에 잘 되면 지워
		}
		else {

			pushSubject(nRoomIndex,nInRoomIndex,ask.nSubjectIdx);
			memcpy(rep.subject,m_submitSubject[nRoomIndex],sizeof(BYTE)*CLASSNUM*CLASSSEAT);
			gPC->SendSelect(PL_SUBMIT_REP,sizeof(PK_SUBMIT_REP),&rep,ECM_SUBMIT,nRoomIndex);
		}
	}
}

void gSubmitCore::pk_submitready_ask(PK_DEFAULT *pk,SOCKET sock)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	PK_SUBMITREADY_ASK ask;

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_SUBMITREADY_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_SUBMITREADY_ASK] %s\t player : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	gMainWin::GetIF()->LogWrite(buf);

	PK_SUBMITREADY_REP rep;
	int nRoomIndex = gPlayerContainer::GetIF()->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRoomCore::GetIF()->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);
	if(!isSubjectFull(nRoomIndex,nInRoomIndex)) {
		rep.result = ESUB_LESSCLASS;
	}
	else {
		rep.result = ESUB_SUCCESS;
		m_isFinishSubmitSubject[nRoomIndex][nInRoomIndex] = true;
	}
	gMainWin::GetIF()->Send(PL_SUBMITREADY_REP,sizeof(rep),&rep,ask.szID);
	if(isFinishAllSubmit(nRoomIndex)) {
		gGamePlayerContainer::GetIF()->pk_maingamestart_rep(nRoomIndex);
	}
}

//	모든 이에게 패킷은 오되 하나의 쓰레드만 받아서 일괄처리.
void gSubmitCore::pk_submitcount_ask(PK_DEFAULT *pk,SOCKET sock)
{

	gPlayerContainer	*gPC	=						gPlayerContainer::GetIF();
	gGamePlayerContainer			*gGPC	=		gGamePlayerContainer::GetIF();
	gRoomCore			*gRC	=		gRoomCore::GetIF();

	PK_SUBMITCOUNT_ASK ask;

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_SUBMITCOUNT_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_SUBMITCOUNT_ASK] %s\t player : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	gMainWin::GetIF()->LogWrite(buf);

	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID , nRoomIndex);
	

	EnterCriticalSection (&gMainWin::GetIF()->crit[nRoomIndex]);

	gGPC->m_bSyncronize[nRoomIndex][nInRoomIndex] = true;

	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
		if(gRC->m_rooms[nRoomIndex].szRoomMaxPlayer[i][0] != '\0') // m_isGamePlayer[nRoomIndex][i] == true;
			if(! gGPC->m_bSyncronize[nRoomIndex][i])	{
				LeaveCriticalSection (&gMainWin::GetIF()->crit[nRoomIndex]);
				return ;
			}

	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
		if(gRC->m_rooms[nRoomIndex].szRoomMaxPlayer[i][0] != '\0') // m_isGamePlayer[nRoomIndex][i] == true;
			gGPC->m_bSyncronize[nRoomIndex][i] = false;
	

	LeaveCriticalSection (&gMainWin::GetIF()->crit[nRoomIndex]);
	
	int i,j,k;
	int randSubjectIndex;

	int remainSubjectIndex[CLASSNUM];
	int remainSubjectCount = 0;

	for (k = 0 ; k < ROOMMAXPLAYER ; k++)	{
		if (gRC->m_rooms[nRoomIndex].szRoomMaxPlayer[k][0] == '\0')
			continue;
		for (i=0;i< MAXSUBJECT ; i++)	{
			for (j=0;j<CLASSNUM ; j++)
				remainSubjectIndex[j] = true;
			while(m_submitSubjectPlayer[nRoomIndex][k][i] == AVAILSEAT && remainSubjectCount < CLASSNUM)	{
				randSubjectIndex = rand()%CLASSNUM;
				if (!putSubject(nRoomIndex , k , randSubjectIndex))	{	//실패
					if (remainSubjectIndex[randSubjectIndex])					remainSubjectCount++;
					remainSubjectIndex[randSubjectIndex] = false;
				}
			}
		}

	}
	
	gGamePlayerContainer::GetIF()->pk_maingamestart_rep(nRoomIndex);
	
}



void gSubmitCore::Release()
{
		
}

