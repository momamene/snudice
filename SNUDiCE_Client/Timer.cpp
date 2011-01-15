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
		int a=1; //gTimer::치명적인 타이머 오류
		a/=0;
		return -1;
	}
	frameSyn();
	//if(m_cycleMs > 0 )
	return (((GetTickCount() - m_start))*m_frame)/m_cycleMs;
}


void gTimer::frameStart(int cycleMs,int frame) {
	if(m_on)
	{
		int	t = 3;
	}
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