#include "GamePlayerContainer.h"
#include "RoomCore.h"
#include "TileContainer.h"
#include "PlayerContainer.h"
#include "MainWin.h"
#include "SubmitCore.h"
#include "SubjectContainer.h"

#include <stdio.h>
#include <time.h>

#define CHARDATAFILE ".\\chardata.dat"
#define ENDROUND	20

static gGamePlayerContainer s_GamePlayerContainer;

gGamePlayerContainer *gGamePlayerContainer::GetIF()
{
	return &s_GamePlayerContainer;
}

bool gGamePlayerContainer::SetUp()
{
	srand((unsigned)time(NULL));

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
			//m_isNokdu[nRoomIndex][i] = true;			

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
			for(int j = 0 ; j < MAXSUBJECT ; j++) 
				m_nSubjectCount[nRoomIndex][i][j] = 90;
			m_GamePlayer[nRoomIndex][i].nPos = gTC->m_xInitSpacePos * LINEY + gTC->m_yInitSpacePos;
			//m_GamePlayer[nRoomIndex][i].nPos = 2 * LINEY + 17;

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

	if(m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina<=0) {
		staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],1);
		pk_popinfo_rep(nRoomIndex,1,0);	
		pk_gameplayerinfo_rep(nRoomIndex);
		pk_nextturn_rep(nRoomIndex);
		return;
	}

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

	wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,000,sock);
	OutputDebugString(buf);
	
	
	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_MOVEEND_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_MOVEEND_ASK] %s\t message : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	OutputDebugString(buf);

	wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,111,sock);
	OutputDebugString(buf);
	
	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);
	char szTurnID[IDLENGTH];
	strcpy(szTurnID,m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].szID);

	wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,222,sock);
	OutputDebugString(buf);

	if(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos == ask.nDestPos) {
		m_bSyncronize[nRoomIndex][nInRoomIndex] = true;
		
		wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,333,sock);
		OutputDebugString(buf);
		
		if(isbSynAllTrue(nRoomIndex)) {
			PushbSynAllPlayer(nRoomIndex,false);
			if(gTC->m_tileMap[ask.nDestPos].tileType==TY_BUS) {
				OutputDebugString("TY_BUS\n");
				pk_busmovechoose_rep(nRoomIndex,szTurnID);
			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType==TY_CLASS) {
				OutputDebugString("TY_CLASS\n");
				int getAccomplishment = meetGrade(nRoomIndex,gTC->m_tileMap[ask.nDestPos].flag1);
				
				wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,444,sock);
				OutputDebugString(buf);
				
				GradeRankSyncronizer(nRoomIndex);

				wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,555,sock);
				OutputDebugString(buf);
					
				if(getAccomplishment!=-1) {
					OutputDebugString("TY_MySubject\n");
					wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,666,sock);
					OutputDebugString(buf);
					staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],-1);
					wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,777,sock);
					OutputDebugString(buf);
					pk_popinfo_rep(nRoomIndex,-1,getAccomplishment);

					wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,888,sock);
					OutputDebugString(buf);
				}
				pk_gameplayerinfo_rep(nRoomIndex);
				wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,999,sock);
				OutputDebugString(buf);
				pk_nextturn_rep(nRoomIndex);


			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType=TY_DRINK) {
				OutputDebugString("TY_DRINK\n");
				staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],-1);
				pk_popinfo_rep(nRoomIndex,-1,0);
				pk_gameplayerinfo_rep(nRoomIndex);
				pk_nextturn_rep(nRoomIndex);
				wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,000,sock);
				OutputDebugString(buf);
			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType==TY_STAMINA) {
				OutputDebugString("TY_STAMINA\n");
				staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],1);
				pk_popinfo_rep(nRoomIndex,1,0);
				pk_gameplayerinfo_rep(nRoomIndex);
				pk_nextturn_rep(nRoomIndex);
				wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,1111,sock);
				OutputDebugString(buf);
			}
			else {
				OutputDebugString("TY_NOTHING\n");
				pk_gameplayerinfo_rep(nRoomIndex);
				pk_nextturn_rep(nRoomIndex);
				wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,2222,sock);
				OutputDebugString(buf);
			}
		}
	}
	else {
		wsprintf(buf,"%d %d %d\n",m_GamePlayer[0][0].nPos,3333,sock);
		OutputDebugString(buf);
		wsprintf(buf,"server : %d %d , client : %d %d player : %s etc : %d %d\n",
			(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos)/LINEY,
			(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos)%LINEY,
			ask.nDestPos/LINEY,
			ask.nDestPos%LINEY,
			ask.szID,
			m_nTurn[nRoomIndex],
			nRoomIndex);
		OutputDebugString("[pk_moveend_ask] 심각한 Error, 보안 주의 요망, 서버와 클라이언트의 연산 결과가 다름\n");
		OutputDebugString(buf);
		OutputDebugString("이 방은 더 이상 동작하지 않습니다.\n");
	}
}

