#include <windows.h>
#include "gTimer.h"
#include "gMainWin.h"

static gTimer s_timer;

gTimer *gTimer::GetIF()
{
	return &s_timer;
}


void gTimer::SetUp()
{
	/*
	m_start = GetTickCount();
	m_cycleMs = 1000;
	m_frame = 0;
	*/
	m_turn =  0;
	m_on = false;
}

int gTimer::frame()
{
	gMainWin *gmainWin = gMainWin::GetIF();
	if (!m_on) {
		MessageBox(gmainWin->m_hWnd, "gTimer 치명적 오류 : 적절하지 않은 Timer 사용", "Error", MB_OK);
		return -1;
	}
	frameSyn();
	//if(m_cycleMs > 0 )
	return (((GetTickCount() - m_start))*m_frame)/m_cycleMs;
}

/*
int gTimer::frameNoneAuto()
{
	if(m_cycleMs > 0)
		return ((m_start - GetTickCount())/m_cycleMs)*m_frame;
}
*/

void gTimer::frameStart(int cycleMs,int frame) {
	m_on = true;
	if(cycleMs > 0 && frame > 0 ){
		m_cycleMs = cycleMs;
		m_frame = frame;
		m_start = GetTickCount();
		m_turn = 0;
	}
}

int gTimer::frameSyn() {
	int count=0;
	while((GetTickCount() - m_start) > m_cycleMs){
		m_start += m_cycleMs;
		m_turn++;
	}
	return count;
}

void gTimer::frameEnd(){
	m_start = GetTickCount();
//	m_turn = 0;
	m_on = false;
}