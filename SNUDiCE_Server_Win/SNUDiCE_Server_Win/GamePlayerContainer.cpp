#include "GamePlayerContainer.h"
#include "RoomCore.h"
#include "TileContainer.h"
#include "PlayerContainer.h"
#include "MainWin.h"
#include "SubmitCore.h"

#include <stdio.h>

#define CHARDATAFILE ".\\chardata.dat"

static gGamePlayerContainer s_GamePlayerContainer;

gGamePlayerContainer *gGamePlayerContainer::GetIF()
{
	return &s_GamePlayerContainer;
}

bool gGamePlayerContainer::SetUp()
{
	FILE  *fp;
	fp = fopen(CHARDATAFILE, "rt");
	if(!fp)
		return false;
	int   i, k;
	int   nIndex = 0;  // 몇번째 캐릭터 입력중이냐
	int   nCount;   // 뭐입력중이나. 0 ; 이름, 1; 단대 .. .
	char  szBuf[256];
	char  szTemp[256];
	while( fgets(szBuf, 256, fp) != NULL)
	{
		if(szBuf[0] == '/' && szBuf[1] == '/')
			continue;        // 주석 건너뛰기
		i = 0;
		k = 0;
		nCount = 0;
		while(szBuf[i] != '\n')
		{
			if(szBuf[i] == ',')
			{
				szTemp[k] = NULL;
				switch(nCount++)
				{
				case 0: // 이름
					strcpy(m_CharInfo[nIndex].szName, szTemp);
					break;
				case 1: // 단과대학
					strcpy(m_CharInfo[nIndex].szCollege, szTemp);
					break;
				case 2: // 성별
					if( strcmp(szTemp, "남") == 0 )
						m_CharInfo[nIndex].bMale = true;
					else
						m_CharInfo[nIndex].bMale = false;
					break;
				case 3: // 언어
					m_CharInfo[nIndex].nLang = atoi(szTemp);
					break;
				case 4: // 수리
					m_CharInfo[nIndex].nMath = atoi(szTemp);
					break;
				case 5: // 예술
					m_CharInfo[nIndex].nArt = atoi(szTemp);
					break;
				case 6: // 체력
					m_CharInfo[nIndex].nStamina = atoi(szTemp);
					break;
				case 7: // 4면체
					m_CharInfo[nIndex].nDice4 = atoi(szTemp);
					break;
				case 8: // 6면체
					m_CharInfo[nIndex].nDice6 = atoi(szTemp);
					break;
				}
				k = 0;
			}
			else if(szBuf[i] != '\t')
				szTemp[k++] = szBuf[i];
			i++;
		}
		nIndex++;
	}
	fclose(fp);

	return true;
}


