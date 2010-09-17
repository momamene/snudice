//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//	gPlayerContainer.h
//
//	2010. 08. 10		CoderK
//
//	로그인된 플레이어들의 정보를 담고 있음
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
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

	void			SendSelect (ePROTOCOL prot,int pkSize,void *pk,eCOREMODE mode,int nPage);	// Player 중에서 nPage인 사람들 대상으로 Send하는 특수함수.

	//	void			PrintUserList();

};