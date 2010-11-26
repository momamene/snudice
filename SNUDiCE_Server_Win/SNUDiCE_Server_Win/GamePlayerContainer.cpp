#include "GamePlayerContainer.h"
#include "RoomCore.h"
#include "TileContainer.h"
#include "PlayerContainer.h"
#include "MainWin.h"
#include "SubmitCore.h"
#include "SubjectContainer.h"
#include "ItemContainer.h"
#include "ChannelCore.h"
#include "ChannelContainer.h"

#include <time.h>


#define ENDROUND	100

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
	memset(&m_struct_itemuse_ask[nRoomIndex], 0, sizeof(PK_ITEMUSE_ASK));


	

	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)		
		// GAMEPLAYER�� ���� Setting�� 
		// �� ���� gGamePlayerContainer�� ������ �и��Ͽ� �����ϴ� ������ �����ָ� �� ������� ������?
	{
		if(gRC->m_rooms[nRoomIndex].szRoomMaxPlayer[i][0] == '\0') {
			m_isGamePlayer[nRoomIndex][i] = false;
		}
		else {
			m_favor[nRoomIndex][i].bYes = CPS_NONE;		//����
			m_favor[nRoomIndex][i].lvTargetIndex = -1;
			m_GamePlayer[nRoomIndex][i].nLove = -1;	//����
			
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
//	for ()
//	m_rmWalk[nRoomIndex] = 0;
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
		pk_infochangeTile_rep(nRoomIndex,nInRoomIndex,1,0);	
		pk_gameplayerinfo_rep(nRoomIndex);
		pk_nextturn_rep(nRoomIndex);
		return;
	}

	rep.Dice4_1 = 0;
	rep.Dice4_2 = 0;
	rep.Dice6_1 = 0;
	rep.Dice6_2 = 0;

	int nSum;
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
	
	/*	�̵�����
	rep.Dice4_1 = 2;
	rep.Dice4_2 = 0;
	rep.Dice6_1 = 0;
	rep.Dice6_2 = 0;
	*/
	
	nSum = rep.Dice4_1 + rep.Dice4_2 + rep.Dice6_1 + rep.Dice6_2;

	if(m_isNokdu[nRoomIndex][nInRoomIndex]) nSum *= -1;

	
	rep.nDist = nSum;
	
	pk_movestart_rep(nRoomIndex,nInRoomIndex, rep);
	
	
	//gMainWin::GetIF()->Send(PL_MOVESTART_REP,sizeof(PK_MOVESTART_REP),&rep,ask.szID);

}
void gGamePlayerContainer::pk_movestart_rep (int nRoomIndex , int nInRoomIndex , PK_MOVESTART_REP rep)
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();
	gRoomCore			*gRC = gRoomCore::GetIF();
	gTileContainer		*gTC = gTileContainer::GetIF();
	//////////////////////////////////////////////////////////////////////////
	int stopPoint , des;
	PushbSynAllPlayer(nRoomIndex,false);


	if (m_GamePlayer[nRoomIndex][nInRoomIndex].nLove == -1)	{	//��, �ַγ�?
		stopPoint = putFavorCross(nRoomIndex , nInRoomIndex , m_GamePlayer[nRoomIndex][nInRoomIndex].nPos , rep.nDist);
		des = stopPoint;

		movePlayer(nRoomIndex,nInRoomIndex,des,MPS_MOVE);
		rep.nDist = rep.nDist - m_rmWalk[nRoomIndex];
		gPC->SendSelect(PL_MOVESTART_REP,sizeof(PK_MOVESTART_REP),&rep,ECM_GAME,nRoomIndex);
	}
	else	{	//�� Ŀ���̳�?
		PK_MOVESTARTCOUPLE_REP repCouple;
		repCouple = rep;
		des = gTC->destination(m_GamePlayer[nRoomIndex][nInRoomIndex].nPos , rep.nDist);
		movePlayer(nRoomIndex,nInRoomIndex,des,MPS_MOVE);

		int partnerIndex = m_favor[nRoomIndex][nInRoomIndex].lvTargetIndex;
		movePlayer(nRoomIndex,partnerIndex,des,MPS_MOVE);

		gPC->SendSelect(PL_MOVESTARTCOUPLE_REP,sizeof(PK_MOVESTARTCOUPLE_REP),&rep,ECM_GAME,nRoomIndex);

	}
	//////////////////////////////////////////////////////////////////////////
}


int gGamePlayerContainer::putFavorCross(int nRoomIndex, int nInRoomIndex, int nPos , int nDist)
{
	gTileContainer *gTC = gTileContainer::GetIF();
	gCharinfo* gCI = gCharinfo::GetIF();
	GAMEPLAYER metPlayer , myPlayer = m_GamePlayer[nRoomIndex][nInRoomIndex];
	int iPos = nPos;
	
	bool nok = false;
	if (nDist < 0 )	{
		nok = true;
		nDist = -nDist;
	}

	int dest;	//����
	
	for (int i = 1 ; i <= nDist ; i++)	{
		
		dest = nok ? -i : i;
		
		iPos =  gTC->destination(nPos,dest);
		
		for (int j = 0 ; j < ROOMMAXPLAYER ; j++)	{
			if (nInRoomIndex == j)		continue;	//	j : ������ ��� index
			metPlayer = m_GamePlayer[nRoomIndex][j];
			if (iPos == metPlayer.nPos)	{
				if (gCI->getMale(metPlayer.ctype)^gCI->getMale(myPlayer.ctype))	{
					if (metPlayer.nLove != -1)	//�����ִ»������ �۾�����;
						continue;
					if (dest == nDist)	{	//������������ ���� 
						if (favorUpFunc(nRoomIndex , nInRoomIndex , j , SAMETILE_FAVORPOINT))	{
							m_rmWalk[nRoomIndex] = 0;
							return iPos;
						}
					}
					else	{			//�������� ����
						if (favorUpFunc(nRoomIndex , nInRoomIndex , j , CROSS_FAVORPOINT))	{
							m_rmWalk[nRoomIndex] = nDist - dest;	//�����Ÿ� ����
							return iPos;
						}
					}
				}
			}
		}
	}
	return iPos;
}
//����, 

void gGamePlayerContainer::pk_askcouple_rep(int nRoomIndex , int playerIndex_a, int playerIndex_b)
{
	PK_ASKCOUPLE_REP rep1, rep2;
	char *playerID_a , *playerID_b;
	gRoomCore			*gRC  = gRoomCore::GetIF();

	playerID_a = gRC->FindPlayerszIDInTheRoom(playerIndex_a,nRoomIndex);
	playerID_b = gRC->FindPlayerszIDInTheRoom(playerIndex_b,nRoomIndex);

	strcpy(rep1.szCouple , playerID_a);
	strcpy(rep2.szCouple , playerID_b);
	
	gMainWin::GetIF()->Send(PL_ASKCOUPLE_REP,sizeof(PK_ASKCOUPLE_REP),&rep1,playerID_b);
	gMainWin::GetIF()->Send(PL_ASKCOUPLE_REP,sizeof(PK_ASKCOUPLE_REP),&rep2,playerID_a);
	
}

