//------------------------------------------------------------------------------------
//	gItemContainer Class
//
//	2010. 10. 01	CoderK
//
//	������ �����̳�
//------------------------------------------------------------------------------------
#pragma once
#include "network.h"

#define COUPLE_BROCKEN_DEBUF_INDEX ITEMNUM 
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