bool gGamePlayerContainer::init(int nRoomIndex)		
{
	CLASSTYPE classtype[ROOMMAXPLAYER];
	gRoomCore *gRC = gRoomCore::GetIF();
	gTileContainer *gTC = gTileContainer::GetIF();
	gSubmitCore *gSC = gSubmitCore::GetIF();
	gRC->FindClasstypeFromIDs_RMP(nRoomIndex,classtype);

	memset(m_GamePlayer[nRoomIndex], 0, sizeof(GAMEPLAYER) * ROOMMAXPLAYER);

	

	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)		
		// GAMEPLAYER의 정보 Setting과 
		// 그 외의 gGamePlayerContainer의 정보를 분리하여 저장하는 형식을 보여주면 더 깔끔하지 않을까?
	{
		if(gRC->m_rooms[nRoomIndex].szRoomMaxPlayer[i][0] == '\0') {
			m_isGamePlayer[nRoomIndex][i] = false;
		}
		else {
			m_isGamePlayer[nRoomIndex][i] = true;
			m_isNokdu[nRoomIndex][i] = false;			
			strcpy(m_GamePlayer[nRoomIndex][i].szID,gRC->m_rooms[nRoomIndex].szRoomMaxPlayer[i]);
			m_GamePlayer[nRoomIndex][i].ctype = classtype[i];
			m_GamePlayer[nRoomIndex][i].nLang = m_CharInfo[classtype[i]].nLang;
			m_GamePlayer[nRoomIndex][i].nMath = m_CharInfo[classtype[i]].nMath;
			m_GamePlayer[nRoomIndex][i].nArt = m_CharInfo[classtype[i]].nArt;
			m_GamePlayer[nRoomIndex][i].nStamina = m_CharInfo[classtype[i]].nStamina;
			m_GamePlayer[nRoomIndex][i].nMaxStamina = m_CharInfo[classtype[i]].nStamina;
			m_GamePlayer[nRoomIndex][i].nDice4 = m_CharInfo[classtype[i]].nDice4;
			m_GamePlayer[nRoomIndex][i].nDice6 = m_CharInfo[classtype[i]].nDice6;
			// sangwoo temp (grade 관련)
			for(int j = 0 ; j < MAXSUBJECT ; j++) 
			m_GamePlayer[nRoomIndex][i].fGrade[j] = 0.7;
			m_GamePlayer[nRoomIndex][i].fAvGrade = 0.7;
			m_GamePlayer[nRoomIndex][i].nRank = 1;
			// end
			m_GamePlayer[nRoomIndex][i].nPos = gTC->m_xInitSpacePos * LINEY + gTC->m_yInitSpacePos;
			memcpy(m_GamePlayer[nRoomIndex][i].bySubIdx,
				gSC->m_submitSubjectPlayer[nRoomIndex][i],
				sizeof(BYTE)*MAXSUBJECT);
		}
		m_bSyncronize[nRoomIndex][i] = true;
	}

	FirstTurn(nRoomIndex);		// m_nTurn reset.
	m_nRound[nRoomIndex] = 0;

	return true;
}

void gGamePlayerContainer::pk_maingamestart_rep(int nRoomIndex)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	init(nRoomIndex);

	PK_MAINGAMESTART_REP rep;
	memcpy(rep.list,m_GamePlayer[nRoomIndex],sizeof(GAMEPLAYER)*ROOMMAXPLAYER);
	rep.nTurn = 0; // 치명적 temp - 당장 바꿔야지.

	gPC->PutModeToModeForAll(ECM_SUBMIT,nRoomIndex,ECM_GAME);
	
	gPC->SendSelect(PL_MAINGAMESTART_REP,sizeof(PK_MAINGAMESTART_REP),&rep,ECM_GAME,nRoomIndex);

	
}

void gGamePlayerContainer::pk_movestart_ask(PK_DEFAULT *pk,SOCKET sock)
{
	PK_MOVESTART_ASK		ask;		//from client
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();
	gRoomCore			*gRC = gRoomCore::GetIF();
	gTileContainer		*gTC = gTileContainer::GetIF();

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_MOVESTART_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_MOVESTART_ASK] %s\t message : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	OutputDebugString(buf);

	
	PK_MOVESTART_REP		rep;
	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);

	int nSum;
	rep.Dice4_1 = 0;
	rep.Dice4_2 = 0;
	rep.Dice6_1 = 0;
	rep.Dice6_2 = 0;
	switch(m_GamePlayer[nRoomIndex][nInRoomIndex].nDice4) {
	case 0:
		break;
	case 1:
		rep.Dice4_1 = rand()%4 + 1;
		break;
	case 2:
		rep.Dice4_1 = rand()%4 + 1;
		rep.Dice4_2 = rand()%4 + 1;
		break;
	}
	switch(m_GamePlayer[nRoomIndex][nInRoomIndex].nDice6) {
	case 0:
		break;
	case 1:
		rep.Dice6_1 = rand()%6 + 1;
		break;
	case 2:
		rep.Dice6_1 = rand()%6 + 1;
		rep.Dice6_2 = rand()%6 + 1;
		break;
	}
	nSum = rep.Dice4_1 + rep.Dice4_2 + rep.Dice6_1 + rep.Dice6_2;
	if(m_isNokdu[nRoomIndex][nInRoomIndex]) nSum *= -1;
	rep.nDist = nSum;

	int des = gTC->destination(m_GamePlayer[nRoomIndex][nInRoomIndex].nPos,rep.nDist);
	if(des == gTC->m_xInitSpacePos * LINEY + gTC->m_yInitSpacePos) { // flip
		if(m_isNokdu[nRoomIndex][nInRoomIndex]) m_isNokdu[nRoomIndex][nInRoomIndex] = false;
		else m_isNokdu[nRoomIndex][nInRoomIndex] = true;
	}
	m_GamePlayer[nRoomIndex][nInRoomIndex].nPos = des;

	PushbSynAllPlayer(nRoomIndex,false);

	gPC->SendSelect(PL_MOVESTART_REP,sizeof(PK_MOVESTART_REP),&rep,ECM_GAME,nRoomIndex);
	//gMainWin::GetIF()->Send(PL_MOVESTART_REP,sizeof(PK_MOVESTART_REP),&rep,ask.szID);
}