bool gGamePlayerContainer::favorUpFunc(int nRoomIndex , int playerIndex_a, int playerIndex_b , int upPoint /* = CROSS_FAVORPOINT */)	{
	char				buf [1024];
	
	m_favor[nRoomIndex][playerIndex_a].point[playerIndex_b] += upPoint;
	m_favor[nRoomIndex][playerIndex_b].point[playerIndex_a] += upPoint;


	if (m_favor[nRoomIndex][playerIndex_a].point[playerIndex_b]  >= MINIMUM_COUPLE_CONDITION)	{	//Ŀ�� �������� ����
		m_favor[nRoomIndex][playerIndex_a].lvTargetIndex = playerIndex_b;				m_favor[nRoomIndex][playerIndex_a].bYes = CPS_PROPOSE;	
		m_favor[nRoomIndex][playerIndex_b].lvTargetIndex = playerIndex_a;				m_favor[nRoomIndex][playerIndex_b].bYes = CPS_PROPOSE;	
		return true;
	}
	else	
		wsprintf(buf,"[FavorUp][Room : %d ; index : %d and %d : %d point] ", nRoomIndex , playerIndex_a , playerIndex_b , upPoint);
	OutputDebugString(buf);

	
	return false;
}
void gGamePlayerContainer::debuger_move(int nDis,char* szID) {
	gPlayerContainer	*gPCt = gPlayerContainer::GetIF();
	gRoomCore			*gRC = gRoomCore::GetIF();
	gTileContainer		*gTCt = gTileContainer::GetIF();

	int nRoomIndex = gPCt->GetCoreFlag(szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(szID,nRoomIndex);
	
	if(nInRoomIndex != m_nTurn[nRoomIndex]) return;
	//����� ��ɾ� ���� ��, �ش� turn�� �ƴ� ���� ������ ������ ��.

	PK_MOVESTART_REP debug_rep;
	debug_rep.Dice4_1	=	 0;
	debug_rep.Dice4_2	=	 0;
	debug_rep.Dice6_1	=	 0;
	debug_rep.Dice6_2	=	 0;
	debug_rep.nDist		=	 nDis; 
	pk_movestart_rep(nRoomIndex , nInRoomIndex , debug_rep);
}

void gGamePlayerContainer::debuger_card(int nIndex,char* szID) {
	gPlayerContainer	*gPCt = gPlayerContainer::GetIF();
	gRoomCore			*gRC = gRoomCore::GetIF();
	
	int nRoomIndex = gPCt->GetCoreFlag(szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(szID,nRoomIndex);

	if(nInRoomIndex != m_nTurn[nRoomIndex]) return;
	//����� ��ɾ� ���� ��, �ش� turn�� �ƴ� ���� ������ ������ ��.
	if(nIndex < 0 || nIndex >= ITEMNUM ) return;
	// �߸��� nIndex ��

	
	getItem(nRoomIndex,m_nTurn[nRoomIndex],nIndex);
	pk_gameplayerinfo_rep(nRoomIndex);
}



void gGamePlayerContainer::debuger_turn(char* szID) {
	gPlayerContainer	*gPCt = gPlayerContainer::GetIF();
//	gRoomCore			*gRC = gRoomCore::GetIF();

	int nRoomIndex = gPCt->GetCoreFlag(szID);
	pk_nextturn_rep(nRoomIndex);
}

void gGamePlayerContainer::movePlayer(int nRoomIndex,int nInRoomIndex,int des,MovePlayerState mpState)
{
	gTileContainer *gTC = gTileContainer::GetIF();
	if(mpState == MPS_MOVE)
	{
		if(des == 2*LINEY+17) 
			m_isNokdu[nRoomIndex][nInRoomIndex] = true;
		else
			m_isNokdu[nRoomIndex][nInRoomIndex] = false;
	}
	else if(mpState == MPS_BUS && des == gTC->m_xInitSpacePos * LINEY + gTC->m_yInitSpacePos) 
	{ // flip
		if(m_isNokdu[nRoomIndex][nInRoomIndex]) 
			m_isNokdu[nRoomIndex][nInRoomIndex] = false;
		else 
			m_isNokdu[nRoomIndex][nInRoomIndex] = true;
	}
	else if(mpState == MPS_WARP) {
		if(isNokduFromPosByHardCoded(des))
			m_isNokdu[nRoomIndex][nInRoomIndex] = true;
		else
			m_isNokdu[nRoomIndex][nInRoomIndex] = false;
	}
	m_GamePlayer[nRoomIndex][nInRoomIndex].nPos = des;
}

bool gGamePlayerContainer::isNokduFromPosByHardCoded(int nPos)
{
	switch(nPos)
	{
	case 5*LINEY+15:
	case 5*LINEY+16:
	case 5*LINEY+17:
	case 4*LINEY+18:
	case 3*LINEY+17:
	case 2*LINEY+17:
	case 2*LINEY+16:
	case 3*LINEY+15:
		return true;
	default:
		return false;
	}
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

	if (m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nLove > -1)	//Ŀ�� ������
		nRoomIndex = nRoomIndex;
	
	if(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos == ask.nDestPos) {
		m_bSyncronize[nRoomIndex][nInRoomIndex] = true;
			
		if(isbSynAllTrue(nRoomIndex)) {	// ��� ���갡 ������...
			PushbSynAllPlayer(nRoomIndex,false);
			if (m_favor[nRoomIndex][m_nTurn[nRoomIndex]].bYes == CPS_PROPOSE)	{	//���µ��� Ŀ�ü�������
				pk_askcouple_rep(nRoomIndex,m_nTurn[nRoomIndex],m_favor[nRoomIndex][m_nTurn[nRoomIndex]].lvTargetIndex);
				return;
			}
			TILE *aaa= gTC->m_tileMap;

			if(gTC->m_tileMap[ask.nDestPos].tileType==TY_BUS) {
				OutputDebugString("TY_BUS\n");
				pk_busmovechoose_rep(nRoomIndex,szTurnID);
			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType==TY_CLASS) {
				OutputDebugString("TY_CLASS\n");
				// ��������
				int getAccomplishment = meetGrade ( nRoomIndex , gTC->m_tileMap[ask.nDestPos].flag2 , m_nTurn[nRoomIndex]);
				int getCoupleAccomplishment = -1;	int partnerIndex = -1;	//Ŀ�þƴϸ� -1
				GradeRankSyncronizer(nRoomIndex);

				if(getAccomplishment!=-1) {
					OutputDebugString("TY_MySubject\n");
					staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],-1);
				}
				if (m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nLove != -1)	{	//Ŀ�ø��
					partnerIndex = m_favor[nRoomIndex][m_nTurn[nRoomIndex]].lvTargetIndex;
					getCoupleAccomplishment = meetGrade(nRoomIndex,gTC->m_tileMap[ask.nDestPos].flag2 , partnerIndex);
					
					if (getCoupleAccomplishment != -1)	{
						OutputDebugString("TY_PartnerSubject\n");
						staminaConvert(nRoomIndex,partnerIndex,-1);
					}
				}
				// �������
				
				if (getAccomplishment != -1 && getCoupleAccomplishment != -1)	{ 	//���� ���� ���
					pk_infochangeTile_rep(nRoomIndex,m_nTurn[nRoomIndex],-1,
						getCoupleAccomplishment > getAccomplishment ? getCoupleAccomplishment : getAccomplishment, partnerIndex);
					//���� ������������� (���ν����ִϱ� -��-;;����� ��;;)
				}	else if (getAccomplishment != -1 && getCoupleAccomplishment == -1)	{	//���� ���� ���
					pk_infochangeTile_rep(nRoomIndex,m_nTurn[nRoomIndex],-1, getAccomplishment);
				}	else if (getAccomplishment == -1 && getCoupleAccomplishment != -1)	{	//�ʸ� ���� ���
					pk_infochangeTile_rep(nRoomIndex,partnerIndex,-1, getCoupleAccomplishment);
				}
				if (getAccomplishment == -1 && getCoupleAccomplishment == -1)	{	//���
					pk_nextturn_rep(nRoomIndex);
				}
				pk_gameplayerinfo_rep(nRoomIndex);
			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType==TY_DRINK) {
				OutputDebugString("TY_DRINK\n");
				staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],-1);
				if (m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nLove == -1)	{	//�̱�
					pk_infochangeTile_rep(nRoomIndex,m_nTurn[nRoomIndex],-1,0);
				} else	{	//Ŀ��
					int partnerIndex = m_favor[nRoomIndex][m_nTurn[nRoomIndex]].lvTargetIndex;
					staminaConvert(nRoomIndex,partnerIndex,-1);
					pk_infochangeTile_rep(nRoomIndex,m_nTurn[nRoomIndex],-1,0 , partnerIndex);
				}

				pk_gameplayerinfo_rep(nRoomIndex);
//				pk_nextturn_rep(nRoomIndex);
			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType==TY_STAMINA) {
				OutputDebugString("TY_STAMINA\n");
				staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],1);
				if (m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nLove == -1)	{	//�̱�
					pk_infochangeTile_rep(nRoomIndex,m_nTurn[nRoomIndex] , 1,0);
				}	else	{	//Ŀ��
					int partnerIndex = m_favor[nRoomIndex][m_nTurn[nRoomIndex]].lvTargetIndex;
					staminaConvert(nRoomIndex,partnerIndex,1);
					pk_infochangeTile_rep(nRoomIndex,m_nTurn[nRoomIndex] , 1,0 , partnerIndex);
				}
				pk_gameplayerinfo_rep(nRoomIndex);
