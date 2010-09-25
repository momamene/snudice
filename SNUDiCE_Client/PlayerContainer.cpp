#include "PlayerContainer.h"
#include "Map.h"
#include "MainWin.h"
#include <stdio.h>

#define CHARDATAFILE		".\\Data\\chardata.dat"
#define CHARIMGDATAFILE		".\\Data\\charimgdata.dat"
#define CHARDESCRIPTFILE	".\\Data\\chardescript.dat"

gPlayerContainer s_PlayerContainer;

gPlayerContainer *gPlayerContainer::GetIF()
{
	return &s_PlayerContainer;
}

gPlayerContainer::gPlayerContainer(void)
{
}

gPlayerContainer::~gPlayerContainer(void)
{
}

void gPlayerContainer::SetMyPlayer(PK_LOGIN_REP* rep)
{
	memcpy(&m_MyPlayer, &rep->player, sizeof(PLAYER));
	memcpy(&m_MyChannel, &rep->channel, sizeof(CHANNEL));
}

void gPlayerContainer::RefreshChannel(CHANNEL *channel)
{
	memcpy(&m_MyChannel, channel, sizeof(CHANNEL));
}

void gPlayerContainer::SetMyRoom(ROOM *room)
{
	memcpy(&m_MyRoom, room, sizeof(ROOM));
}

void gPlayerContainer::SetPlayerList(PLAYER *list)
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

