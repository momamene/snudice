//------------------------------------------------------------------------------------
//	gServer.h
//
//	2010. 08. 04	CoderK	
//
//	server class
//------------------------------------------------------------------------------------
#pragma once
#include "networkconst.h"

class gServer
{
public:
	gServer();
	virtual ~gServer();
	
	static gServer	*GetIF();

public:
	bool		m_bConnect;				// ������ Connect�Ǿ���

public:
	bool		SetUp();
	void		Release();
	void		Send();
	void		Receive(LPARAM lParam);
	void		ReConnect();			// titlecore���� ������ ��û

private:
	void		EndSocket();
	bool		SocketErrorMessage(LPARAM lParam);	// error���� false

};