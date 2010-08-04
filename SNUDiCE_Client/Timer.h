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
	//int				frameAuto();
	//int				frameNoneAuto();
	int				frame();
	void			frameStart(int cycleMs,int frame);
	void			frameEnd();
//private:
	int				frameSyn();
};