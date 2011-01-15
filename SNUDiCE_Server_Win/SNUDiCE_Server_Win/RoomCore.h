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
	void			pk_roomback_ask(PK_DEFAULT *pk, SOCKET sock);	//수정사항
	void			pk_charselect_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_gameready_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_gamestart_ask(PK_DEFAULT *pk,SOCKET sock);

//

	void			ExitTheRoom (char* szID);

	void			SendRoomListCauseChange(int nPage);		// nPage에 있는 애들에게 RoomList를 갱신

	int				FindPlayerIndexInTheRoom(char* szID,int nRoomIndex);
	char*			FindPlayerszIDInTheRoom(int nInRoomIndex , int nRoomIndex);
	void			FindClasstypeFromIDs_RMP(int roomIndex,CLASSTYPE* classtype);

private:
	void			SendRoomRefreshCauseChange(int nRoomIndex);		// nRoomIndex에 있는 애들에게 RoomInfo를 갱신

	int				FindFirstEmptyRoom ();	
	int				FindTheRoom(char* szRoomName);
	
	bool			isFullRoom (int index);
	void			EnterTheRoom (int index,char* szID);
	void			DeleteTheRoom (int index);
	
	bool			isRoomInPage(int nPage);
	bool			ChangeMakerToFirstUser(int roomIndex);
	void			FindPlayersFromIDs_RMP(int roomIndex,PLAYER* getPlayerlist);
};