//				pk_nextturn_rep(nRoomIndex);
			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType==TY_ITEM) {
				OutputDebugString("TY_ITEM\n");
				getItem(nRoomIndex,m_nTurn[nRoomIndex]);
				if (m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nLove != -1)		//Ŀ��
					getItem(nRoomIndex,m_favor[nRoomIndex][m_nTurn[nRoomIndex]].lvTargetIndex);
				pk_gameplayerinfo_rep(nRoomIndex);
				pk_nextturn_rep(nRoomIndex);
			}
			else {//���
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
	
	movePlayer(nRoomIndex,nInRoomIndex,ask.nPos,MPS_MOVE);
	rep.nDist = dis;
	if (m_GamePlayer[nRoomIndex][nInRoomIndex].nLove == -1)	{	//�ַ�
		gPC->SendSelect(PL_BUSMOVESTART_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);
	}	else	{	//Ŀ��
		int partnerIndex = m_favor[nRoomIndex][nInRoomIndex].lvTargetIndex;
		movePlayer(nRoomIndex,partnerIndex,ask.nPos,MPS_MOVE);
		gPC->SendSelect(PL_BUSMOVESTARTCOUPLE_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);
	}
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

	memcpy(rep.list,m_GamePlayer[nRoomIndex],sizeof(GAMEPLAYER)*ROOMMAXPLAYER);

	pk_subGameplayerinfo_rep(nRoomIndex,&rep);

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
			if((gIC->m_ItemList[j].nLang != 0 || gIC->m_ItemList[j].nMath != 0 || gIC->m_ItemList[j].nArt != 0)
				&& m_ItemCoolTime[nRoomIndex][i][j] > 0) {
				rep->list[i].nLang += gIC->m_ItemList[j].nLang;
				rep->list[i].nMath += gIC->m_ItemList[j].nMath;
				rep->list[i].nArt += gIC->m_ItemList[j].nArt;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
/// ���� ���� �Լ�
//////////////////////////////////////////////////////////////////////////

int gGamePlayerContainer::meetGrade(int nRoomIndex,int subjectIndex ,int nInRoomIndex) // subjectIndex = flag1
{	// int ������ resultMIC ���� return �ϸ� �ǰڳ�..
	gSubjectContainer *gSCt = gSubjectContainer::GetIF();
	gItemContainer *gICt = gItemContainer::GetIF();

	int resultMIC = -1;	// error
	for(int i = 0 ; i < MAXSUBJECT ; i++ ){
		if(m_GamePlayer[nRoomIndex][nInRoomIndex].bySubIdx[i] == subjectIndex){
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

void gGamePlayerContainer::getItem(int nRoomIndex,int nInRoomIndex,int nItemID)
{
	for(int i = 0 ; i < MAXITEMNUM ; i++)
	{
		if(m_GamePlayer[nRoomIndex][nInRoomIndex].nItem[i] == -1) {
			if (nItemID >= 0) m_GamePlayer[nRoomIndex][nInRoomIndex].nItem[i] = nItemID;
			else m_GamePlayer[nRoomIndex][nInRoomIndex].nItem[i] = rand()%20;
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
	PK_ITEMUSE_ASK		ask;
	gPlayerContainer	*gPCt =	gPlayerContainer::GetIF();
	gRoomCore			*gRC =	gRoomCore::GetIF();

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_ITEMUSE_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_ITEMUSE_ASK] %s\t itemIndex : %s %d \n", inet_ntoa(clientAddr.sin_addr), ask.szID, ask.nItemID);
	OutputDebugString(buf);

	PK_ITEMUSE_REP		rep;
	memset(&rep,0,sizeof(rep));

	int nRoomIndex = gPCt->GetCoreFlag(ask.szID);
//	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);	

	PushbSynAllPlayer(nRoomIndex,false);
 
	strcpy(rep.szUser,ask.szID); // �̰� �°���?
	rep.nItemID = ask.nItemID;
	strcpy(rep.szTarget,ask.szTarget);

	m_struct_itemuse_ask[nRoomIndex] = ask;	// �̰� �� �ǰ���?

//	gMainWin::GetIF()->Send(PL_ITEMUSE_REP,sizeof(rep),&rep,ask.szID);
	gPCt->SendSelect(PL_ITEMUSE_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);

}

void gGamePlayerContainer::pk_itemusestart_ask(PK_DEFAULT *pk,SOCKET sock)
{
	PK_ITEMUSESTART_ASK		preAsk;		//from client
	gPlayerContainer	*gPC =	gPlayerContainer::GetIF();
	gRoomCore			*gRC =	gRoomCore::GetIF();


	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	preAsk = *((PK_ITEMUSESTART_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_ITEMUSESTART_ASK] %s\t %s \n", inet_ntoa(clientAddr.sin_addr), preAsk.szID);
	OutputDebugString(buf);

	int nRoomIndex = gPC->GetCoreFlag(preAsk.szID);
	int nPreInRoomIndex = gRC->FindPlayerIndexInTheRoom(preAsk.szID,nRoomIndex);	// ��ũ�� üĿ

	m_bSyncronize[nRoomIndex][nPreInRoomIndex] = true;
	if(isbSynAllTrue(nRoomIndex)) {

		PK_ITEMUSE_ASK ask = m_struct_itemuse_ask[nRoomIndex];
		int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex); // �������� �����ۻ����

		//rep.result = ITEMUSE_SUCCESS;
		ItemUseState iuState = itemUse(ask,nRoomIndex,nInRoomIndex,ask.nItemID);
		pk_gameplayerinfo_rep(nRoomIndex);

		
		//if(rep.result == ITEMUSE_ERROR){
	
		if(iuState == IUS_NONE) {
			// �ƹ��͵� ����.
			// �׷��� �̷� �������� �����Ƿ� �� �������߰���?
			// �ƴ�. Move Series�� IUS_NONE �迭.
		}
		else if(iuState == IUS_NEXTTURN) {
			OutputDebugString("IUS_NEXTTURN");
			pk_nextturn_rep(nRoomIndex);
		}
		else if(iuState == IUS_INFOCHANGE) {
			OutputDebugString("IUS_INFOCHANGE");
			pk_infochangeItem_rep(ask);
		}
		else if(iuState == IUS_INVALIDSTATE) {
			// error ó��
			OutputDebugString("ġ������ itemuse ���� \n");
		}
		//gPC->SendSelect(PL_ITEMUSE_REP,sizeof(rep),&rep,ECM_GAME,gPC->GetCoreFlag(ask.szID));
	}
}

ItemUseState gGamePlayerContainer::itemUse (PK_ITEMUSE_ASK ask, int nRoomIndex, int nInRoomIndex, int itemIndex)
{	// nInRoomIndex�� �������� ����� ����, itemIndex�� 0-19 ������ ���״����...
	gItemContainer		*gIC =	gItemContainer::GetIF();
	gPlayerContainer	*gPC =	gPlayerContainer::GetIF();
	gRoomCore			*gRC =	gRoomCore::GetIF();

	char buf [1024];

	pushItem(nRoomIndex,nInRoomIndex,ask.nItemID);
	wsprintf(buf,"itemUse(f) - nItemID : %d ",ask.nItemID);
	OutputDebugString(buf);
	
	if(gIC->m_ItemList[ask.nItemID].nExistTurn > 0) {
		// ���� 0���� Ŭ ����...
		// �� ���Ǵ� �������� ��Ÿ�� �ִ� ������ �����.
		if(gIC->m_ItemList[ask.nItemID].type == ITEM_STAT)
		{
			OutputDebugString("type : ITEM_STAT\n");
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
			return IUS_INFOCHANGE;
		}
		else if(gIC->m_ItemList[ask.nItemID].type == ITEM_TOGETHERCLASS)
		{
			OutputDebugString("type : ITEM_TOGETHERCLASS\n");
			switch (gIC->m_ItemList[ask.nItemID].target) {
				case TARGET_OTHER:
					m_ItemCoolTime[nRoomIndex][nInRoomIndex][ask.nItemID]
					= gIC->m_ItemList[ask.nItemID].nExistTurn;
					m_ItemCoolTime[nRoomIndex][nInRoomIndex][ask.nItemID]
					+= gRC->FindPlayerIndexInTheRoom(ask.szTarget,nRoomIndex)*100;
					break;
			}
			return IUS_NEXTTURN;
		}
	}

	else {
		if(gIC->m_ItemList[ask.nItemID].type == ITEM_STAMINA) {
			OutputDebugString("type : ITEM_STAMINA\n");

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
			return IUS_INFOCHANGE;
		}
		else if(gIC->m_ItemList[ask.nItemID].type == ITEM_NOCLASS)
		{
			OutputDebugString("type : ITEM_NOCLASS\n");
			switch(gIC->m_ItemList[ask.nItemID].target) {
				case TARGET_OTHER:
					m_ItemCoolTime[nRoomIndex][gRC->FindPlayerIndexInTheRoom(ask.szTarget,nRoomIndex)][ask.nItemID] = 99;
					break;
			}
			return IUS_NEXTTURN;
		}
		else if(gIC->m_ItemList[ask.nItemID].type == ITEM_MOVESELECT)
		{
			OutputDebugString("type : ITEM_MOVESELECT\n");
			switch(gIC->m_ItemList[ask.nItemID].target) {
				case TARGET_ME:
					if (m_GamePlayer[nRoomIndex][nInRoomIndex].nLove == -1)
						pk_warpstart_rep(nRoomIndex,nInRoomIndex,ask.nDestPos);
					else	{
						bool *bInRoomIndex = new bool[ROOMMAXPLAYER];
						int *desList  = new int[ROOMMAXPLAYER];
						memset(bInRoomIndex , 0 , sizeof(bInRoomIndex));
						memset(desList , 0 , sizeof(desList));
						int partnerIndex  = m_favor[nRoomIndex][nInRoomIndex].lvTargetIndex;
						bInRoomIndex[nInRoomIndex] = true;	bInRoomIndex[partnerIndex] = true;
						desList[nInRoomIndex] = ask.nDestPos;	desList[partnerIndex] = ask.nDestPos;
						
						pk_warpliststart_rep(nRoomIndex , bInRoomIndex ,desList);

						delete desList;						delete bInRoomIndex;
					}
					break;
			}

			return IUS_NONE;
		}
		else if(gIC->m_ItemList[ask.nItemID].type == ITEM_MOVEPLACE)
		{
			OutputDebugString("type : ITEM_MOVEPLACE\n");

			switch(gIC->m_ItemList[ask.nItemID].target) {
				case TARGET_ME:
					if (m_GamePlayer[nRoomIndex][nInRoomIndex].nLove == -1)
						pk_warpstart_rep(nRoomIndex,nInRoomIndex,	gIC->m_ItemList[ask.nItemID].nPos	);
					else	{
						bool *bInRoomIndex = new bool[ROOMMAXPLAYER];
						int *desList  = new int[ROOMMAXPLAYER];
						memset(bInRoomIndex , 0 , sizeof(bInRoomIndex));
						memset(desList , 0 , sizeof(desList));
						int partnerIndex  = m_favor[nRoomIndex][nInRoomIndex].lvTargetIndex;
						bInRoomIndex[nInRoomIndex] = true;	bInRoomIndex[partnerIndex] = true;
						desList[nInRoomIndex] = ask.nDestPos;	desList[partnerIndex] = ask.nDestPos;

						pk_warpliststart_rep(nRoomIndex , bInRoomIndex ,desList);

						delete desList;						delete bInRoomIndex;
					}
					break;
				case TARGET_OTHER:
//					bool barrInRoomIndex[ROOMMAXPLAYER];
//					putTargetTrueForOther(nRoomIndex,nInRoomIndex,barrInRoomIndex,TARGET_OTHER);
//					int narrDes[ROOMMAXPLAYER];
//					putTargetIntForOther(nRoomIndex,nInRoomIndex,narrDes,TARGET_OTHER,gIC->m_ItemList[ask.nItemID].nPos);
//					pk_warpliststart_rep(nRoomIndex,m_isGamePlayer[nRoomIndex],narrDes);
					
					if (m_GamePlayer[nRoomIndex][nInRoomIndex].nLove == -1)
						pk_warpstart_rep(nRoomIndex,nInRoomIndex,	gIC->m_ItemList[ask.nItemID].nPos	);
					else	{
						bool *bInRoomIndex = new bool[ROOMMAXPLAYER];
						int *desList  = new int[ROOMMAXPLAYER];
						memset(bInRoomIndex , 0 , sizeof(bInRoomIndex));
						memset(desList , 0 , sizeof(desList));
						int partnerIndex  = m_favor[nRoomIndex][nInRoomIndex].lvTargetIndex;
						bInRoomIndex[nInRoomIndex] = true;	bInRoomIndex[partnerIndex] = true;
						desList[nInRoomIndex] = ask.nDestPos;	desList[partnerIndex] = ask.nDestPos;

						pk_warpliststart_rep(nRoomIndex , bInRoomIndex ,desList);

						delete desList;						delete bInRoomIndex;
					}
					break;
				case TARGET_ALLEXCEPTME :
					bool *bInRoomIndex = new bool[ROOMMAXPLAYER];
					int *desList  = new int[ROOMMAXPLAYER];

					bool isCouple = false;
					for (int i = 0 ; i < ROOMMAXPLAYER ; i++)	{
						if (m_isGamePlayer[nRoomIndex][i])	{
							if (m_favor[nRoomIndex][i].lvTargetIndex == nInRoomIndex)
								isCouple = true;
							desList[i] = gIC->m_ItemList[ask.nItemID].nPos;
							bInRoomIndex[i] = 1;
						}	else	{
							desList[i] = 0;
							bInRoomIndex[i] = 0;
						}
					}
					
					if (!isCouple)	{
						desList[nInRoomIndex] = 0;	bInRoomIndex[nInRoomIndex] = 0;
					}

					pk_warpliststart_rep(nRoomIndex , bInRoomIndex ,desList);

					delete desList;						delete bInRoomIndex;
					break;
			}
			return IUS_NONE;
		}

		else if (gIC->m_ItemList[ask.nItemID].type == ITEM_DASH)	{
			switch(gIC->m_ItemList[ask.nItemID].target) {
				case TARGET_OTHERSEX :

					int partnerIndex = gRC->FindPlayerIndexInTheRoom(ask.szTarget,nRoomIndex);

					m_favor[nRoomIndex][partnerIndex].lvTargetIndex = nInRoomIndex;				m_favor[nRoomIndex][partnerIndex].bYes = CPS_PROPOSE;	
					m_favor[nRoomIndex][nInRoomIndex].lvTargetIndex = partnerIndex;				m_favor[nRoomIndex][nInRoomIndex].bYes = CPS_PROPOSE;	

					pk_askcouple_rep(	nRoomIndex,	nInRoomIndex , partnerIndex	);

					
					break;
			}
		}	else if (gIC->m_ItemList[ask.nItemID].type == ITEM_POWERDASH)	{
			
			
			int partnerIndex = gRC->FindPlayerIndexInTheRoom(ask.szTarget,nRoomIndex);
			char *szID_me = gRC->FindPlayerszIDInTheRoom(nInRoomIndex , nRoomIndex) , *szID_partner = gRC->FindPlayerszIDInTheRoom(partnerIndex , nRoomIndex);
			
			pk_becouple_rep(nRoomIndex, gPC->GetPlayerFromID(szID_me) ,  gPC->GetPlayerFromID(szID_partner));
		}
		return IUS_NONE;
	}
	
	OutputDebugString("itemUse �з����� ���� case ����\n");
	return IUS_INVALIDSTATE;
}


void gGamePlayerContainer::pk_warpstart_rep (int nRoomIndex, int nInRoomIndex, int des)
{
	OutputDebugString("pk_warstart_rep(f) \n");
	PK_WARPSTART_REP	rep;

	gPlayerContainer	*gPC =	gPlayerContainer::GetIF();
	gTileContainer		*gTC =	gTileContainer::GetIF();
	gRoomCore			*gRC =	gRoomCore::GetIF();
	
	
	rep.nDest = des;
	strcpy(rep.szID , gRC->FindPlayerszIDInTheRoom(nInRoomIndex,nRoomIndex));
	//rep.nDist = gTC->distance(m_GamePlayer[nRoomIndex][nInRoomIndex].nPos,des);
	
	PushbSynAllPlayer(nRoomIndex,false);
	movePlayer(nRoomIndex,nInRoomIndex,des,MPS_WARP);
	gPC->SendSelect(PL_WARPSTART_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);
}


void gGamePlayerContainer::pk_warpliststart_rep (int nRoomIndex, bool* bInRoomIndex, int* des)
{
	OutputDebugString("pk_warliststart_rep(f) \n");
	PK_WARPLISTSTART_REP	rep;

	gPlayerContainer	*gPC =	gPlayerContainer::GetIF();
	gTileContainer		*gTC =	gTileContainer::GetIF();

	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
	{
		if(bInRoomIndex[i]) {
			movePlayer(nRoomIndex,i,des[i],MPS_WARP);
			rep.nDestPos[i] = des[i];
		}
		else{
			rep.nDestPos[i] = -1;
		}

	}
	PushbSynAllPlayer(nRoomIndex,false);

	gPC->SendSelect(PL_WARPLISTSTART_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);

}


void gGamePlayerContainer::pk_warpend_ask (PK_DEFAULT *pk, SOCKET sock)
{
	PK_WARPEND_ASK		ask;		//from client
	gPlayerContainer	*gPC =	gPlayerContainer::GetIF();
	gRoomCore			*gRC =	gRoomCore::GetIF();
	gTileContainer		*gTC =	gTileContainer::GetIF();


	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_WARPEND_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_WARPEND_ASK] %s\t %s \n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	OutputDebugString(buf);

	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);
	char szTurnID[IDLENGTH];
	strcpy(szTurnID,m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].szID);



	if(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos == ask.nDestPos) {
		m_bSyncronize[nRoomIndex][nInRoomIndex] = true;

		if(isbSynAllTrue(nRoomIndex)) {	// ��� ������ ������,,, ���� �����;;
			PushbSynAllPlayer(nRoomIndex,false); 
			if(gTC->m_tileMap[ask.nDestPos].tileType==TY_CLASS) {
				OutputDebugString("TY_CLASS\n");
				int getAccomplishment = meetGrade ( nRoomIndex , gTC->m_tileMap[ask.nDestPos].flag2 , m_nTurn[nRoomIndex]);
				int getCoupleAccomplishment = -1;
				GradeRankSyncronizer(nRoomIndex);

				if(getAccomplishment!=-1) {	//������ ���⼭ ���ڵ�~!
					OutputDebugString("TY_MySubject\n");
					staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],-1);
					if (m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nLove == -1)
						pk_infochangeTile_rep(nRoomIndex,m_nTurn[nRoomIndex],-1,getAccomplishment);
				}
				if (m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nLove != -1)	{	//Ŀ�ø��
					int partnerIndex = m_favor[nRoomIndex][m_nTurn[nRoomIndex]].lvTargetIndex;
					getCoupleAccomplishment = meetGrade(nRoomIndex,gTC->m_tileMap[ask.nDestPos].flag2 , partnerIndex);

					if (getCoupleAccomplishment != -1)	{
						OutputDebugString("TY_PartnerSubject\n");
						staminaConvert(nRoomIndex,partnerIndex,-1);
						if (getAccomplishment != -1)	//���� ���� ���
							pk_infochangeTile_rep(nRoomIndex,m_nTurn[nRoomIndex],-1,
							getCoupleAccomplishment > getAccomplishment ? getCoupleAccomplishment : getAccomplishment, partnerIndex);
						//���� ������������� (���ν����ִϱ� -��-;;����� ��;;)
						else
							pk_infochangeTile_rep(nRoomIndex,partnerIndex,-1, getCoupleAccomplishment);
					}
				}
				pk_gameplayerinfo_rep(nRoomIndex);
			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType==TY_DRINK) {
				OutputDebugString("TY_DRINK\n");
				staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],-1);
				pk_infochangeTile_rep(nRoomIndex,m_nTurn[nRoomIndex],-1,0);
				pk_gameplayerinfo_rep(nRoomIndex);
				pk_infochangeTile_rep(nRoomIndex,m_nTurn[nRoomIndex],-1,0);
			}
			else if(gTC->m_tileMap[ask.nDestPos].tileType==TY_STAMINA) {
				OutputDebugString("TY_STAMINA\n");
				staminaConvert(nRoomIndex,m_nTurn[nRoomIndex],1);
				pk_infochangeTile_rep(nRoomIndex,m_nTurn[nRoomIndex] , 1,0);
				pk_gameplayerinfo_rep(nRoomIndex);
				pk_infochangeTile_rep(nRoomIndex,m_nTurn[nRoomIndex] , 1,0);
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
		OutputDebugString("[pk_warpend_ask] �ɰ��� Error, ���� ���� ���, ������ Ŭ���̾�Ʈ�� ���� ����� �ٸ�\n");
		OutputDebugString(buf);		OutputDebugString("�� ���� �� �̻� �������� �ʽ��ϴ�.\n");
	}

}


void gGamePlayerContainer::pk_warplistend_ask (PK_DEFAULT *pk, SOCKET sock)
{
	PK_WARPLISTEND_ASK		ask;		//from client
	gPlayerContainer	*gPC =	gPlayerContainer::GetIF();
	gRoomCore			*gRC =	gRoomCore::GetIF();
	gTileContainer		*gTC =  gTileContainer::GetIF();


	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_WARPLISTEND_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_WARPLISTEND_ASK] %s\t %s \n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	OutputDebugString(buf);

	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);


	m_bSyncronize[nRoomIndex][nInRoomIndex] = true;

	if(isbSynAllTrue(nRoomIndex)) {	// ��� ������ ������,,, ���� �����;;
		PushbSynAllPlayer(nRoomIndex,false); 
		OutputDebugString("TY_NOTHING\n");
		pk_gameplayerinfo_rep(nRoomIndex);
		pk_nextturn_rep(nRoomIndex);
	}


}


