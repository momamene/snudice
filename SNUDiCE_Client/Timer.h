//////////////////////////////////////////////////////////////////////////
/// 10.09.23
/// Coder : 장난죄송
///
/// 현재 frame은 frame() 으로 받는다. 즉, 현재 state는 frame()/m_frame 째인 것이다.
/// 그리고 m_frame = frame() 이 되는 주기가 m_cycleMs이다.
/// 한 cycle이 지난 것은 m_turn의 변화로 안다.
///
//////////////////////////////////////////////////////////////////////////


#pragma once
class gTimer {
public:
	static gTimer	*GetIF();
	//private:
	int				m_start;		// start 시점의 CPU time

	int				m_cycleMs;		// 몇 Ms 가 지나면 1턴이 지난다.
	int				m_frame;		// 1턴당 몇 frame일까?
	int				m_turn;			// 몇턴이 지났다.
	bool			m_on;

public:
	void			SetUp();	
	int				frame();							// 지금 몇 frame째이다. 
	void			frameStart(int cycleMs,int frame);	// timer start
	void			frameEnd();							// timer end
private:
	int				frameSyn();
};