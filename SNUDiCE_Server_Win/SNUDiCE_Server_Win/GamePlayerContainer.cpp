#include "GamePlayerContainer.h"
#include "RoomCore.h"
#include "TileContainer.h"
#include "PlayerContainer.h"
#include "MainWin.h"
#include "SubmitCore.h"
#include "SubjectContainer.h"
#include "ItemContainer.h"


#include <time.h>


#define ENDROUND	1

static gGamePlayerContainer s_GamePlayerContainer;

gGamePlayerContainer *gGamePlayerContainer::GetIF()
{
	return &s_GamePlayerContainer;
}

//////////////////////////////////////////////////////////////////////////
/// SetUp & Init
//////////////////////////////////////////////////////////////////////////


bool gGamePlayerContainer::SetUp()
{
//	srand((unsigned)time(NULL));

	return true;
}


bool gGamePlayerContainer::init(int nRoomIndex)		
{
	CLASSTYPE classtype[ROOMMAXPLAYER];
	gRoomCore *gRC = gRoomCore::GetIF();
	gTileContainer *gTC = gTileContainer::GetIF();
	gSubmitCore *gSC = gSubmitCore::GetIF();
	gRC->FindClasstypeFromIDs_RMP(nRoomIndex,classtype);
	gCharinfo	*gC = gCharinfo::GetIF();

	memset(m_GamePlayer[nRoomIndex], 0, sizeof(GAMEPLAYER) * ROOMMAXPLAYER);

	

	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)		
		// GAMEPLAYER�� ���� Setting�� 
		// �� ���� gGamePlayerContainer�� ������ �и��Ͽ� �����ϴ� ������ �����ָ� �� ������� ������?
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

			m_GamePlayer[nRoomIndex][i].nLang = gC->m_CharInfo[classtype[i]].nLang;
			m_GamePlayer[nRoomIndex][i].nMath = gC->m_CharInfo[classtype[i]].nMath;
			m_GamePlayer[nRoomIndex][i].nArt = gC->m_CharInfo[classtype[i]].nArt;
			m_GamePlayer[nRoomIndex][i].nStamina = gC->m_CharInfo[classtype[i]].nStamina;
			m_GamePlayer[nRoomIndex][i].nMaxStamina = gC->m_CharInfo[classtype[i]].nStamina;
			m_GamePlayer[nRoomIndex][i].nDice4 = gC->m_CharInfo[classtype[i]].nDice4;
			m_GamePlayer[nRoomIndex][i].nDice6 = gC->m_CharInfo[classtype[i]].nDice6;
			
			// sangwoo temp (grade ����)
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
			
			m_GamePlayer[nRoomIndex][i].nItem[0] = 0;
			for(int j = 1 ; j < MAXITEMNUM ; j++)
				m_GamePlayer[nRoomIndex][i].nItem[j] = -1;

			for(int j = 0 ; j < ITEMNUM ; j++)
				m_ItemCoolTime[nRoomIndex][i][j] = 0;
		}
		m_bSyncronize[nRoomIndex][i] = true;
	}

	FirstTurn(nRoomIndex);		// m_nTurn reset.
	m_nRound[nRoomIndex] = 0;

	return true;
}

void gGamePlayerContainer::Release()
{

}


//////////////////////////////////////////////////////////////////////////
/// packet
//////////////////////////////////////////////////////////////////////////

void gGamePlayerContainer::pk_maingamestart_rep(int nRoomIndex)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	init(nRoomIndex);

	PK_MAINGAMESTART_REP rep;
	memcpy(rep.list,m_GamePlayer[nRoomIndex],sizeof(GAMEPLAYER)*ROOMMAXPLAYER);
	rep.nTurn = 0; // ġ���� temp - ���� �ٲ����.

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
	movePlayer(nRoomIndex,nInRoomIndex,des);

	PushbSynAllPlayer(nRoomIndex,false);

	gPC->SendSelect(PL_MOVESTART_REP,sizeof(PK_MOVESTART_REP),&rep,ECM_GAME,nRoomIndex);
	//gMainWin::GetIF()->Send(PL_MOVESTART_REP,sizeof(PK_MOVESTART_REP),&rep,ask.szID);
}