void gGamePlayerContainer::pk_infochangeItem_rep(PK_ITEMUSE_ASK ask)
{
	OutputDebugString("pk_infochangeItem_rep(f) \n");
	gPlayerContainer	*gPC	=	gPlayerContainer::GetIF();
	gRoomCore			*gRC	=	gRoomCore::GetIF();
	gItemContainer		*gICt	= gItemContainer::GetIF();
	gCharinfo			*gCi	= gCharinfo::GetIF();

	PK_INFOCHANGE_REP rep;
	memset(&rep,0,sizeof(PK_INFOCHANGE_REP));

	int nRoomIndex = gPC->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);
	int nTarget = gRC->FindPlayerIndexInTheRoom(ask.szTarget,nRoomIndex);

	if(gICt->m_ItemList[ask.nItemID].type == ITEM_STAT) {
		switch (gICt->m_ItemList[ask.nItemID].target) {
		case TARGET_ME:
			if(gICt->m_ItemList[ask.nItemID].nMulti == 0) {	// �� �κ��� ���κ� Ȯ��Ǿ�� ��
				rep.info[nInRoomIndex].nArt = gICt->m_ItemList[ask.nItemID].nArt;
				rep.info[nInRoomIndex].nLang = gICt->m_ItemList[ask.nItemID].nLang;
				rep.info[nInRoomIndex].nMath = gICt->m_ItemList[ask.nItemID].nMath;
			}
			else {
				CLASSTYPE cType = m_GamePlayer[nRoomIndex][nInRoomIndex].ctype;
				int nMulti = gICt->m_ItemList[ask.nItemID].nMulti;
				rep.info[nInRoomIndex].nArt = gCi->m_CharInfo[cType].nArt * (nMulti - 1);
				rep.info[nInRoomIndex].nLang = gCi->m_CharInfo[cType].nLang * (nMulti - 1);
				rep.info[nInRoomIndex].nMath = gCi->m_CharInfo[cType].nMath * (nMulti - 1);
			}
			strcpy(rep.info[nInRoomIndex].szID,ask.szID);
			break;

		case TARGET_OTHER:
			rep.info[nTarget].nArt = gICt->m_ItemList[ask.nItemID].nArt;
			rep.info[nTarget].nLang = gICt->m_ItemList[ask.nItemID].nLang;
			rep.info[nTarget].nMath = gICt->m_ItemList[ask.nItemID].nMath;
			strcpy(rep.info[nTarget].szID,m_GamePlayer[nRoomIndex][nTarget].szID);
			break;
			
		case TARGET_MEOTHER:
			for(int i = 0 ; i < ROOMMAXPLAYER ; i++) {
				if(i == nInRoomIndex || 
					i == nTarget) {
					rep.info[i].nArt = gICt->m_ItemList[ask.nItemID].nArt;
					rep.info[i].nLang = gICt->m_ItemList[ask.nItemID].nLang;
					rep.info[i].nMath = gICt->m_ItemList[ask.nItemID].nMath;
					strcpy(rep.info[i].szID,m_GamePlayer[nRoomIndex][i].szID);
				}
			}
			break;

		case TARGET_ALLEXCEPTME:
			for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
			{
				if(m_isGamePlayer[nRoomIndex][i] && i != nInRoomIndex) {
					rep.info[i].nArt = gICt->m_ItemList[ask.nItemID].nArt;
					rep.info[i].nLang = gICt->m_ItemList[ask.nItemID].nLang;
					rep.info[i].nMath = gICt->m_ItemList[ask.nItemID].nMath;
					strcpy(rep.info[i].szID,m_GamePlayer[nRoomIndex][i].szID);
				}
			}
			break;

		}
	}
	else if(gICt->m_ItemList[ask.nItemID].type == ITEM_STAMINA) {
		switch (gICt->m_ItemList[ask.nItemID].target) {
		case TARGET_ME:
			rep.info[nInRoomIndex].nStamina = gICt->m_ItemList[ask.nItemID].nStamina;
			strcpy(rep.info[nInRoomIndex].szID,ask.szID);
			break;

		case TARGET_OTHER:
			
			rep.info[nTarget].nStamina = gICt->m_ItemList[ask.nItemID].nStamina;
			strcpy(rep.info[nTarget].szID,m_GamePlayer[nRoomIndex][nTarget].szID);
			break;

		case TARGET_MEOTHER:
			for(int i = 0 ; i < ROOMMAXPLAYER ; i++) {
				if(i == nInRoomIndex || 
					i == gRC->FindPlayerIndexInTheRoom(ask.szTarget,nRoomIndex)) {
						rep.info[i].nStamina = gICt->m_ItemList[ask.nItemID].nStamina;
						strcpy(rep.info[i].szID,m_GamePlayer[nRoomIndex][i].szID);
				}
			}
			break;

		case TARGET_ALLEXCEPTME:
			for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
			{
				if(m_isGamePlayer[nRoomIndex][i] && i != nInRoomIndex) {
					rep.info[i].nStamina = gICt->m_ItemList[ask.nItemID].nStamina;
					strcpy(rep.info[i].szID,m_GamePlayer[nRoomIndex][i].szID);
				}
			}
			break;
		}
	}

	PushbSynAllPlayer(nRoomIndex,false);
	
	gPC->SendSelect(PL_INFOCHANGE_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);

	pk_gameplayerinfo_rep(nRoomIndex);

}