bool gPlayerContainer::SetUpCharInfo()
{
	FILE		*fp;

	fp = fopen(CHARDATAFILE, "rt");
	if(!fp)
		return false;

	int			i, k;
	int			nIndex = 0;		// ���° ĳ���� �Է����̳�
	int			nCount;			// ���Է����̳�. 0 ; �̸�, 1; �ܴ� .. .
	char		szBuf[256];
	char		szTemp[256];

	while( fgets(szBuf, 256, fp) != NULL)
	{
		if(szBuf[0] == '/' && szBuf[1] == '/')
			continue;								// �ּ� �ǳʶٱ�

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
					case 0:	// �̸�
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

void gPlayerContainer::Release()
{
	int			i;

	for(i = 0; i < MAXCHARNUM; i++)
	{
		m_ImgInfo[i].ImgCharSel.Release();
		m_ImgInfo[i].ImgDot.Release();
		m_ImgInfo[i].ImgPic.Release();
	}

}

bool gPlayerContainer::SetUp()
{
	if(!SetUpCharInfo())
		return false;

	if(!SetUpCharImg())
		return false;

	if(!SetupCharDesc())
		return false;

	memset(m_nAbsDrawlineX,0,sizeof(int)*ROOMMAXPLAYER);
	memset(m_nAbsDrawlineY,0,sizeof(int)*ROOMMAXPLAYER);
	memset(m_moveFoot,0,sizeof(int)*ROOMMAXPLAYER);
	memset(m_movePosition,0,sizeof(int)*ROOMMAXPLAYER);

	int		i;

	for(i = 0; i < ROOMMAXPLAYER; i++)
		m_moveFoot[i] = 1;

	return true;
}

bool gPlayerContainer::SetupCharDesc()
{
	int c,j,i;
	char temp[100]={0,};

	FILE *fp=fopen(CHARDESCRIPTFILE,"rt");
	for(j=0;j<16;j++) {
		fgets(temp,100,fp); c=0;
		for(i=0;i<strlen(temp);i++) {
			if(temp[i]==',') { m_script1[j][c]=0; break; }
			else m_script1[j][c++]=temp[i];
		}
		i++;
		while(temp[i]=='\t' || temp[i]==' ') i++;
		c=0;
		for(;i<strlen(temp);i++) {
			if(temp[i]==',') { m_script2[j][c]=0; break; }
			else m_script2[j][c++]=temp[i];
		}
		m_script2[j][c]=0;
	}
	fclose(fp);

	return true;
}

bool gPlayerContainer::SetUpCharImg()
{
	FILE		*fp;

	fp = fopen(CHARIMGDATAFILE, "rt");
	if(!fp)
		return false;

	int			i, k;
	int			nIndex = 0;		// ���° ĳ���� �Է����̳�
	int			nCount;			// ���Է����̳�.
	char		szBuf[256];
	char		szTemp[256];

	while( fgets(szBuf, 256, fp) != NULL)
	{
		if(szBuf[0] == '/' && szBuf[1] == '/')
			continue;								// �ּ� �ǳʶٱ�

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
					case 0:	// ĳ���� ���� ȭ��
						if(!m_ImgInfo[nIndex].ImgCharSel.Load(szTemp))
							return false;
						break;
					case 1:	// ��Ʈ
						if(!m_ImgInfo[nIndex].ImgDot.Load(szTemp))
							return false;
						break;
					case 2: // ĳ���� ��. ui�� �� ��
						if(!m_ImgInfo[nIndex].ImgPic.Load(szTemp))
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

void gPlayerContainer::SetMyGamePlayer(GAMEPLAYER* gp)
{
	memcpy(&m_MyGamePlayer, gp, sizeof(GAMEPLAYER));
}

void gPlayerContainer::SetGPList(GAMEPLAYER *list)
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

void gPlayerContainer::MainLoop()
{
	Draw();
}

void gPlayerContainer::PacketalDrawFix() {

	POINT		pt;

	for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
	{
		if(m_MyRoom.szRoomMaxPlayer[i][0] != '\0')
		{
			pt.x	= m_GPlayerList[i].nPos / LINEY;
			pt.y	= m_GPlayerList[i].nPos % LINEY;
			pt		= gMap::GetIF()->conToAbs(pt);
			m_nAbsDrawlineX[i] = pt.x;
			m_nAbsDrawlineY[i] = pt.y;
		}
	}
}

void gPlayerContainer::Draw()
{
	RECT	rcScr;
	RECT	rcImg;
	gMap* gmap = gMap::GetIF();

	for(int h = 0 ; h < LINEY ; h++)		// y��ǥ ������ sorting
	{	
		for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
		{
			if(m_MyRoom.szRoomMaxPlayer[i][0] != '\0' && m_GPlayerList[i].nPos%LINEY == h)
			{
				SetRect(&rcScr, 
					-gmap->m_nAbsDrawlineX + m_nAbsDrawlineX[i] + 15 ,
					-gmap->m_nAbsDrawlineY + m_nAbsDrawlineY[i] - FULLY ,
					-gmap->m_nAbsDrawlineX + m_nAbsDrawlineX[i] + 15 + 70 ,
					-gmap->m_nAbsDrawlineY + m_nAbsDrawlineY[i] - FULLY + 130 );
				SetRect(&rcImg, 
					m_moveFoot[i]*70,
					m_movePosition[i]*130,
					(m_moveFoot[i]+1)*70, 
					(m_movePosition[i]+1)*130);
				m_ImgInfo[ m_GPlayerList[i].ctype ].ImgDot.Draw(rcScr, rcImg, false);
			}
		}
	}
}

void gPlayerContainer::SyncronizeToMap(int nInRoomIndex)
{
	gMap* gmap = gMap::GetIF();

	m_nAbsDrawlineX[nInRoomIndex] = gmap->m_nAbsDrawlineX + WNDSIZEW/2 - HALFX;
	m_nAbsDrawlineY[nInRoomIndex] = gmap->m_nAbsDrawlineY + WNDSIZEH/2 - HALFY;
}

void gPlayerContainer::PutFootPosition(int nInRoomIndex,int nframe,int nCutline)
{
	// tileContainer�� m_xSpacePos �� m_ySpacePos�� �о, nMovePosition�� ����.
	// frame�� �о m_moveFoot�� ����
	m_movePosition[nInRoomIndex] = gMap::GetIF()->PositionFor_gPC();
	int nframeLocal = (nframe/nCutline);

	if(nframeLocal % 4 == 0)
		m_moveFoot[nInRoomIndex] = 1;
	else if(nframeLocal % 4 == 1)
		m_moveFoot[nInRoomIndex] = 0;
	else if(nframeLocal % 4 == 2)
		m_moveFoot[nInRoomIndex] = 1;
	else if(nframeLocal % 4 == 3)
		m_moveFoot[nInRoomIndex] = 2;
}

bool gPlayerContainer::isTurn(int turn)
{
	if(strcmp(m_GPlayerList[turn].szID, m_MyGamePlayer.szID) == 0)
		return true;
	else
		return false;
}