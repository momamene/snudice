//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//	gLoginCore.h
//
//	2010. 08. 08		CoderK
//
//	�α��� ��� ó��
//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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

public:
	USER_LIST		m_UserList;

public:
	bool			SetUp();
	void			Release();

	// packet

	void			pk_login_ask(PK_DEFAULT *pk, SOCKET sock);

//	void			PrintUserList();

};