/*
void gGamePlayerContainer::putTargetTrueForOther(int nRoomIndex,int nInRoomIndex, bool* getBarrInRoomIndex,ITEMTARGET target) {
	for(int i = 0 ; i < ROOMMAXPLAYER ; i++ )
	{
		if(m_isGamePlayer[nRoomIndex][i]) {
			// �ϴ� other�� ���� �������� ��?
			getBarrInRoomIndex[i] = true;
		}
		else {
			getBarrInRoomIndex[i] = false;
		}
	}
}
*/
void gGamePlayerContainer::putTargetIntForOther(int nRoomIndex,int nInRoomIndex, int* getNarrDes,ITEMTARGET target,int nVal) {
	for(int i = 0 ; i < ROOMMAXPLAYER ; i++ )
	{
		if(m_isGamePlayer[nRoomIndex][i]) {
			// �ϴ� other�� ���� �������� ��?
			getNarrDes[i] = nVal;
		}
		else {
			getNarrDes[i] = 0;
		}
	}
}

void gGamePlayerContainer::pk_infochangeTile_rep(int nRoomIndex,int nInRoomIndex, int stamina,int accomplishment , int coupleIndex)
{
	OutputDebugString("pk_infochangeTile_rep(f) \n");
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	PK_INFOCHANGE_REP	rep;
	memset(&rep,0,sizeof(PK_INFOCHANGE_REP));

	strcpy(rep.info[nInRoomIndex].szID,m_GamePlayer[nRoomIndex][nInRoomIndex].szID);
	rep.info[nInRoomIndex].nLang = 0;
	rep.info[nInRoomIndex].nMath = 0;
	rep.info[nInRoomIndex].nArt = 0;
	rep.info[nInRoomIndex].nStamina = stamina;
	rep.info[nInRoomIndex].nGrade = accomplishment;

	if (coupleIndex != -1)	{
		int partnerIndex = m_favor[nRoomIndex][nInRoomIndex].lvTargetIndex;
		strcpy(rep.info[partnerIndex].szID,m_GamePlayer[nRoomIndex][partnerIndex].szID);
		rep.info[partnerIndex].nLang = 0;
		rep.info[partnerIndex].nMath = 0;
		rep.info[partnerIndex].nArt = 0;
		rep.info[partnerIndex].nStamina = stamina;
		rep.info[partnerIndex].nGrade = accomplishment;
	}
	
	PushbSynAllPlayer(nRoomIndex,false);

	gPC->SendSelect(PL_INFOCHANGE_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);
}

