#include "PlayerContainer.h"
#include "Map.h"
#include "MainWin.h"
#include "UIGame.h"
#include <stdio.h>
#include <algorithm>

using namespace std;

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

	m_nNoDraw = -1;
	m_nNoDraw2 = -1;

	return true;
}

void gPlayerContainer::Clear()
{
	memset(m_moveFoot,0,sizeof(int)*ROOMMAXPLAYER);
	memset(m_movePosition,0,sizeof(int)*ROOMMAXPLAYER);

	int		i;

	for(i = 0; i < ROOMMAXPLAYER; i++)
		m_moveFoot[i] = 1;

	m_nNoDraw = -1;
	m_nNoDraw2 = -1;
}

bool gPlayerContainer::SetupCharDesc()
{
	int c,j,i;
	char temp[100]={0,};

	FILE	*fp = fopen(CHARDESCRIPTFILE,"rt");
	for(j = 0;j < 16;j++)
	{
		fgets(temp, 100, fp); c=0;
		for(i = 0;i < (int)strlen(temp); i++)
		{
			if(temp[i]==',')
			{
				m_script1[j][c]=0;
				break;
			}
			else
				m_script1[j][c++] = temp[i];
		}
		i++;
		while(temp[i]=='\t' || temp[i]==' ') i++;
		c=0;
		for(; i < (int)strlen(temp); i++)
		{
			if(temp[i]==',')
			{
				m_script2[j][c]=0;
				break;
			}
			else
				m_script2[j][c++] = temp[i];
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
					case 1:	// 도트
						if(!m_ImgInfo[nIndex].ImgDot.Load(szTemp))
							return false;
						break;
					case 2: // 캐릭터 얼굴. ui에 쓸 거
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
	memcpy(&m_GPlayerList, list, sizeof(GAMEPLAYER) * ROOMMAXPLAYER);

	int			i;

	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strcmp(m_MyPlayer.szID, m_GPlayerList[i].szID) == 0)
		{
			SetMyGamePlayer(&m_GPlayerList[i]);
			break;
		}
	}

	if(gMainWin::GetIF()->m_eCoreMode == ECM_GAME)
		gUIGame::GetIF()->SetRankList();

}

void gPlayerContainer::MainLoop()
{
	Draw();
}

