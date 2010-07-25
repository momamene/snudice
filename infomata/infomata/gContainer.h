#pragma once
#include <windows.h>
#include "const.h"
#include "gStream.h"


class gContainer
{
public:
	gStream		m_gstream[DAILY];
	State8		m_clickstate;

public:
	void		init();
	
	int			absToIndex(POINT pt);
	RECT		index_valueToRect(int index,float val);
	
	void		LClick(int x,int y);
	void		RClick();

};
