//------------------------------------------------------------------------------------
//	gCharManager Class
//
//	2010. 07. 17	CoderK
//
//	캐릭터 관련된 것들 처리
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

