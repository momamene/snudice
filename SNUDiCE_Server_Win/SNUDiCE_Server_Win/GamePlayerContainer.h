#pragma once
#include "network.h"

class gGamePlayerContainer
{
public:
	static gGamePlayerContainer *GetIF();

	CHARINFO	m_CharInfo[CLASS_END];

	GAMEPLAYER	m_GamePlayer[MAXROOM][ROOMMAXPLAYER];
	bool		m_isGamePlayer[MAXROOM][ROOMMAXPLAYER];		
	// ���� �ذ� ȣȯ��Ű�� �ʴ�...
	// �׷��� �� ���� �� �ִ� �Ŵ� ȣȯ��Ű���� ����.
	bool		m_isNokdu[MAXROOM][ROOMMAXPLAYER];
	int			m_nTurn[MAXROOM];
	int			m_nRound[MAXROOM];						
	

	bool		m_bSyncronize[MAXROOM][ROOMMAXPLAYER];

	void		pk_maingamestart_rep(int nRoomIndex);
	void		pk_movestart_ask(PK_DEFAULT *pk,SOCKET sock);
	void		pk_moveend_ask(PK_DEFAULT *pk,SOCKET sock);
	void		pk_nextturn_rep(int nRoomIndex);
	void		pk_busmovechoose_rep(int nRoomIndex,char* szID);
	void		pk_busmoveselect_ask(PK_DEFAULT *pk,SOCKET sock);
	void		pk_busmoveend_ask(PK_DEFAULT *pk,SOCKET sock);

	bool		SetUp();
	bool		init(int nRoomIndex);
	void		Release();

private:
	void		FirstTurn(int nRoomIndex);
	void		NextTurn(int nRoomIndex);

	void		PushbSynAllPlayer(int nRoomIndex,bool bSyn);
	bool		isbSynAllTrue(int nRoomIndex);

};