void gGamePlayerContainer::movePlayer(int nRoomIndex,int nInRoomIndex,int des,bool bIsBus)
{
	gTileContainer *gTC = gTileContainer::GetIF();
	if(bIsBus)
	{
		if(des == 2*LINEY+17) 
			m_isNokdu[nRoomIndex][nInRoomIndex] = true;
		else
			m_isNokdu[nRoomIndex][nInRoomIndex] = false;
	}
	else if(!bIsBus && des == gTC->m_xInitSpacePos * LINEY + gTC->m_yInitSpacePos) 
	{ // flip
		if(m_isNokdu[nRoomIndex][nInRoomIndex]) 
			m_isNokdu[nRoomIndex][nInRoomIndex] = false;
		else 
			m_isNokdu[nRoomIndex][nInRoomIndex] = true;
	}
	m_GamePlayer[nRoomIndex][nInRoomIndex].nPos = des;
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

	
	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);
	char szTurnID[IDLENGTH];
	strcpy(szTurnID,m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].szID);



	if(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos == ask.nDestPos) {
		m_bSyncronize[nRoomIndex][nInRoomIndex] = true;
			
		if(isbSynAllTrue(nRoomIndex)) {	// ��� ���갡 ������...
			PushbSynAllPlayer(nRoomIndex,false);
			if(gTC->m_tileMap[ask.nDestPos].tileType==TY_BUS) {
				OutputDebugString("TY_BUS\n");
				pk_busmovechoose_rep(nRoomIndex,szTurnID);
			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType==TY_CLASS) {
				OutputDebugString("TY_CLASS\n");
				int getAccomplishment = meetGrade(nRoomIndex,gTC->m_tileMap[ask.nDestPos].flag1);
				
				GradeRankSyncronizer(nRoomIndex);

					
				if(getAccomplishment!=-1) {
					OutputDebugString("TY_MySubject\n");
					staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],-1);
					pk_popinfo_rep(nRoomIndex,-1,getAccomplishment);

				}
				pk_gameplayerinfo_rep(nRoomIndex);
				pk_nextturn_rep(nRoomIndex);
			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType==TY_DRINK) {
				OutputDebugString("TY_DRINK\n");
				staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],-1);
				pk_popinfo_rep(nRoomIndex,-1,0);
				pk_gameplayerinfo_rep(nRoomIndex);
				pk_nextturn_rep(nRoomIndex);
			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType==TY_STAMINA) {
				OutputDebugString("TY_STAMINA\n");
				staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],1);
				pk_popinfo_rep(nRoomIndex,1,0);
				pk_gameplayerinfo_rep(nRoomIndex);
				pk_nextturn_rep(nRoomIndex);
			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType==TY_ITEM) {
				OutputDebugString("TY_ITEM\n");
				getItem(nRoomIndex,m_nTurn[nRoomIndex]);
				pk_gameplayerinfo_rep(nRoomIndex);
				pk_nextturn_rep(nRoomIndex);
			}
			else {
				OutputDebugString("TY_NOTHING\n");
				pk_gameplayerinfo_rep(nRoomIndex);
				pk_nextturn_rep(nRoomIndex);
			}
		}
	}
	else {
		OutputDebugString(buf);
		wsprintf(buf,"server : %d %d , client : %d %d player : %s etc : %d %d\n",
			(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos)/LINEY,
			(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos)%LINEY,
			ask.nDestPos/LINEY,
			ask.nDestPos%LINEY,
			ask.szID,
			m_nTurn[nRoomIndex],
			nRoomIndex);
		OutputDebugString("[pk_moveend_ask] �ɰ��� Error, ���� ���� ���, ������ Ŭ���̾�Ʈ�� ���� ����� �ٸ�\n");
		OutputDebugString(buf);		OutputDebugString("�� ���� �� �̻� �������� �ʽ��ϴ�.\n");
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
		return; // ���� ���� ���� �� ���� �ƴ�.
	int dis = gTC->distance(m_GamePlayer[nRoomIndex][nInRoomIndex].nPos,ask.nPos);
	
	movePlayer(nRoomIndex,nInRoomIndex,ask.nPos,true);

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
		OutputDebugString("[pk_moveend_ask] �ɰ��� Error, ���� ���� ���, ������ Ŭ���̾�Ʈ�� ���� ����� �ٸ�\n");
		OutputDebugString(buf);
		OutputDebugString("�� ���� �� �̻� �������� �ʽ��ϴ�.\n");
	}
}

