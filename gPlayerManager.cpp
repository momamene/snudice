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

void gPlayerManager::SetUp(){
	gTitleCore *gtitleCore = gTitleCore::GetIF();
	gCharManager *gcharManager = gCharManager::GetIF();
	
	m_playerN = 0;
	for(int i = 0 ; i < MAXPLAYER ; i++) {
		m_playerState[i] = gtitleCore->m_ePlayer[i];
		if(m_playerState[i] != EPS_NONE){
			m_player[i].SetUp(gcharManager->m_Chars[10+i]);
			m_playerN++;
		}
	}
	
}

void gPlayerManager::Draw(){
	for(int i = 0 ; i < MAXPLAYER ; i++) {
		if(m_playerState[i] != EPS_NONE) {
			m_player[i].Draw();
		}
	}
}

/*
gPlayerManager::gPlayerManager()
{

}

gPlayerManager::~gPlayerManager()
{

}
*/