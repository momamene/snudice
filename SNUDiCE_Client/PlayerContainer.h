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
	CHANNEL			m_MyChannel;

public:
	void			SetMyPlayer(PK_LOGIN_REP *rep);
	void			RefreshChannel(PK_CHANNELREFRESH_REP *rep);
};