void gGamePlayerContainer::PushbSynAllPlayer(int nRoomIndex,bool bSyn)
{
	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
		//if(m_GamePlayer[nRoomIndex][i].szID[0]!='\0')
		if(m_isGamePlayer[nRoomIndex][i])
			m_bSyncronize[nRoomIndex][i] = bSyn;
}


bool gGamePlayerContainer::isbSynAllTrue(int nRoomIndex)
{
	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
		//if(m_GamePlayer[nRoomIndex][i].szID[0]!='\0')
		if(m_isGamePlayer[nRoomIndex][i])
			if(!m_bSyncronize[nRoomIndex][i]) 
				return false;
	return true;
}


void gGamePlayerContainer::pk_moveend_ask(PK_DEFAULT *pk,SOCKET sock)
{
	PK_MOVEEND_ASK		ask;		//from client
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();
	gRoomCore			*gRC = gRoomCore::GetIF();
	gTileContainer		*gTC = gTileContainer::GetIF();

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];
	
	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_MOVEEND_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_MOVEEND_ASK] %s\t message : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	OutputDebugString(buf);

	
	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);
	char szTurnID[IDLENGTH];
	strcpy(szTurnID,m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].szID);

	if(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos == ask.nDestPos) {
		m_bSyncronize[nRoomIndex][nInRoomIndex] = true;

		if(isbSynAllTrue(nRoomIndex)) {
			PushbSynAllPlayer(nRoomIndex,false);
			if(gTC->m_tileMap[ask.nDestPos].tileType==TY_BUS)
				pk_busmovechoose_rep(nRoomIndex,szTurnID);
			else			
				pk_nextturn_rep(nRoomIndex);			
		}
	}
	else {
		wsprintf(buf,"server : %d %d , client : %d %d player : %s \n",
			(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos)/LINEY,
			(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos)%LINEY,
			ask.nDestPos/LINEY,
			ask.nDestPos%LINEY,
			ask.szID);
		OutputDebugString("[pk_moveend_ask] 심각한 Error, 보안 주의 요망, 서버와 클라이언트의 연산 결과가 다름\n");
		OutputDebugString(buf);
		OutputDebugString("이 방은 더 이상 동작하지 않습니다.\n");
	}
}

void gGamePlayerContainer::pk_nextturn_rep (int nRoomIndex)
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	PK_NEXTTURN_REP		rep;

	rep.nNowTurn = m_nTurn[nRoomIndex];
	NextTurn(nRoomIndex);
	rep.nNextTurn = m_nTurn[nRoomIndex];

	gPC->SendSelect(PL_NEXTTURN_REP,sizeof(PK_NEXTTURN_REP),&rep,ECM_GAME,nRoomIndex);
}

