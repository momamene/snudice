#pragma once
#include "network.h"

//#define MAXROOMNUM	10


class gRoomCore
{
public:
	static gRoomCore *GetIF();

	bool			m_isRoom[MAXROOM]; // 방은 0-9 까지!
	ROOM			m_rooms[MAXROOM];


public:
	// start function
	bool			SetUp();
	void			Release();

	// packet function
	void			pk_roommaker_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_roomlist_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_roomjoin_ask(PK_DEFAULT *pk, SOCKET sock);
	void			ExitTheRoom (char* szID);
	void			SendRoomListCauseChange(int nPage);

private:
	int				FindFirstEmptyRoom ();
	int				FindTheRoom(char* szRoomName);
	bool			isFullRoom (int index);
	void			EnterTheRoom (int index,char* szID);
	void			DeleteTheRoom (int index);
	
	bool			isRoomInPage(int nPage);
	bool			ChangeMakerToFirstUser(int roomIndex);
	void			FindPlayersFromIDs_RMP(int roomIndex,PLAYER* getPlayerlist);
};