void gPlayerContainer::Draw()
{
	RECT	rcScr;
	RECT	rcImg;
	gMap* gmap = gMap::GetIF();

	for(int h = 0 ; h < LINEY ; h++)		// y좌표 순으로 sorting
	{	
		for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
		{
			if(m_MyRoom.szRoomMaxPlayer[i][0] != '\0' && m_GPlayerList[i].nPos%LINEY == h)
			{
				if(m_nNoDraw == i || m_nNoDraw2 == i)
					continue;

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


void gPlayerContainer::MainLoop_Busing(gImage *bus, RECT *rcDest, RECT *rcSour, int turn)
{
	Draw_Busing(bus, rcDest, rcSour, turn);
}

void gPlayerContainer::Draw_Busing(gImage *bus, RECT *rcDest, RECT *rcSour, int turn)
{
	RECT	rcScr;
	RECT	rcImg;

	gMap* gmap = gMap::GetIF();

	int		busY = m_GPlayerList[turn].nPos % LINEY;

	for(int h = 0 ; h < LINEY ; h++)		// y좌표 순으로 sorting
	{	
		if(h == busY)
		{
			if(bus)
				bus->Draw(*rcDest, *rcSour, false);
		}
		for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
		{
			if(m_nNoDraw == i || m_nNoDraw2 == i)
				continue;

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

void gPlayerContainer::MainLoop_Warp(int charidx, int dY)
{
	Draw_Warp(charidx, dY);
}

void gPlayerContainer::MainLoop_WarpList(int *dest, bool drawAll, int dY)
{
	Draw_WarpList(dest, drawAll, dY);
}

void gPlayerContainer::Draw_Warp(int charidx, int dY)
{
	RECT	rcScr;
	RECT	rcImg;

	gMap* gmap = gMap::GetIF();

	for(int h = 0 ; h < LINEY ; h++)		// y좌표 순으로 sorting
	{	
		for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
		{
			if(m_nNoDraw == i || m_nNoDraw2 == i)
				continue;

			if(m_MyRoom.szRoomMaxPlayer[i][0] != '\0' && m_GPlayerList[i].nPos%LINEY == h)
			{
				SetRect(&rcScr, 
					-gmap->m_nAbsDrawlineX + m_nAbsDrawlineX[i] + 15 ,
					-gmap->m_nAbsDrawlineY + m_nAbsDrawlineY[i] - FULLY ,
					-gmap->m_nAbsDrawlineX + m_nAbsDrawlineX[i] + 15 + 70 ,
					-gmap->m_nAbsDrawlineY + m_nAbsDrawlineY[i] - FULLY + 130 );

				if(i == charidx)
					OffsetRect(&rcScr, 0, dY);

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

void gPlayerContainer::Draw_WarpList(int *dest, bool drawAll, int dY)
{
	RECT	rcScr;
	RECT	rcImg;

	gMap* gmap = gMap::GetIF();

	for(int h = 0 ; h < LINEY ; h++)		// y좌표 순으로 sorting
	{	
		for(int i = 0 ; i < ROOMMAXPLAYER ; i++)
		{
			if(!drawAll)
				if(dest[i] == -1)
					continue;

			if(m_MyRoom.szRoomMaxPlayer[i][0] != '\0' && m_GPlayerList[i].nPos%LINEY == h)
			{
				SetRect(&rcScr, 
					-gmap->m_nAbsDrawlineX + m_nAbsDrawlineX[i] + 15 ,
					-gmap->m_nAbsDrawlineY + m_nAbsDrawlineY[i] - FULLY ,
					-gmap->m_nAbsDrawlineX + m_nAbsDrawlineX[i] + 15 + 70 ,
					-gmap->m_nAbsDrawlineY + m_nAbsDrawlineY[i] - FULLY + 130 );

				if(dest[i] != -1)
					OffsetRect(&rcScr, 0, dY);

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


void gPlayerContainer::SyncronizeToMap(int nInRoomIndex, int pairIndex)
{
	gMap* gmap = gMap::GetIF();
	const int INTERVAL = 4;
	static int bef=-1, countdown, num, i;
	static pair<int,int> plow[INTERVAL];

	if(nInRoomIndex!=-2 && bef != nInRoomIndex) countdown=num=i=0;
	if(pairIndex != -1) {
		if(num>=INTERVAL) {
			m_nAbsDrawlineX[pairIndex] = plow[i].first + WNDSIZEW/2 - HALFX;
			m_nAbsDrawlineY[pairIndex] = plow[i].second + WNDSIZEH/2 - HALFY;
			i=(i+1)%INTERVAL;
		}
	}
	bef=nInRoomIndex;
	plow[countdown]=make_pair(gmap->m_nAbsDrawlineX, gmap->m_nAbsDrawlineY);
	countdown = (countdown+1)%INTERVAL; num++;

	if(nInRoomIndex != -2) {
		m_nAbsDrawlineX[nInRoomIndex] = gmap->m_nAbsDrawlineX + WNDSIZEW/2 - HALFX;
		m_nAbsDrawlineY[nInRoomIndex] = gmap->m_nAbsDrawlineY + WNDSIZEH/2 - HALFY;
	}
}

void gPlayerContainer::PutFootPosition(int nInRoomIndex,int nframe,int nCutline, int couple)
{
	// tileContainer의 m_xSpacePos 와 m_ySpacePos를 읽어서, nMovePosition을 결정.
	// frame을 읽어서 m_moveFoot을 결정
	const int INTERVAL = 4;
	int nframeLocal = (nframe/nCutline), r;

	if(nframeLocal % 4 == 0) r = 1;
	else if(nframeLocal % 4 == 1) r = 0;
	else if(nframeLocal % 4 == 2) r = 1;
	else if(nframeLocal % 4 == 3) r = 2;

	static int bef = -1, count, num, i;
	static pair<int,int> plow[INTERVAL];

	if(nInRoomIndex!=-2 && bef != nInRoomIndex) count = num = i = 0;
	if(couple!=-1) { 
		if(num>=INTERVAL) {
			m_movePosition[couple] = plow[i].first;
			m_moveFoot[couple] = plow[i].second;
			i=(i+1)%INTERVAL;
		}
	}
	bef = nInRoomIndex; num++;
	plow[count] = make_pair(gMap::GetIF()->PositionFor_gPC(), r); count=(count+1)%INTERVAL;

	if(nInRoomIndex!=-2) {
		m_movePosition[nInRoomIndex] = gMap::GetIF()->PositionFor_gPC();
		m_moveFoot[nInRoomIndex] = r;
	}
}

bool gPlayerContainer::isTurn(int turn)
{
	if(strcmp(m_GPlayerList[turn].szID, m_MyGamePlayer.szID) == 0)
		return true;
	else
		return false;
}

int gPlayerContainer::GetCoupleIndex(int nTurn)
{
	if(strlen(m_GPlayerList[nTurn].szCouple) == 0) return -1;

	for(int i=0; i<ROOMMAXPLAYER; i++)
		if(!strcmp(m_GPlayerList[nTurn].szCouple, m_GPlayerList[i].szID))
			return i;
	return -1;
}

int gPlayerContainer::GetMyGPIndex()
{
	int			i;

	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strcmp(m_MyGamePlayer.szID, m_GPlayerList[i].szID) == 0)
			return i;
	}
	return -1;
}

int gPlayerContainer::GetMyPIndex()
{
	int			i;

	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strcmp(m_MyPlayer.szID, m_PlayerList[i].szID) == 0)
			return i;
	}
	return -1;
}

int gPlayerContainer::GetGPNum()
{
	int		temp = 0;
	int		i;

	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strlen(m_GPlayerList[i].szID) != 0)
			temp++;
	}
	return temp;
}

void gPlayerContainer::FootClear()
{
	int		i;

	for(i = 0; i < ROOMMAXPLAYER; i++)
		m_moveFoot[i] = 1;
}

int	gPlayerContainer::GetGPIndex(char* id)
{
	int		i;

	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strcmp(m_GPlayerList[i].szID, id) == 0)
			return i;
	}
	return -1;
}

bool gPlayerContainer::Restore()
{
	int		i;

	for(i = 0; i < MAXCHARNUM; i++)
	{
		if(!m_ImgInfo[i].ImgCharSel.Restore())
			return false;
		if(!m_ImgInfo[i].ImgDot.Restore())
			return false;
		if(!m_ImgInfo[i].ImgPic.Restore())
			return false;
	}
	return true;
}

int gPlayerContainer::GetMyItemNum()
{
	int		i;
	int		count = 0;

	for(i = 0; i < MAXITEMNUM; i++)
	{
		if(m_MyGamePlayer.nItem[i] != -1)
			count++;
	}
	return count;
}

int	gPlayerContainer::GetCharNumPos(int nPos)
{
	int		i;
	int		count = 0;

	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strlen(m_GPlayerList[i].szID) != 0)
		{
			if(m_GPlayerList[i].nPos == nPos)
				count++;
		}
	}
	return count;
}

GAMEPLAYER*	gPlayerContainer::GetPlayerByPos(int nPos)
{
	int		i;

	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strlen(m_GPlayerList[i].szID) != 0)
		{
			if(strcmp(m_GPlayerList[i].szID, m_MyGamePlayer.szID) == 0 )
				continue;
			if(m_GPlayerList[i].nPos == nPos)
				return &m_GPlayerList[i];
		}
	}
	return NULL;
}