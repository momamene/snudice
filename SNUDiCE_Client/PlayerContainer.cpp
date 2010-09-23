#include "PlayerContainer.h"
#include <stdio.h>

#define CHARDATAFILE		".\\Data\\chardata.dat"
#define CHARIMGDATAFILE		".\\Data\\charimgdata.dat"


gDataContainer s_PlayerContainer;

gDataContainer *gDataContainer::GetIF()
{
	return &s_PlayerContainer;
}

gDataContainer::gDataContainer(void)
{
}

gDataContainer::~gDataContainer(void)
{
}

void gDataContainer::SetMyPlayer(PK_LOGIN_REP* rep)
{
	memcpy(&m_MyPlayer, &rep->player, sizeof(PLAYER));
	memcpy(&m_MyChannel, &rep->channel, sizeof(CHANNEL));
}

void gDataContainer::RefreshChannel(CHANNEL *channel)
{
	memcpy(&m_MyChannel, channel, sizeof(CHANNEL));
}

void gDataContainer::SetMyRoom(ROOM *room)
{
	memcpy(&m_MyRoom, room, sizeof(ROOM));
}

void gDataContainer::SetPlayerList(PLAYER *list)
{
	memcpy(m_PlayerList, list, sizeof(PLAYER) * ROOMMAXPLAYER);

	for(int i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strcmp(m_PlayerList[i].szID, m_MyPlayer.szID) == 0)
		{
			memcpy(&m_MyPlayer, &m_PlayerList[i], sizeof PLAYER);
			break;
		}
	}
}

bool gDataContainer::SetUpCharInfo()
{
	FILE		*fp;

	fp = fopen(CHARDATAFILE, "rt");
	if(!fp)
		return false;

	int			i, k;
	int			nIndex = 0;		// 몇번째 캐릭터 입력중이냐
	int			nCount;			// 뭐입력중이나. 0 ; 이름, 1; 단대 .. .
	char		szBuf[256];
	char		szTemp[256];

	while( fgets(szBuf, 256, fp) != NULL)
	{
		if(szBuf[0] == '/' && szBuf[1] == '/')
			continue;								// 주석 건너뛰기

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
					case 0:	// 이름
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

void gDataContainer::Release()
{
	int			i;

	for(i = 0; i < MAXCHARNUM; i++)
	{
		m_ImgInfo[i].ImgCharSel.Release();
	}

}

bool gDataContainer::SetUp()
{
	if(!SetUpCharInfo())
		return false;

	if(!SetUpCharImg())
		return false;

	return true;
}

bool gDataContainer::SetUpCharImg()
{
	FILE		*fp;

	fp = fopen(CHARIMGDATAFILE, "rt");
	if(!fp)
		return false;

	int			i, k;
	int			nIndex = 0;		// 몇번째 캐릭터 입력중이냐
	int			nCount;			// 뭐입력중이나.
	char		szBuf[256];
	char		szTemp[256];

	while( fgets(szBuf, 256, fp) != NULL)
	{
		if(szBuf[0] == '/' && szBuf[1] == '/')
			continue;								// 주석 건너뛰기

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
					case 0:	// 캐릭터 선택 화면
						if(!m_ImgInfo[nIndex].ImgCharSel.Load(szTemp))
							return false;
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

void gDataContainer::SetMyGamePlayer(GAMEPLAYER* gp)
{
	memcpy(&m_MyGamePlayer, gp, sizeof(GAMEPLAYER));
}

void gDataContainer::SetGPList(GAMEPLAYER *list)
{
	memcpy(&m_GPlayerList, list, sizeof(PLAYER) * ROOMMAXPLAYER);

	int			i;

	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strcmp(m_MyPlayer.szID, m_GPlayerList[i].szID) == 0)
		{
			SetMyGamePlayer(&m_GPlayerList[i]);
			break;
		}
	}
}