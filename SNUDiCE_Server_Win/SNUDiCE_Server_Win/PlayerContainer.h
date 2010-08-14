//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//	gPlayerContainer.h
//
//	2010. 08. 10		CoderK
//
//	�α��ε� �÷��̾���� ������ ��� ����
//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
#include "network.h"
#include <list>

using namespace std;

typedef list<PLAYER*> PLAYER_LIST;

class gPlayerContainer
{
public:
	static gPlayerContainer *GetIF();

	gPlayerContainer();
	virtual ~gPlayerContainer();

public:
	PLAYER_LIST		m_PlayerList;

public:
	void			AddPlayer(PLAYER* player);
	void			DeletePlayer(SOCKET sock);
	bool			SetUp();
	void			Release();

	// packet

	void			pk_login_ask(PK_DEFAULT *pk, SOCKET sock);
	bool			isExistedPlayer(char* id);

	//	void			PrintUserList();

};