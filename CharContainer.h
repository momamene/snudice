//------------------------------------------------------------------------------------
//	gCharManager Class
//
//	2010. 07. 17	CoderK
//
//	ĳ���� ���õ� �͵� ó��
//------------------------------------------------------------------------------------
#pragma once
#include "gChar.h"

class gCharManager  
{
public:
	static gCharManager *GetIF();

	gCharManager();
	virtual ~gCharManager();

public:
	gChar		*m_Chars;

	bool		SetUp();
	void		Release();

};

