//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//	gPlayerContainer.h
//
//	2010. 08. 10		CoderK
//
//	�α��ε� �÷��̾���� ������ ��� ����
//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
#include "network.h"
#include <list>


using namespace std;

typedef list<PLAYER*> PLAYER_LIST;

class gPlayerContainer
{
public:
	static gPlayerContainer *GetIF();

	gPlayerContainer();
	virtual ~gPlayerContainer();

public:
	PLAYER_LIST		m_PlayerList;

public:
	void			AddPlayer(PLAYER* player);
	bool			DeletePlayer(SOCKET sock, char getClientID[IDLENGTH]);	// socket�� �ָ�, ���̵� �����, clientID�� �����ϴ� �Լ�
	bool			SetUp();					// clientID
	void			Release();

	bool			PutMode(char* id, eCOREMODE mode);
	bool			PutCoreFlag(char* id, int flag);
	void			PutModeToModeForAll(eCOREMODE befMode, int flag, eCOREMODE newMode);
	bool			PutClassType(char*id, CLASSTYPE classtype);
	bool			PutBoolReady (char* id,bool bReady);
	eCOREMODE		GetMode(char* id);
	int				GetCoreFlag(char* id);
	CLASSTYPE		GetClassType (char* id);

	bool			isClasstypeExistedInRoom(int flag,CLASSTYPE clsstype);
	bool			isAllReadyInRoom(int nRoomIndex);

	// packet

//	void			pk_login_ask(PK_DEFAULT *pk, SOCKET sock);
	
	void			pk_friendadd_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_frienddelete_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_getplayerinfo_ask(PK_DEFAULT *pk, SOCKET sock);
	
	bool			isExistedPlayer(char* id);
	bool			FindSocketFromID(char* id, SOCKET* getSock);

	void			SendSelect (ePROTOCOL prot,int pkSize,void *pk,eCOREMODE mode,int nPage);	// Player �߿��� nPage�� ����� ������� Send�ϴ� Ư���Լ�.
	
	//PLAYER[ROOMMAXPLAYER] GetPlayersFromIDs_RMP(char* szID[ROOMMAXPLAYER]);
	PLAYER			GetPlayerFromID(char* szID);	// return ���� [8(RMP)]�� �迭
	PLAYER			GetPlayerFromSocket(SOCKET sock);
	
	
	void			Draw(HDC hdc);

	//	void			PrintUserList();

};