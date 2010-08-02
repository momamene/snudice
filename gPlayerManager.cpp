// gPlayerManager.cpp: implementation of the gPlayerManager class.
//
//////////////////////////////////////////////////////////////////////

#include "gPlayerManager.h"
#include "gTitleCore.h"
#include "gCharManager.h"
#include "gGameCore.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static gPlayerManager s_gPlayerManager; // 2

gPlayerManager *gPlayerManager::GetIF() // 3
{
	return &s_gPlayerManager;
}

gPlayerManager::gPlayerManager()
{

}

gPlayerManager::~gPlayerManager()
{

}


void gPlayerManager::SetUp()
{
	int		i;

	for(i = 0; i < MAXPLAYER; i++)
	{
		switch(gTitleCore::GetIF()->m_ePlayer[i])
		{
			case EPS_PLAYER:
				m_player[i].m_bUser = true;
				m_player[i].m_nNP = i;
				m_playerN++;
				break;
			case EPS_COM:
				m_player[i].m_bUser = false;
				m_player[i].m_nNP = i;
				m_playerN++;
				break;
			case EPS_NONE:
				m_player[i].m_nNP = -1;
				break;
		}
	}
}

void gPlayerManager::Draw(){
	tileContainer *tilecontainer = tileContainer::GetIF();

	/*
	for(int i = 0 ; i < MAXPLAYER ; i++)
	{
		if(m_player[i].m_nNP != -1)
		{
			m_player[i].Draw();
		}
	}
	*/
	for(int i = 0 ; i < LINEX*LINEY ; i++){
		if(tilecontainer->tileMap[i].tileType==TY_NONE) continue;
		for(int j = 0 ; j < MAXPLAYER ; j++){
			if(m_player[j].m_nNP!=-1&&m_player[j].m_xSpacePos==i/LINEY&&m_player[j].m_ySpacePos==i%LINEY) m_player[j].Draw();
		}
	}

}

void gPlayerManager::Release()
{
	int		i;

	for(i = 0; i < MAXPLAYER; i++)
		m_player[i].Release();
}

int	gPlayerManager::StudentNum(int flag) // flag = flag2 = index != flag1
{
	gGameCore *gameCore = gGameCore::GetIF();
	int res=0;
	for(int i = 0 ; i < MAXPLAYER ; i++){
		// cantate
		if(/*m_player[i].m_nNP!=-1&&*/m_player[i].isMySubject(flag)) res++;
	}
	return res;
}

void gPlayerManager::CooltimePass() 
{
	for(int i = 0 ; i < MAXPLAYER ; i++) {
		if(m_player[i].m_nNP == -1) continue;
		for(int j = 0 ; j < MAXCARD ; j++) {
			if(m_player[i].m_itemCooltime[j] > 0 ) m_player[i].m_itemCooltime[j]--;
		}
	}
	return;
}