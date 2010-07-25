#include "gContainer.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

void gContainer::init()
{
	m_clickstate = none;
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

int gContainer::absToIndex(POINT pt)
{
	if(pt.x<0||pt.y<0||pt.x>FULLX||pt.y>FULLY) return -1;
	int ans;
	ans = (pt.x*LINEX)/FULLX + ((pt.y*LINEY)/FULLY)*LINEX;
	if( ans<0 || ans>DAILY ) return -1;
	else return ans;
}

RECT gContainer::index_valueToRect(int index,float val)
{
	//if( index<0 || index>DAILY ) ; // return NULL;
	RECT rc;
	rc.left = ((index%LINEX)*FULLX)/LINEX;
	rc.right = rc.left + FULLX/LINEX;
	rc.bottom = ((index/LINEX)*FULLY)/LINEY + FULLY/LINEY/2;
	rc.top = rc.bottom - HEIGHTRATE*val;
	return rc;
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

void gContainer::LClick(int x, int y )
{
	POINT tempPT;
	int index;

	tempPT.x = x;
	tempPT.y = y;
	index = absToIndex(tempPT);
	if(m_clickstate!=none)
		m_gstream[index].m_standardLoad[m_clickstate]++;
}

void gContainer::RClick()
{
	if(m_clickstate==none) m_clickstate=(State8)0;
	else m_clickstate = (State8)((int)m_clickstate + 1);
}

