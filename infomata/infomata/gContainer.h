#pragma once
#include <windows.h>
#include "const.h"
#include "gStream.h"


class gContainer
{
public:
	gStream		m_gstream[DAILY];

public:
	int			absToIndex(POINT pt);
	RECT		index_valueToRect(int index,float val);

};
