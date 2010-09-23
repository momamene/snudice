#include "GamePlayerContainer.h"
#include "RoomCore.h"
#include "TileContainer.h"
#include "PlayerContainer.h"
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
	int   nIndex = 0;  // ���° ĳ���� �Է����̳�
	int   nCount;   // ���Է����̳�. 0 ; �̸�, 1; �ܴ� .. .
	char  szBuf[256];
	char  szTemp[256];
	while( fgets(szBuf, 256, fp) != NULL)
	{
		if(szBuf[0] == '/' && szBuf[1] == '/')
			continue;        // �ּ� �ǳʶٱ�
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
				case 0: // �̸�
					strcpy(m_CharInfo[nIndex].szName, szTemp);
					break;
				case 1: // �ܰ�����
					strcpy(m_CharInfo[nIndex].szCollege, szTemp);
					break;
				case 2: // ����
					if( strcmp(szTemp, "��") == 0 )
						m_CharInfo[nIndex].bMale = true;
					else
						m_CharInfo[nIndex].bMale = false;
					break;
				case 3: // ���
					m_CharInfo[nIndex].nLang = atoi(szTemp);
					break;
				case 4: // ����
					m_CharInfo[nIndex].nMath = atoi(szTemp);
					break;
				case 5: // ����
					m_CharInfo[nIndex].nArt = atoi(szTemp);
					break;
				case 6: // ü��
					m_CharInfo[nIndex].nStamina = atoi(szTemp);
					break;
				case 7: // 4��ü
					m_CharInfo[nIndex].nDice4 = atoi(szTemp);
					break;
				case 8: // 6��ü
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
	gRC->FindClasstypeFromIDs_RMP(nRoomIndex,classtype);

	memset(m_GamePlayer[nRoomIndex], 0, sizeof(GAMEPLAYER) * ROOMMAXPLAYER);

	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
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
			// sangwoo temp
			for(int j = 0 ; j < MAXSUBJECT ; j++) 
				m_GamePlayer[nRoomIndex][i].fGrade[j] = 0.7;
			m_GamePlayer[nRoomIndex][i].nPos = gTC->m_xInitSpacePos * LINEY + gTC->m_yInitSpacePos;
			// end
		}
	}

	return true;
}

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
	int nInRoomIndex = gRC->FindThePlayerInTheRoom(ask.szID,nRoomIndex);

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
	if(des == gTC->m_xInitSpacePos*LINEY+gTC->m_yInitSpacePos) { // flip
		if(m_isNokdu[nRoomIndex][nInRoomIndex]) m_isNokdu[nRoomIndex][nInRoomIndex] = false;
		else m_isNokdu[nRoomIndex][nInRoomIndex] = true;
	}
	m_GamePlayer[nRoomIndex][nInRoomIndex].nPos = des;


	gPC->SendSelect(PL_MOVESTART_REP,sizeof(PK_MOVESTART_REP),&rep,ECM_GAME,nRoomIndex);
}

void gGamePlayerContainer::Release()
{
	
}