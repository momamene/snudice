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

public:
	bool		SetUp();
	void		Release();
	void		Send();
	void		Receive(LPARAM lParam);
	void		ReConnect();			// titlecore에서 재접속 요청

private:
	void		EndSocket();
	bool		SocketErrorMessage(LPARAM lParam);	// error나면 false

};