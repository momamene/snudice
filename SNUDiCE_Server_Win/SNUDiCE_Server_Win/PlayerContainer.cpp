#include "PlayerContainer.h"
#include "MainWin.h"

static gPlayerContainer s_PlayerContainer;

gPlayerContainer *gPlayerContainer::GetIF()
{
	return &s_PlayerContainer;
}

gPlayerContainer::gPlayerContainer()
{

}

gPlayerContainer::~gPlayerContainer()
{

}

bool gPlayerContainer::SetUp()
{
	return true;
}

void gPlayerContainer::Release()
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;
		delete temp;
		temp = NULL;
	}
	m_PlayerList.clear();
}

void gPlayerContainer::AddPlayer(PLAYER* player)
{
	PLAYER*		add;
	add = new PLAYER;

	memcpy(add, player, sizeof(PLAYER));

	m_PlayerList.push_back(add);
}

bool gPlayerContainer::isExistedPlayer(char* id)
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;

		if(strcmp(temp->szID, id) == 0)
			return true;
	}
	return false;
}

char* gPlayerContainer::DeletePlayer(SOCKET sock)
{
	PLAYER*		temp;
	char		szTemp[IDLENGTH];

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;

		if(temp->sock == sock)
		{
			strcpy(szTemp,temp->szID);
			delete temp;
			temp = NULL;
			m_PlayerList.erase(it);
			return szTemp;
			//break;
		}
	}
	return NULL;
}