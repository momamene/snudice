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
	bool		m_bConnect;				// 서버와 Connect되었냐

private:
	PK_DEFAULT	m_pkDefault;
	

public:
	bool		SetUp();
	void		Release();
	bool		Send(DWORD type, DWORD size, void *buf);
	void		Receive(LPARAM lParam);
	void		ReConnect();			// titlecore에서 재접속 요청

private:
	void		EndSocket();
	bool		SocketErrorMessage(LPARAM lParam);	// error나면 false

};