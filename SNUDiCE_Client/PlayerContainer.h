//------------------------------------------------------------------------------------
//	gPlayerContainer Class
//
//	2010. 08. 02	CoderK
//
//	플레이어 다루자
//------------------------------------------------------------------------------------
#pragma once
#include "networkconst.h"

class gPlayerContainer
{
public:
	static gPlayerContainer *GetIF();

	gPlayerContainer(void);
	virtual ~gPlayerContainer(void);
public:
	PLAYER			m_MyPlayer;		// 나

public:
	void			SetMyPlayer(PLAYER* myplayer);
};
