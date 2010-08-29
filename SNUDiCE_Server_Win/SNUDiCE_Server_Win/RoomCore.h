#pragma once
#include "network.h"

#define MAXROOMNUM	10


class gRoomCore
{
public:
	static gRoomCore *GetIF();

	bool			m_isRoom[MAXROOMNUM]; // ���� 0-9 ����!
	ROOM			m_rooms[MAXROOMNUM];


public:
	// start function
	bool			SetUp();
	void			Release();

	// packet function
	void			pk_roommaker_ask(PK_DEFAULT *pk, SOCKET sock);
	void			ExitTheRoom (char* szID);

private:
	int				FindFirstEmptyRoom ();
	int				FindTheRoom(char* szRoomName);
	bool			isFullRoom (int index);
	void			EnterTheRoom (int index,char* szID);
	void			DeleteTheRoom (int index);
	

};