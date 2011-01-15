#pragma once
#include "network.h"

//#define MAXROOMNUM	10


class gRoomCore
{
public:
	static gRoomCore *GetIF();

	bool			m_isRoom[MAXROOM]; // ���� 0-9 ����!
	ROOM			m_rooms[MAXROOM];

public:
	// start function
	bool			SetUp();
	void			Release();

	// packet function
	void			pk_roommaker_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_roomlist_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_roomjoin_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_roomback_ask(PK_DEFAULT *pk, SOCKET sock);	//��������
	void			pk_charselect_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_gameready_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_gamestart_ask(PK_DEFAULT *pk,SOCKET sock);

//

	void			ExitTheRoom (char* szID);

	void			SendRoomListCauseChange(int nPage);		// nPage�� �ִ� �ֵ鿡�� RoomList�� ����

	int				FindPlayerIndexInTheRoom(char* szID,int nRoomIndex);
	char*			FindPlayerszIDInTheRoom(int nInRoomIndex , int nRoomIndex);
	void			FindClasstypeFromIDs_RMP(int roomIndex,CLASSTYPE* classtype);

private:
	void			SendRoomRefreshCauseChange(int nRoomIndex);		// nRoomIndex�� �ִ� �ֵ鿡�� RoomInfo�� ����

	int				FindFirstEmptyRoom ();	
	int				FindTheRoom(char* szRoomName);
	
	bool			isFullRoom (int index);
	void			EnterTheRoom (int index,char* szID);
	void			DeleteTheRoom (int index);
	
	bool			isRoomInPage(int nPage);
	bool			ChangeMakerToFirstUser(int roomIndex);
	void			FindPlayersFromIDs_RMP(int roomIndex,PLAYER* getPlayerlist);
};


