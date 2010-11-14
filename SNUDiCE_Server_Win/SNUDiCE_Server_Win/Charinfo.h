#pragma once
#include "network.h"

#define CHARDATAFILE ".\\chardata.dat"

class gCharinfo
{
public:
	static gCharinfo *GetIF();

	CHARINFO		m_CharInfo[CLASS_END];

public:
	bool			SetUp();
	void			Release();

	CHARINFO		getCharinfo(int index);
	bool			getMale(int index);
};