void gGamePlayerContainer::pk_busmovechoose_rep(int nRoomIndex,char* szID)
{
	PK_BUSMOVECHOOSE_REP	rep;

	rep.nNowTurn = m_nTurn[nRoomIndex];
	gMainWin::GetIF()->Send(PL_BUSMOVECHOOSE_REP,sizeof(rep),&rep,szID);
}


void gGamePlayerContainer::pk_busmoveselect_ask(PK_DEFAULT *pk,SOCKET sock)
{
	PK_BUSMOVESELECT_ASK		ask;		//from client
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();
	gRoomCore			*gRC = gRoomCore::GetIF();
	gTileContainer		*gTC = gTileContainer::GetIF();

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_BUSMOVESELECT_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_BUSMOVESELECT_ASK] %s\t message : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	OutputDebugString(buf);

	PK_BUSMOVESTART_REP		rep;

	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);	
	if(nInRoomIndex != m_nTurn[nRoomIndex])
		return; // 보낸 놈이 지금 턴 놈이 아님.
	int dis = gTC->distance(m_GamePlayer[nRoomIndex][nInRoomIndex].nPos,ask.nPos);
	m_GamePlayer[nRoomIndex][nInRoomIndex].nPos = ask.nPos;
	// hard coding
	if(ask.nPos == 2*LINEY+17) 
		m_isNokdu[nRoomIndex][nInRoomIndex] = true;
	else
		m_isNokdu[nRoomIndex][nInRoomIndex] = false;
	// end

	rep.nDist = dis;

	gPC->SendSelect(PL_BUSMOVESTART_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);
}

void gGamePlayerContainer::pk_busmoveend_ask(PK_DEFAULT *pk,SOCKET sock)
{
	PK_BUSMOVEEND_ASK		ask;		//from client
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();
	gRoomCore			*gRC = gRoomCore::GetIF();
	gTileContainer		*gTC = gTileContainer::GetIF();

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_BUSMOVEEND_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_BUSMOVEEND_ASK] %s\t message : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	OutputDebugString(buf);


	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);

	if(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos == ask.nDestPos) {
		m_bSyncronize[nRoomIndex][nInRoomIndex] = true;

		if(isbSynAllTrue(nRoomIndex)) {
			PushbSynAllPlayer(nRoomIndex,false);
			pk_nextturn_rep(nRoomIndex);
		}
	}
	else {
		wsprintf(buf,"server : %d %d , client : %d %d player : %s room : %d\n",
			(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos)/LINEY,
			(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos)%LINEY,
			ask.nDestPos/LINEY,
			ask.nDestPos%LINEY,
			ask.szID,
			nRoomIndex);
		OutputDebugString("[pk_moveend_ask] 심각한 Error, 보안 주의 요망, 서버와 클라이언트의 연산 결과가 다름\n");
		OutputDebugString(buf);
		OutputDebugString("이 방은 더 이상 동작하지 않습니다.\n");
	}
}




void gGamePlayerContainer::FirstTurn(int nRoomIndex)
{
	m_nTurn[nRoomIndex] = 0;
	for(int i = 0 ; i < MAXROOM ; i++) {
		//if(m_GamePlayer[nRoomIndex][i].szID[0]!='\0') { 
		if(m_isGamePlayer[nRoomIndex][i]) {
			m_nTurn[nRoomIndex] = i;
			break;
		}
	}
}


void gGamePlayerContainer::NextTurn(int nRoomIndex)
{
	while(1)
	{
		m_nTurn[nRoomIndex]++;
		if(m_nTurn[nRoomIndex]==ROOMMAXPLAYER) {
			m_nTurn[nRoomIndex] = 0;
			m_nRound[nRoomIndex]++;
		}
		//if(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].szID[0]!='\0') 
		if(m_isGamePlayer[nRoomIndex][m_nTurn[nRoomIndex]])
			break;

	}
}


void gGamePlayerContainer::Release()
{
	
}