void gGamePlayerContainer::pk_nextturn_rep (int nRoomIndex)
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	PK_NEXTTURN_REP		rep;

	char	buf[128];

	rep.nNowTurn = m_nTurn[nRoomIndex];
	NextTurn(nRoomIndex);
	rep.nNextTurn = m_nTurn[nRoomIndex];
	wsprintf(buf,"[pk_nextturn_rep] room : %d befTurn : %d nextTurn : %d\n",nRoomIndex,rep.nNowTurn,rep.nNextTurn);
	OutputDebugString(buf);

	if(m_nRound[nRoomIndex]<ENDROUND)
		gPC->SendSelect(PL_NEXTTURN_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);
	else
		pk_gameend_rep(nRoomIndex);
}


void gGamePlayerContainer::pk_busmovechoose_rep(int nRoomIndex,char* szID)
{
	PK_BUSMOVECHOOSE_REP	rep;

	rep.nNowTurn = m_nTurn[nRoomIndex];
	gMainWin::GetIF()->Send(PL_BUSMOVECHOOSE_REP,sizeof(rep),&rep,szID);
}


void gGamePlayerContainer::pk_gameplayerinfo_rep (int nRoomIndex)
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	PK_GAMEPLAYERINFO_REP		rep;

	memcpy(rep.list,m_GamePlayer[nRoomIndex],sizeof(GAMEPLAYER)*ROOMMAXPLAYER);

	gPC->SendSelect(PL_GAMEPLAYERINFO_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);
}


