//------------------------------------------------------------------------------------
//	gItemContainer Class
//
//	2010. 10. 01	CoderK
//
//	������ �����̳�
//------------------------------------------------------------------------------------
#pragma once
#include "networkconst.h"
#include "Image.h"

#define ITEMCARDIMG_W		140
#define ITEMCARDIMG_H		196

class gItemContainer
{
public:
	static gItemContainer *GetIF();

	gItemContainer(void);
	~gItemContainer(void);

public:
	ITEMCARD		m_ItemList[ITEMNUM];
	gImage			m_ItemImg[ITEMNUM];

public:
	bool		SetUp();
	void		Release();
};