void gGamePlayerContainer::pk_gameend_rep(int nRoomIndex)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	PK_GAMEEND_REP	rep;

	int nWinnerIndex = WhoIsRankOne(nRoomIndex);
	strcpy(rep.szID,m_GamePlayer[nRoomIndex][nWinnerIndex].szID);

	gPC->SendSelect(PL_GAMEEND_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);
}

//////////////////////////////////////////////////////////////////////////
/// info ���� rep �Լ�
//////////////////////////////////////////////////////////////////////////

void gGamePlayerContainer::pk_gameplayerinfo_rep (int nRoomIndex)
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	PK_GAMEPLAYERINFO_REP		rep;
	pk_subGameplayerinfo_rep(nRoomIndex,&rep);

	memcpy(rep.list,m_GamePlayer[nRoomIndex],sizeof(GAMEPLAYER)*ROOMMAXPLAYER);

	gPC->SendSelect(PL_GAMEPLAYERINFO_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);
}

void gGamePlayerContainer::pk_subGameplayerinfo_rep(int nRoomIndex,PK_GAMEPLAYERINFO_REP* rep)
{	// �����ϰ� stat ������ ���� �Լ�. 
	// stat �����ۿ� ���� �ɷ�ġ�� ����Ǹ�, rep�� ������ ����ä�� ������ �����ϴ� �Լ��̴�.
	gItemContainer		*gIC = gItemContainer::GetIF();
	for(int i = 0 ; i < ROOMMAXPLAYER ; i++) {
		for(int j = 0 ; j < ITEMNUM ; j++) {	// multi item
			if(gIC->m_ItemList[j].nMulti>0 && m_ItemCoolTime[nRoomIndex][i][j] > 0) {
				rep->list[i].nLang *= gIC->m_ItemList[j].nMulti;
				rep->list[i].nMath *= gIC->m_ItemList[j].nMulti;
				rep->list[i].nArt *= gIC->m_ItemList[j].nMulti;
			}
		}
		for(int j = 0 ; j < ITEMNUM ; j++) {	// plusminus item
			if(gIC->m_ItemList[j].nLang + gIC->m_ItemList[j].nMath + gIC->m_ItemList[j].nArt > 0
				&& m_ItemCoolTime[nRoomIndex][i][j] > 0) {
				rep->list[i].nLang += gIC->m_ItemList[j].nLang;
				rep->list[i].nMath += gIC->m_ItemList[j].nMath;
				rep->list[i].nArt += gIC->m_ItemList[j].nArt;
			}
		}
	}
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

//////////////////////////////////////////////////////////////////////////
/// ���� ���� �Լ�
//////////////////////////////////////////////////////////////////////////

int gGamePlayerContainer::meetGrade(int nRoomIndex,int subjectIndex) // subjectIndex = flag1
{	// int ������ resultMIC ���� return �ϸ� �ǰڳ�..
	gSubjectContainer *gSCt = gSubjectContainer::GetIF();
	gItemContainer *gICt = gItemContainer::GetIF();

	int nInRoomIndex = m_nTurn[nRoomIndex];

	int resultMIC = -1;	// error
	for(int i = 0 ; i < MAXSUBJECT ; i++ ){
		if(m_GamePlayer[nRoomIndex][nInRoomIndex].bySubIdx[i]==subjectIndex){
			if(gSCt->m_subject[subjectIndex].flag1==0) {		// ���
				resultMIC = meetItemCalculator(nRoomIndex,nInRoomIndex,0,m_GamePlayer[nRoomIndex][nInRoomIndex].nLang);
			}
			else if(gSCt->m_subject[subjectIndex].flag1==1) {	// ����
				resultMIC = meetItemCalculator(nRoomIndex,nInRoomIndex,1,m_GamePlayer[nRoomIndex][nInRoomIndex].nMath);
			}
			else if(gSCt->m_subject[subjectIndex].flag1==2) {	// ��ü��
				resultMIC = meetItemCalculator(nRoomIndex,nInRoomIndex,2,m_GamePlayer[nRoomIndex][nInRoomIndex].nArt);
			}

			if(resultMIC != -1) 
			{
				for(int j = 0 ; j < ITEMNUM ; j++) // ITEM_NOCLASS �� ȿ���� ����
				{
					if(gICt->m_ItemList[j].type == ITEM_NOCLASS &&
						m_ItemCoolTime[nRoomIndex][nInRoomIndex][j]>0) {
						m_ItemCoolTime[nRoomIndex][nInRoomIndex][j] = 0;
						resultMIC = 0;
						break;
					}
				}
				if(resultMIC == 0) break;

				m_nSubjectCount[nRoomIndex][nInRoomIndex][i] += resultMIC; // �������� ���� ���� ȿ��
				
				for(int j = 0 ; j < ITEMNUM ; j++) // ITEM_TOGETHERCLASS �� ȿ���� ����
				{
					if(gICt->m_ItemList[j].type == ITEM_TOGETHERCLASS &&
						m_ItemCoolTime[nRoomIndex][nInRoomIndex][j]>0)
					{
						m_nSubjectCount[nRoomIndex][nInRoomIndex]
						[m_ItemCoolTime[nRoomIndex][nInRoomIndex][j]/100] += resultMIC;					
					}
				}
			}
			break;
		}
	}

	return resultMIC;
}


int gGamePlayerContainer::meetItemCalculator(int nRoomIndex,int nInRoomIndex,int classType,int originalVal) {
	gItemContainer *gIC = gItemContainer::GetIF();
	int t;
	for(int i = 0 ; i < ITEMNUM ; i++) {
		t = m_ItemCoolTime[nRoomIndex][nInRoomIndex][i];
		if(t > 0)
			if(gIC->m_ItemList[i].nMulti > 0) originalVal *= gIC->m_ItemList[i].nMulti;
	}
	for(int i = 0 ; i < ITEMNUM ; i++) {
		t = m_ItemCoolTime[nRoomIndex][nInRoomIndex][i];
		if(t > 0) {
			if(classType == 0 && gIC->m_ItemList[i].nLang > 0)	originalVal += gIC->m_ItemList[i].nLang;
			if(classType == 1 && gIC->m_ItemList[i].nMath > 0)	originalVal += gIC->m_ItemList[i].nMath;	
			if(classType == 2 && gIC->m_ItemList[i].nArt > 0)	originalVal += gIC->m_ItemList[i].nArt;
		}
	}
	return originalVal*20;
}


void gGamePlayerContainer::GradeRankSyncronizer(int nRoomIndex)	// �� �Լ��� ����� ����, grade�� rank�� �񵿱�ȭ�� ������.
{	// count���� ������ ����ȭ�� ����.
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


//////////////////////////////////////////////////////////////////////////
/// �� �Լ�
//////////////////////////////////////////////////////////////////////////


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
			releaseItemGlobal(nRoomIndex);
		}
		//if(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].szID[0]!='\0') 
		if(m_isGamePlayer[nRoomIndex][m_nTurn[nRoomIndex]])
			break;

	}
}


