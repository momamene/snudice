class gTimer {
public:
	static gTimer	*GetIF();
//private:
	int				m_start;		// start ������ CPU time

	int				m_cycleMs;		// �� Ms �� ������ 1���� ������.
	int				m_frame;		// 1�ϴ� �� frame�ϱ�?
	int				m_turn;			// ������ ������.
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