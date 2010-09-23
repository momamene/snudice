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
	gRC->FindClasstypeFromIDs_RMP(nRoomIndex,classtype);

	memset(m_GamePlayer[nRoomIndex], 0, sizeof(GAMEPLAYER) * ROOMMAXPLAYER);

	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
	{
		if(gRC->m_rooms[nRoomIndex].szRoomMaxPlayer[i][0] == '\0') {
			m_isGamePlayer[nRoomIndex][i] = false;
		}
		else {
			m_isGamePlayer[nRoomIndex][i] = true;
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
	rep.nTurn = 0; // 치명적 temp - 당장 바꿔야지.

	gPC->PutModeToModeForAll(ECM_SUBMIT,nRoomIndex,ECM_GAME);
	
	gPC->SendSelect(PL_MAINGAMESTART_REP,sizeof(PK_MAINGAMESTART_REP),&rep,ECM_GAME,nRoomIndex);
}


void gGamePlayerContainer::Release()
{
	
}