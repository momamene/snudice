//------------------------------------------------------------------------------------
//	gItemContainer Class
//
//	2010. 10. 01	CoderK
//
//	아이템 컨테이너
//------------------------------------------------------------------------------------
#pragma once
#include "network.h"

class gItemContainer
{
public:
	static gItemContainer *GetIF();

public:
	ITEMCARD		m_ItemList[ITEMNUM];

public:
	bool		SetUp();
	void		Release();
};
