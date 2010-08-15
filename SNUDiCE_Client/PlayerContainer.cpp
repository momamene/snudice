#include "PlayerContainer.h"

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

void gPlayerContainer::SetMyPlayer(PLAYER* myplayer)
{
	memcpy(&m_MyPlayer, myplayer, sizeof(PLAYER));
}