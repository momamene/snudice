#pragma once
#include "network.h"

class gGamePlayerContainer
{
public:
	static gGamePlayerContainer *GetIF();

	GAMEPLAYER	m_GamePlayer[MAXROOM][ROOMMAXPLAYER];
	bool		m_isGamePlayer[MAXROOM][ROOMMAXPLAYER];
	CHARINFO	m_CharInfo[CLASS_END];
	bool		m_isNokdu[MAXROOM][ROOMMAXPLAYER];

	void		pk_maingamestart_rep(int nRoomIndex);
	void		pk_movestart_ask(PK_DEFAULT *pk,SOCKET sock);

	bool		SetUp();
	bool		init(int nRoomIndex);
	void		Release();
};