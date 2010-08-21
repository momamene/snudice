#pragma once
#include "network.h"
#include <list>

using namespace std;

typedef list<USER*>	USER_LIST;

class gLoginCore
{
public:
	static gLoginCore *GetIF();

	gLoginCore();
	virtual ~gLoginCore();

//public:
	//USER_LIST		m_UserList;

public:
	bool			SetUp();
	void			Release();

	// packet

	void			pk_login_ask(PK_DEFAULT *pk, SOCKET sock);

//	void			PrintUserList();

private:
	void			Put(char* id, char* pw);
	USER*			GetID(char* id);
};