#include <windows.h>
#include "Timer.h"
#include "MainWin.h"

static gTimer s_timer;

gTimer *gTimer::GetIF()
{
	return &s_timer;
}


void gTimer::SetUp()
{
	m_start=GetTickCount();
	m_turn =0;
	m_on   =false;
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
	int		time = GetTickCount();
	while( time - m_start > m_cycleMs){
		m_start += m_cycleMs;
		m_turn++;
	}
	return m_turn;
}

void gTimer::frameEnd(){
	m_start = GetTickCount();
	m_turn = 0;
	m_on = false;
}