void gGamePlayerContainer::pk_infochangeend_ask(PK_DEFAULT *pk, SOCKET sock)
{
	PK_INFOCHANGEEND_ASK		ask;		//from client
	gPlayerContainer	*gPCt =	gPlayerContainer::GetIF();
	gRoomCore			*gRC =	gRoomCore::GetIF();
	
	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_INFOCHANGEEND_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_INFOCHANGEEND_ASK] %s\t message : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	OutputDebugString(buf);

	int nRoomIndex = gPCt->GetCoreFlag(ask.szID);
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID,nRoomIndex);

	m_bSyncronize[nRoomIndex][nInRoomIndex] = true;
	
	if(isbSynAllTrue(nRoomIndex)) {
		pk_nextturn_rep(nRoomIndex);
	}


}



//�����ڵ�, Ŭ���̾�Ʈ������ ask�� �ƴ϶� ���� ���� ������ ����ÿ� ȣ���
void gGamePlayerContainer::pk_exit_ask(char *clientID, SOCKET sock)
{
	gPlayerContainer	*gPC =	gPlayerContainer::GetIF();
	gRoomCore			*gRC =	gRoomCore::GetIF();
	gSubmitCore			*gSC =  gSubmitCore::GetIF();


	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);


	wsprintf(buf,"[PK_EXIT_ASK] %s\t message : %s \n", inet_ntoa(clientAddr.sin_addr), clientID);
	OutputDebugString(buf);

	int nRoomIndex = gPC->GetCoreFlag(clientID);	//�����?
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(clientID,nRoomIndex);	//����ε���? // �̰��� ���� �����̴� //�̳�(�����༮) ���϶� �Ѿ����!

	PK_EXIT_REP rep;
	rep.flag = 0;
	strcpy(rep.szID , clientID);

	m_isGamePlayer[nRoomIndex][nInRoomIndex] = false;	//������ Out ��Ű��
	//������� üũ , ��������� �����Ƽ� �� for��

	for (int i = 0 ; i < ROOMMAXPLAYER ; i++)	{
		rep.flag += m_isGamePlayer[nRoomIndex][i];
	}
	switch(gPC->GetMode(clientID))	{
		case ECM_GAME :	//�����϶�
			if (rep.flag == 1)	{
				pk_gameend_rep(nRoomIndex);
				return;
			}
			gPC->SendSelect(PL_EXIT_REP,sizeof(PK_EXIT_REP),&rep, ECM_GAME , nRoomIndex);

			if (m_nTurn[nRoomIndex] == nInRoomIndex)	//���� �������� �� ���̾��� ��
				pk_nextturn_rep(nRoomIndex);	//�� ���� ����;
			break;
		case ECM_SUBMIT :
			gSC->m_isFinishSubmitSubject[nRoomIndex][nInRoomIndex] = true;	//�����ߴٰ� ��
			if (rep.flag == 1)		{
				pk_maingamestart_rep(nRoomIndex);	//������ ���Ӹ�� ����
				return;
			}

			break;
	}
}


