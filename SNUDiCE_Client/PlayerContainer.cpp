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