// gPlayerManager.cpp: implementation of the gPlayerManager class.
//
//////////////////////////////////////////////////////////////////////

#include "gPlayerManager.h"
#include "gTitleCore.h"
#include "gCharManager.h"

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
	for(int i = 0 ; i < MAXPLAYER ; i++)
	{
		if(m_player[i].m_nNP != -1)
		{
			m_player[i].Draw();
		}
	}
}

void gPlayerManager::SetPlayer()
{

}

