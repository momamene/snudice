//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//	gServer.h
//
//	2010. 08. 04		CoderK
//
//	게임 서버(일단은 배틀넷)
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
#pragma once
#include <winsock2.h>
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
	bool		SetUp(int argc, char *argv[]);
	void		Run();
	void		Release();
};

