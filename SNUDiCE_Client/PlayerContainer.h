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

public:
	void			SetMyPlayer(PLAYER* myplayer);
};
