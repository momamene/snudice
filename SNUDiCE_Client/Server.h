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

private:
	PK_DEFAULT	m_pkDefault;
	

public:
	bool		SetUp();
	void		Release();
	bool		Send(DWORD type, DWORD size, void *buf);
	void		Receive(LPARAM lParam);		// ���� �޽������� error �ƴϸ� readpacket ȣ��
	void		ReConnect();				// titlecore���� ������ ��û

private:
	void		EndSocket();
	bool		SocketErrorMessage(LPARAM lParam);	// error���� false
	void		ReadPacket();				// packet ���� �� recv ȣ��
	void		Recv();

};