void gGamePlayerContainer::pk_gologin_ask(PK_DEFAULT *pk,SOCKET sock)
{
	PK_GOLOGIN_ASK ask;

	gPlayerContainer	*gPC =	gPlayerContainer::GetIF();
	gChannelContainer	*gCC =	gChannelContainer::GetIF();


	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_GOLOGIN_ASK*)pk->strPacket);

	int nChannel = 	gCC->FindPlayer(ask.szID);

	//	switch(gPC->GetMode(ask.szID))	{
	//		case ECM_BATTLENET :
	gPC->DeletePlayer(sock,ask.szID);
	gPC->PutMode(ask.szID , ECM_LOGIN);
	gCC->DeletePlayer(ask.szID);

	gChannelCore::GetIF()->pk_channelrefresh_rep(nChannel);
	//			break;
	//	}

	wsprintf(buf,"[PK_GOLOGIN_ASK] %s\t message : %s %d \n", inet_ntoa(clientAddr.sin_addr), ask.szID);
	OutputDebugString(buf);


}


void gGamePlayerContainer::pk_anscouple_ask(PK_DEFAULT *pk,SOCKET sock)	//���� , Ŀ���� �Ǿ� �ּ���!
{
	
	PK_ANSCOUPLE_ASK ask;

	gPlayerContainer	*gPC =	gPlayerContainer::GetIF();
	gChannelContainer	*gCC =	gChannelContainer::GetIF();
	gTileContainer		*gTC =  gTileContainer::GetIF();
	gRoomCore	*gRC =	gRoomCore::GetIF();


	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_ANSCOUPLE_ASK*)pk->strPacket);
	
	
	PLAYER gotPlayer	=	gPC->GetPlayerFromSocket(sock);
	int nRoomIndex		=	gotPlayer.nCoreFlag;

	int gotPlayerIndex	=	gRC->FindPlayerIndexInTheRoom(gotPlayer.szID , nRoomIndex);
	
	int tgPlayerIndex	=	m_favor[nRoomIndex][gotPlayerIndex].lvTargetIndex;
	PLAYER tgPlayer		=	gPC->GetPlayerFromID(gRC->FindPlayerszIDInTheRoom(tgPlayerIndex , nRoomIndex));
	

	m_favor[nRoomIndex][gotPlayerIndex].bYes = (CoupleState)ask.bYes;
	if (m_favor[nRoomIndex][gotPlayerIndex].bYes == CPS_ACCEPT && m_favor[nRoomIndex][tgPlayerIndex].bYes == CPS_ACCEPT)	{	//Ŀ��ź��
		pk_becouple_rep(nRoomIndex , gotPlayer , tgPlayer);
		
	}
	
	else if (m_favor[nRoomIndex][gotPlayerIndex].bYes != CPS_PROPOSE && m_favor[nRoomIndex][tgPlayerIndex].bYes != CPS_PROPOSE)	{	//������
		
		m_favor[nRoomIndex][gotPlayerIndex].lvTargetIndex = -1;				m_favor[nRoomIndex][tgPlayerIndex].lvTargetIndex = -1;
		m_favor[nRoomIndex][gotPlayerIndex].bYes = CPS_NONE;					m_favor[nRoomIndex][tgPlayerIndex].bYes = CPS_NONE;
		m_favor[nRoomIndex][gotPlayerIndex].point[tgPlayerIndex] /= 2;		m_favor[nRoomIndex][tgPlayerIndex].point[gotPlayerIndex] /= 2;
		
		//pk_movestart_rep
		if (m_rmWalk[nRoomIndex])	{
			

			PK_MOVESTART_REP rep;
			rep.nDist = m_rmWalk[nRoomIndex];
			rep.Dice4_1 = 0;		rep.Dice4_2 = 0;
			rep.Dice6_1 = 0;		rep.Dice6_2 = 0;

			int des = gTC->destination(m_GamePlayer[nRoomIndex][m_nTurn[nRoomIndex]].nPos , rep.nDist);
			movePlayer(nRoomIndex,m_nTurn[nRoomIndex],des,MPS_MOVE);


			m_rmWalk[nRoomIndex] = 0;

			gPC->SendSelect(PL_MOVESTART_REP,sizeof(PK_MOVESTART_REP),&rep,ECM_GAME,nRoomIndex);
		}	else	{	//���������� �� �� �༮�� �ִ� ���!~
			pk_nextturn_rep(nRoomIndex);	//����;;;;�� �ϳѰ� ����;;
		}
	}
}

