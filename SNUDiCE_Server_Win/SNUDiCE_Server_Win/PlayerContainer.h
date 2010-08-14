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
	void			DeletePlayer(SOCKET sock);
	bool			SetUp();
	void			Release();

	// packet

	void			pk_login_ask(PK_DEFAULT *pk, SOCKET sock);
	bool			isExistedPlayer(char* id);

	//	void			PrintUserList();

};