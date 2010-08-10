//------------------------------------------------------------------------------------
//	gBattleNetCore Class
//
//	2010. 08. 10	CoderK
//
//	�α��� �Ǹ� ��Ʋ�� ����.
//	�游��� ä���ϰ�, �� ����.. ���� �޴��ְ� �׷���
//------------------------------------------------------------------------------------
#include "Core.h"
#include "coreconst.h"
#include "Image.h"

class gBattleNetCore : Core
{
public:
	static gBattleNetCore	*GetIF();
	
	gBattleNetCore();
	virtual ~gBattleNetCore();

public:
	gImage		m_ImgBack;
	
public:
	// overriding
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();
	
	//about mouse
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
	// end overriding

	bool		PreTransMsg(MSG &msg);
};