void gGamePlayerContainer::pk_popinfo_rep(int nRoomIndex,int stamina,int accomplishment) {

	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	PK_POPINFO_REP				rep;

	int nInRoomIndex= m_nTurn[nRoomIndex];
	strcpy(rep.szID,m_GamePlayer[nRoomIndex][nInRoomIndex].szID);
	rep.nLang = 0;
	rep.nMath = 0;
	rep.nArt = 0;
	rep.nStamina = stamina;
	rep.nGrade = accomplishment;

	gPC->SendSelect(PL_POPINFO_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);
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

//////////////////////////////////////////////////////////////////////////
/// 학점 관련 함수
//////////////////////////////////////////////////////////////////////////

int gGamePlayerContainer::meetGrade(int nRoomIndex,int subjectIndex) // subjectIndex = flag1
{	// int 값으로 resultMIC 값을 return 하면 되겠네..
	gSubjectContainer *gSCt = gSubjectContainer::GetIF();

	int nInRoomIndex = m_nTurn[nRoomIndex];
	
	int resultMIC = -1;	// error
	for(int i = 0 ; i < MAXSUBJECT ; i++ ){
		if(m_GamePlayer[nRoomIndex][nInRoomIndex].bySubIdx[i]==subjectIndex){
			if(gSCt->m_subject[subjectIndex].flag1==0) {
				resultMIC = meetItemCalculator(0,m_GamePlayer[nRoomIndex][nInRoomIndex].nLang);
				m_nSubjectCount[nRoomIndex][nInRoomIndex][i] += resultMIC;
			}
			else if(gSCt->m_subject[subjectIndex].flag1==1) {
				resultMIC = meetItemCalculator(1,m_GamePlayer[nRoomIndex][nInRoomIndex].nMath);
				m_nSubjectCount[nRoomIndex][nInRoomIndex][i] += resultMIC;
			}
			else if(gSCt->m_subject[subjectIndex].flag1==2) {
				resultMIC = meetItemCalculator(2,m_GamePlayer[nRoomIndex][nInRoomIndex].nArt);
				m_nSubjectCount[nRoomIndex][nInRoomIndex][i] += resultMIC;
			}
			break;
		}
	}
	
	return resultMIC;
}

int gGamePlayerContainer::meetItemCalculator(int classType,int originalVal) {
	/*
	itemContainer* itemcontainer = itemContainer::GetIF();

	int i;
	int convertedVal = originalVal;

	for (i = 0 ; i < MAXCARD ; i++){

		if(m_itemCooltime[i]==0) continue;


		if(itemcontainer->m_item[i].m_effect==0 || itemcontainer->m_item[i].m_effect==classType+1 ){

			if(itemcontainer->m_item[i].m_flagHigh==0) convertedVal += itemcontainer->m_item[i].m_flagLow;
			else if (itemcontainer->m_item[i].m_flagHigh==1){
				convertedVal -= itemcontainer->m_item[i].m_flagLow;
			}
		}
	}
	for (i = 0 ; i < MAXCARD ; i++){
		if(m_itemCooltime[i]==0) continue;
		if(itemcontainer->m_item[i].m_effect==0 || itemcontainer->m_item[i].m_effect==classType+1 ){
			if(itemcontainer->m_item[i].m_flagHigh==2) convertedVal *= itemcontainer->m_item[i].m_flagLow;
		}
	}

	if(convertedVal < 0 ) convertedVal = 0;
*/
	return originalVal*20;
}


void gGamePlayerContainer::GradeRankSyncronizer(int nRoomIndex)	// 이 함수의 존재로 인해, grade와 rank는 비동기화된 개념임.
{	// count만이 진정한 동기화된 개념.
	gSubjectContainer *gSCt = gSubjectContainer::GetIF();
	for(int i = 0 ; i < ROOMMAXPLAYER ; i++) {
		if(m_isGamePlayer[nRoomIndex][i]) {
			for(int j = 0 ; j < MAXSUBJECT ; j++) {
				m_GamePlayer[nRoomIndex][i].fGrade[j] = 
					gSCt->gradeExpectOne(m_nSubjectCount[nRoomIndex][i][j],m_nRound[nRoomIndex]);
			}
			m_GamePlayer[nRoomIndex][i].fAvGrade = 
				gSCt->gradeAverage(m_nSubjectCount[nRoomIndex][i],m_nRound[nRoomIndex],MAXSUBJECT);
		}
	}
	for(int i = 0 ;i < ROOMMAXPLAYER ; i++) {
		if(m_isGamePlayer[nRoomIndex][i]) {
			m_GamePlayer[nRoomIndex][i].nRank = Rank(nRoomIndex,i);			
		}
	}	
}


int gGamePlayerContainer::Rank(int nRoomIndex,int nInRoomIndex)
{
	float myAv = m_GamePlayer[nRoomIndex][nInRoomIndex].fAvGrade;
	int rank = 1;
	for(int i = 0 ; i < ROOMMAXPLAYER ; i++) {
		if(m_isGamePlayer[nRoomIndex][i]) {
			if(m_GamePlayer[nRoomIndex][i].fAvGrade > myAv)
				rank++;
		}
	}
	return rank;
}


void gGamePlayerContainer::staminaConvert(int nRoomIndex,int nInRoomIndex,int nPlusMinus)
{
	if(m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina + nPlusMinus >= 
		m_GamePlayer[nRoomIndex][nInRoomIndex].nMaxStamina)
		m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina = m_GamePlayer[nRoomIndex][nInRoomIndex].nMaxStamina;
	else if(m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina + nPlusMinus <= 0)
		m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina = 0;
	else m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina += nPlusMinus;
}

int gGamePlayerContainer::WhoIsRankOne(int nRoomIndex)
{
	int WinnerIndex = -1;
	float WinnerScore = 0.0;
	char buf[128];
	for(int i = 0 ; i < ROOMMAXPLAYER ; i++) {
		if(m_isGamePlayer[nRoomIndex][i]) {
			if(WinnerScore <= m_GamePlayer[nRoomIndex][i].fAvGrade) {
				WinnerIndex = i;
				WinnerScore = m_GamePlayer[nRoomIndex][i].fAvGrade;
			}
		}
	}
	wsprintf(buf,"[] %d\n",WinnerIndex);
	OutputDebugString(buf);

	return WinnerIndex;
}

void gGamePlayerContainer::pk_gameend_rep(int nRoomIndex)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	PK_GAMEEND_REP	rep;

	int nWinnerIndex = WhoIsRankOne(nRoomIndex);
	strcpy(rep.szID,m_GamePlayer[nRoomIndex][nWinnerIndex].szID);
	
	gPC->SendSelect(PL_GAMEEND_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);

}