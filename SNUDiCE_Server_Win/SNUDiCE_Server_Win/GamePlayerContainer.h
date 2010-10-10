#pragma once
#include "network.h"
#include "Charinfo.h"

class gGamePlayerContainer
{
public:
	static gGamePlayerContainer *GetIF();

	//CHARINFO	m_CharInfo[CLASS_END];
	gCharinfo	m_CharInfo;

	GAMEPLAYER	m_GamePlayer[MAXROOM][ROOMMAXPLAYER];
	bool		m_isGamePlayer[MAXROOM][ROOMMAXPLAYER];		
	// ���� �ذ� ȣȯ��Ű�� �ʴ�...
	// �׷��� �� ���� �� �ִ� �Ŵ� ȣȯ��Ű���� ����.
	// (�Ƴ� �̰� �� ���Ǵ� ����)

	bool		m_isNokdu[MAXROOM][ROOMMAXPLAYER];
	// �� �÷��̾�� ��ο� �ִ°�?

	int			m_nTurn[MAXROOM];
	int			m_nRound[MAXROOM];	

	int			m_nSubjectCount[MAXROOM][ROOMMAXPLAYER][MAXSUBJECT];
	// ���� ���� ���뵵
	// �⺻������ �ɷ� * 20 ��ŭ �����Ѵ�.
	// grade�� subjectContainer���� Ȯ���� �� �ִ�.
	
	int			m_ItemCoolTime[MAXROOM][ROOMMAXPLAYER][ITEMNUM];
	// �� Ÿ������ ��������,
	// 100�������� flag�� ���Ǳ⵵ ��
	// ������, 3��° ������ ��Ÿ�� 4�� 304 ������ �����
	// releaseItemGlobal �Լ��� �����Ǵ� ����
	// ���������� m_ItemCoolTimeSub �� ����� ���� ��õ

	bool		m_bSyncronize[MAXROOM][ROOMMAXPLAYER];	
	// �ֻ��� ���� ��, ������ ���� ��� Ŭ���̾�Ʈ�� ���� �������� �ϴ� ���,
	// m_bSyncornize ������ false�� �ٲ� ��, Ŭ���̾�Ʈ�� �Ϸ��ϴ� ��� true�� �ٲ۴�.
	// ���� user�� ���� ���� ��� �׻� true, �ƴϸ� false.

	void		pk_maingamestart_rep(int nRoomIndex);
	void		pk_movestart_ask(PK_DEFAULT *pk,SOCKET sock);
	void		pk_moveend_ask(PK_DEFAULT *pk,SOCKET sock);
	void		pk_nextturn_rep(int nRoomIndex);
	void		pk_busmovechoose_rep(int nRoomIndex,char* szID);
	void		pk_busmoveselect_ask(PK_DEFAULT *pk,SOCKET sock);
	void		pk_busmoveend_ask(PK_DEFAULT *pk,SOCKET sock);
	void		pk_gameplayerinfo_rep (int nRoomIndex);
	void		pk_subGameplayerinfo_rep(int nRoomIndex,PK_GAMEPLAYERINFO_REP* rep);
	void		pk_popinfo_rep(int nRoomIndex,int stamina,int accomplishment);

	void		pk_gameend_rep(int nRoomIndex);

	void		pk_itemuse_ask(PK_DEFAULT *pk,SOCKET sock);

	bool		SetUp();
	bool		init(int nRoomIndex);
	void		Release();

private:
	void		FirstTurn(int nRoomIndex);
	void		NextTurn(int nRoomIndex);

	void		PushbSynAllPlayer(int nRoomIndex,bool bSyn);
	bool		isbSynAllTrue(int nRoomIndex);

	int			meetGrade(int nRoomIndex,int subjectIndex);  // subjectIndex = flag1
	int			meetItemCalculator(int nRoomIndex,int nInRoomIndex,int classType,int originalVal);
	void		GradeRankSyncronizer(int nRoomIndex);
	int			Rank(int nRoomIndex,int nInRoomIndex);

	int			staminaConvert(int nRoomIndex,int nInRoomIndex,int nPlusMinus);
	int			WhoIsRankOne(int nRoomIndex);
	void		getItem(int nRoomIndex, int nInRoomIndex);
	void		pushItem(int nRoomIndex, int nInRoomIndex,int nItemID);
	void		releaseItemGlobal(int nRoomIndex);
	bool		itemUse (PK_ITEMUSE_ASK ask, int nRoomIndex, int nInRoomIndex, int itemIndex);
	// nInRoomIndex�� �������� ����� ����, itemIndex�� 0-19 ������ ���״����...
	// bool ����, nextturn�� �����ϴ� �� ����.
	// int �� �ٲ� ���ɼ�.

	void		movePlayer(int nRoomIndex,int nInRoomIndex,int des,bool bIsBus = false);
	
};