//////////////////////////////////////////////////////////////////////////
/// ī�� private ������ �Լ�
//////////////////////////////////////////////////////////////////////////

void gGamePlayerContainer::getItem(int nRoomIndex,int nInRoomIndex)
{
	for(int i = 0 ; i < MAXITEMNUM ; i++)
	{
		if(m_GamePlayer[nRoomIndex][nInRoomIndex].nItem[i] == -1) {
			m_GamePlayer[nRoomIndex][nInRoomIndex].nItem[i] = rand()%20;
			break;
		}
	}
}

void gGamePlayerContainer::pushItem(int nRoomIndex,int nInRoomIndex,int nItemID)
{
	for(int i = 0 ; i < MAXITEMNUM ; i++)
	{
		if(m_GamePlayer[nRoomIndex][nInRoomIndex].nItem[i] == nItemID) {
			for( ; i < MAXITEMNUM-1 ; i++) // shift
			{
				m_GamePlayer[nRoomIndex][nInRoomIndex].nItem[i] = 
					m_GamePlayer[nRoomIndex][nInRoomIndex].nItem[i+1];
			}
			m_GamePlayer[nRoomIndex][nInRoomIndex].nItem[i] = -1;

		}
	}
}

void gGamePlayerContainer::releaseItemGlobal(int nRoomIndex)
{
	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
	{
		if(m_isGamePlayer[nRoomIndex][i]) {
			for(int j = 0 ; j < ITEMNUM ; j++) {
				if(m_ItemCoolTime[nRoomIndex][i][j] > 100) {
					m_ItemCoolTime[nRoomIndex][i][j]--;
					if(m_ItemCoolTime[nRoomIndex][i][j]%100 == 0)
						m_ItemCoolTime[nRoomIndex][i][j] = 0;
				}
				else if(m_ItemCoolTime[nRoomIndex][i][j] > 0) 
					m_ItemCoolTime[nRoomIndex][i][j]--;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
/// ��ũ�γ����� �Լ�
//////////////////////////////////////////////////////////////////////////


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

//////////////////////////////////////////////////////////////////////////
/// ��¥ ��Ÿ
//////////////////////////////////////////////////////////////////////////

int gGamePlayerContainer::staminaConvert(int nRoomIndex,int nInRoomIndex,int nPlusMinus)
{
	int temp;
	if(m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina + nPlusMinus >= 
		m_GamePlayer[nRoomIndex][nInRoomIndex].nMaxStamina) {
		temp = m_GamePlayer[nRoomIndex][nInRoomIndex].nMaxStamina - 
			m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina;
		m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina = m_GamePlayer[nRoomIndex][nInRoomIndex].nMaxStamina;
		return temp;
	}
	else if(m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina + nPlusMinus <= 0) {
		temp = m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina;
		m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina = 0;
		return temp;
	}
	else {
		m_GamePlayer[nRoomIndex][nInRoomIndex].nStamina += nPlusMinus;
		return nPlusMinus;
	}
}


//////////////////////////////////////////////////////////////////////////
/// item use ����...
//////////////////////////////////////////////////////////////////////////

void gGamePlayerContainer::pk_itemuse_ask(PK_DEFAULT *pk,SOCKET sock)
{
	PK_ITEMUSE_ASK		ask;		//from client
	gPlayerContainer	*gPC =	gPlayerContainer::GetIF();
	gRoomCore			*gRC =	gRoomCore::GetIF();


	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_ITEMUSE_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_ITEMUSE_ASK] %s\t message : %s %d \n", inet_ntoa(clientAddr.sin_addr), ask.szID, ask.nItemID);
	OutputDebugString(buf);

	PK_ITEMUSE_REP		rep;

	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);	


	rep.result = ITEMUSE_SUCCESS;

	bool bTemp = itemUse(ask,nRoomIndex,nInRoomIndex,ask.nItemID);
	
	if(rep.result == ITEMUSE_ERROR)
		gMainWin::GetIF()->Send(PL_ITEMUSE_REP,sizeof(rep),&rep,ask.szID);
	else if(bTemp) {
		pk_gameplayerinfo_rep(nRoomIndex);
		pk_nextturn_rep(nRoomIndex);
	}
	

	//gPC->SendSelect(PL_ITEMUSE_REP,sizeof(rep),&rep,ECM_GAME,gPC->GetCoreFlag(ask.szID));
}




bool gGamePlayerContainer::itemUse (PK_ITEMUSE_ASK ask, int nRoomIndex, int nInRoomIndex, int itemIndex)
{	// nInRoomIndex�� �������� ����� ����, itemIndex�� 0-19 ������ ���״����...
	gItemContainer		*gIC =	gItemContainer::GetIF();
//	gPlayerContainer	*gPC =	gPlayerContainer::GetIF();
	gRoomCore			*gRC =	gRoomCore::GetIF();

	pushItem(nRoomIndex,nInRoomIndex,ask.nItemID);
	
	if(gIC->m_ItemList[ask.nItemID].nExistTurn > 0) {
		// ���� 0���� Ŭ ����...
		// �� ���Ǵ� �������� ��Ÿ�� �ִ� ������ �����.
		if(gIC->m_ItemList[ask.nItemID].type == ITEM_STAT)
		{
			switch (gIC->m_ItemList[ask.nItemID].target) {
				case TARGET_ME:
					m_ItemCoolTime[nRoomIndex][nInRoomIndex][ask.nItemID] 
					= gIC->m_ItemList[ask.nItemID].nExistTurn;
					break;
				case TARGET_OTHER:
					m_ItemCoolTime[nRoomIndex][gRC->FindPlayerIndexInTheRoom(ask.szTarget,nRoomIndex)]
					[ask.nItemID] = gIC->m_ItemList[ask.nItemID].nExistTurn;
					break;
				case TARGET_MEOTHER:
					m_ItemCoolTime[nRoomIndex][nInRoomIndex][ask.nItemID] 
					= gIC->m_ItemList[ask.nItemID].nExistTurn;
					m_ItemCoolTime[nRoomIndex][gRC->FindPlayerIndexInTheRoom(ask.szTarget,nRoomIndex)]
					[ask.nItemID] = gIC->m_ItemList[ask.nItemID].nExistTurn;
					break;
				case TARGET_ALLEXCEPTME:
					for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
					{
						if(m_isGamePlayer[nRoomIndex][i]&&i!=nInRoomIndex)
						{
							m_ItemCoolTime[nRoomIndex][i][ask.nItemID]
							= gIC->m_ItemList[ask.nItemID].nExistTurn;
						}
					}
					break;
			}
			return true;
		}
		else if(gIC->m_ItemList[ask.nItemID].type == ITEM_TOGETHERCLASS)
		{
			switch (gIC->m_ItemList[ask.nItemID].target) {
				case TARGET_OTHER:
					m_ItemCoolTime[nRoomIndex][nInRoomIndex][ask.nItemID]
					= gIC->m_ItemList[ask.nItemID].nExistTurn;
					m_ItemCoolTime[nRoomIndex][nInRoomIndex][ask.nItemID]
					+= gRC->FindPlayerIndexInTheRoom(ask.szTarget,nRoomIndex)*100;
					break;
			}
			return true;
		}
	}

	else {
		if(gIC->m_ItemList[ask.nItemID].type == ITEM_STAMINA) {
			switch(gIC->m_ItemList[ask.nItemID].target) {
				case TARGET_ME:
					staminaConvert(nRoomIndex,nInRoomIndex,gIC->m_ItemList[ask.nItemID].nStamina);
					break;
				case TARGET_OTHER:
					staminaConvert(nRoomIndex,gRC->FindPlayerIndexInTheRoom(ask.szTarget,nRoomIndex),
						gIC->m_ItemList[ask.nItemID].nStamina);
					break;
				case TARGET_MEOTHER:
					staminaConvert(nRoomIndex,nInRoomIndex,gIC->m_ItemList[ask.nItemID].nStamina);
					staminaConvert(nRoomIndex,gRC->FindPlayerIndexInTheRoom(ask.szTarget,nRoomIndex),
						gIC->m_ItemList[ask.nItemID].nStamina);
					break;
				case TARGET_ALLEXCEPTME:
					for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
					{
						if(m_isGamePlayer[nRoomIndex][i]&&i!=nInRoomIndex)
						{
							staminaConvert(nRoomIndex,i,gIC->m_ItemList[ask.nItemID].nStamina);
						}
					}
					break;
			}
			return true;
		}
		else if(gIC->m_ItemList[ask.nItemID].type == ITEM_NOCLASS)
		{
			switch(gIC->m_ItemList[ask.nItemID].target) {
				case TARGET_OTHER:
					m_ItemCoolTime[nRoomIndex][nInRoomIndex][ask.nItemID] = 99;
					break;
			}
			return true;
		}
		else if(gIC->m_ItemList[ask.nItemID].type == ITEM_MOVESELECT)
		{
			switch(gIC->m_ItemList[ask.nItemID].target) {
				case TARGET_ME:
					break;
			}

			return false;
		}
		else if(gIC->m_ItemList[ask.nItemID].type == ITEM_MOVEPLACE)
		{
			switch(gIC->m_ItemList[ask.nItemID].target) {
				case TARGET_ME:
					m_ItemCoolTime[nRoomIndex][nInRoomIndex][ask.nItemID]
					= gIC->m_ItemList[ask.nItemID].nPos * 100;
					break;
				case TARGET_OTHER:
					m_ItemCoolTime[nRoomIndex][gRC->FindPlayerIndexInTheRoom(ask.szTarget,nRoomIndex)][ask.nItemID]
					= gIC->m_ItemList[ask.nItemID].nPos * 100;
					break;
			}
			return false;
		}
	}
	OutputDebugString("itemUse �з����� ���� case ����\n");
	return false;
}


/*

void gGamePlayerContainer::pk_warpstart_ask (PK_DEFAULT *pk, SOCKET sock)
{
	PK_WARPSTART_ASK		ask;		//from client
	gPlayerContainer	*gPC =	gPlayerContainer::GetIF();
	gRoomCore			*gRC =	gRoomCore::GetIF();


	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_WARPSTART_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_WARPSTART_ASK] %s\t message : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	OutputDebugString(buf);

	// ���� �� �κп� m_ItemCoolTime�� ���� ��Ե� for������ /100 �Ͽ� �о
	// ... �� ���� �Ӹ��� ���ư��� �ʴ´�. ��ư �ؾ� �ϴ°�.
}
*/