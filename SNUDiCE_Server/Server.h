//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//	gServer.h
//
//	2010. 08. 04		CoderK
//
//	게임 서버(일단은 배틀넷)
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
#pragma once
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "network.h"

class gServer  
{
public:
	static gServer		*GetIF();

	gServer();
	virtual ~gServer();

public:
	SOCKET		m_listen_sock;

public:
	bool		Send(DWORD type, DWORD size, void *buf, SOCKET sock);
	void		Recv(PK_DEFAULT *pk, SOCKET	sock);
	bool		SetUp();
	void		Run();
	void		Release();
};

