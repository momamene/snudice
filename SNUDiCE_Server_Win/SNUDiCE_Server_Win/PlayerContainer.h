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
	bool			DeletePlayer(SOCKET sock, char clientID[IDLENGTH]);
	bool			SetUp();
	void			Release();

	bool			PutMode(char* id, eCOREMODE mode);
	bool			PutCoreFlag(char* id, int flag);

	// packet

	void			pk_login_ask(PK_DEFAULT *pk, SOCKET sock);
	bool			isExistedPlayer(char* id);
	bool			FindSocketFromID(char* id, SOCKET* getSock);

	void			SendSelect (ePROTOCOL prot,int pkSize,void *pk,eCOREMODE mode,int nPage);	// Player �߿��� nPage�� ����� ������� Send�ϴ� Ư���Լ�.

	//	void			PrintUserList();

};