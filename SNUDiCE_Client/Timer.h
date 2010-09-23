//////////////////////////////////////////////////////////////////////////
/// 10.09.23
/// Coder : �峭�˼�
///
/// ���� frame�� frame() ���� �޴´�. ��, ���� state�� frame()/m_frame °�� ���̴�.
/// �׸��� m_frame = frame() �� �Ǵ� �ֱⰡ m_cycleMs�̴�.
/// �� cycle�� ���� ���� m_turn�� ��ȭ�� �ȴ�.
///
//////////////////////////////////////////////////////////////////////////


#pragma once
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
	int				frame();							// ���� �� frame°�̴�. 
	void			frameStart(int cycleMs,int frame);	// timer start
	void			frameEnd();							// timer end
private:
	int				frameSyn();
};