void gGamePlayerContainer::pk_becouple_rep(int nRoomIndex , PLAYER player_a , PLAYER player_b)
{
	
	PK_BECOUPLE_REP rep;
	gCharinfo *gCI = gCharinfo::GetIF();
	gRoomCore *gRC = gRoomCore::GetIF();
	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	m_rmWalk[nRoomIndex] = 0;	//�����Ÿ� 0ȭ


	bool gotMale, tgMale;
	gotMale =	gCI->getMale(player_a.classtype);
	tgMale	=	gCI->getMale(player_b.classtype);

	if (gotMale && !tgMale)	{
		strcpy(rep.szMale , player_a.szID);
		strcpy(rep.szFeMale , player_b.szID);

	}
	else if (tgMale && !gotMale)	{
		strcpy(rep.szMale , player_b.szID);
		strcpy(rep.szFeMale , player_a.szID);
	}
	else	{	
		//Exception : ���� / ����Ŀ�� =��=;;
		OutputDebugString("����ź�� �����̰� -��-;;\n");
	}

	int		playerIndex_a , playerIndex_b	;
	
	playerIndex_a	=	gRC->FindPlayerIndexInTheRoom(player_a.szID , nRoomIndex);
	playerIndex_b	=	gRC->FindPlayerIndexInTheRoom(player_b.szID , nRoomIndex);

	char buf[256];
	
	wsprintf(buf,"[Match][Room : %d ; %d and %d : %d point] ", nRoomIndex , playerIndex_a , playerIndex_b , LOVEINITPOINT);
	m_favor[nRoomIndex][playerIndex_a].point[playerIndex_b] = -1;				m_favor[nRoomIndex][playerIndex_a].bYes = CPS_NONE;
	m_favor[nRoomIndex][playerIndex_b].point[playerIndex_a] = -1;				m_favor[nRoomIndex][playerIndex_b].bYes = CPS_NONE;
	m_GamePlayer[nRoomIndex][playerIndex_a].nLove = LOVEINITPOINT ;
	m_GamePlayer[nRoomIndex][playerIndex_b].nLove = LOVEINITPOINT ;

	strcpy(m_GamePlayer[nRoomIndex][playerIndex_a].szCouple , player_b.szID);
	strcpy(m_GamePlayer[nRoomIndex][playerIndex_b].szCouple , player_a.szID);

	if (m_GamePlayer[nRoomIndex][playerIndex_a].nPos != m_GamePlayer[nRoomIndex][playerIndex_b].nPos )	{	//�޷����ֱ�
		pk_warpstart_rep(nRoomIndex , playerIndex_b , m_GamePlayer[nRoomIndex][playerIndex_a].nPos );
	}
		
	gPC->SendSelect(PL_BECOUPLE_REP,sizeof(rep),&rep,ECM_GAME,nRoomIndex);
	pk_gameplayerinfo_rep(nRoomIndex);

}

//���⼭�� ���ϴ� ����?????
void	gGamePlayerContainer::pk_becoupleend_ask(PK_DEFAULT *pk , SOCKET sock)
{

	PK_BECOUPLEEND_ASK ask;

	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	gRoomCore	*gRC =	gRoomCore::GetIF();

	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_BECOUPLEEND_ASK*)pk->strPacket);
	int nRoomIndex = gPC->GetPlayerFromID(ask.szID).nCoreFlag;
	int nInRoomIndex = gRC->FindPlayerIndexInTheRoom(ask.szID , nRoomIndex);
	
	m_bSyncronize[nRoomIndex][nInRoomIndex] = true;
	if (isbSynAllTrue(nRoomIndex))	{	//����ȭ ��
		PushbSynAllPlayer(nRoomIndex, false);
		pk_nextturn_rep(nRoomIndex);
	}
}


