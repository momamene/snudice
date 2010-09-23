#pragma once
#include "network.h"

class gGamePlayerContainer
{
public:
	static gGamePlayerContainer *GetIF();

	GAMEPLAYER	m_GamePlayer[MAXROOM][ROOMMAXPLAYER];
	bool		m_isGamePlayer[MAXROOM][ROOMMAXPLAYER];
	CHARINFO	m_CharInfo[CLASS_END];

	void		pk_maingamestart_rep(int nRoomIndex);

	bool		SetUp();
	bool		init(int nRoomIndex);
	void		Release();
};