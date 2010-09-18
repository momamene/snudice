//------------------------------------------------------------------------------------
//	gPlayerContainer Class
//
//	2010. 08. 02	CoderK
//
//	�÷��̾� �ٷ���
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
	PLAYER			m_MyPlayer;		// ��
	CHANNEL			m_MyChannel;
	ROOM			m_MyRoom;

public:
	void			SetMyPlayer(PK_LOGIN_REP *rep);
	void			RefreshChannel(CHANNEL *channel);
	void			SetMyRoom(ROOM *room);
};
