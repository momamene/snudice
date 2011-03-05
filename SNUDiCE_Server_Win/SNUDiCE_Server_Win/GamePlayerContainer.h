#pragma once
#include "network.h"
#include "Charinfo.h"

#include <vector>

#define MINIMUM_COUPLE_CONDITION 10
#define SAMECLASS_FAVORPOINT 5
#define SAMETILE_FAVORPOINT 5
#define CROSS_FAVORPOINT 2

#define LOVEINITPOINT 3

#define RANDSTANDITEMGET

using namespace std;
enum ItemUseState {
	IUS_NONE,
	IUS_NEXTTURN,
	IUS_INFOCHANGE,
	IUS_INVALIDSTATE,
};

enum MovePlayerState {
	MPS_MOVE,
	MPS_BUS,
	MPS_WARP,
};

enum CoupleState {
	CPS_NONE = -1,
	CPS_REJECT,
	CPS_ACCEPT,

	CPS_PROPOSE,
};


enum GAMESTATE {	//	�� ���¿��� ������ �x
	GS_COUPLESTAND = -2,
	GS_STAND ,
	
	GS_BUS,
	GS_WARP,
	GS_WARPLIST,
	GS_WALK,

	GS_COUPLEBUS,
	GS_COUPLEWALK,

//	GS_DICE,	//���������� GS_WALK�� �ľ� �Ұ� 
	GS_RESULT,
	
	GS_COUPLEASK,
};


//����, ȣ��������ü
struct sFavor 
{
//	char *playerid[ROOMMAXPLAYER];	// �뷫 �ʿ� ������; RoomCore�� FindPlayerIndexInTheRoom�� �̿��Ѵ�.
	int		point[ROOMMAXPLAYER];	// -1 : Ŀ�û��� , �� ȣ������ �������� ������
	int		lvTargetIndex;	//����� �޴� ���
	CoupleState		bYes;			//��Ѽ�������	//	0,1 : Ŀ�ü�������/�������� , -1 : �׷��ž�����.
};


class gGamePlayerContainer
{
public:
	static gGamePlayerContainer *GetIF();

	//CHARINFO	m_CharInfo[CLASS_END];
	gCharinfo	m_CharInfo;

	GAMEPLAYER	m_GamePlayer[MAXROOM][ROOMMAXPLAYER];
	bool		m_isGamePlayer[MAXROOM][ROOMMAXPLAYER];
	GAMESTATE	m_GameState[MAXROOM][ROOMMAXPLAYER];
	
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
	
	vector< pair<int,int> > m_userItemList[MAXROOM][ROOMMAXPLAYER];	//		<Item num  , coolTime>
	
	//����		��������!~
//	int			m_ItemCoolTime[MAXROOM][ROOMMAXPLAYER][ITEMNUM];
	
	// �� Ÿ������ ��������,
	// 100�������� flag�� ���Ǳ⵵ ��
	// ������, 3��° ������ ��Ÿ�� 4�� 304 ������ �����
	// releaseItemGlobal �Լ��� �����Ǵ� ����
	// ���������� m_ItemCoolTimeSub �� ����� ���� ��õ
	

	bool		m_bSyncronize[MAXROOM][ROOMMAXPLAYER];	
	// �ֻ��� ���� ��, ������ ���� ��� Ŭ���̾�Ʈ�� ���� �������� �ϴ� ���,
	// m_bSyncornize ������ false�� �ٲ� ��, Ŭ���̾�Ʈ�� �Ϸ��ϴ� ��� true�� �ٲ۴�.
	// ���� user�� ���� ���� ��� �׻� true, �ƴϸ� false.

//	bool				m_bCoupleSync[MAXROOM];	//����, Ŀ�ÿ� ����ȭ�۾��Ҷ� ����.
	
	PK_ITEMUSE_ASK m_struct_itemuse_ask[MAXROOM];
	// pk_itemuse_ask -> pk_itemuse_rep -> pk_itemusestart_ask �� ���� �������� �ӽ� ����Ǵ� ��Ŷ.


	sFavor m_favor[MAXROOM][ROOMMAXPLAYER];
	//ȣ����

	void		setState(GAMESTATE eState, char *szID);

	void		PushbSynAllPlayer(int nRoomIndex,bool bSyn);
	bool		isbSynAllTrue(int nRoomIndex);


	void		pk_maingamestart_rep(int nRoomIndex);
	void		pk_movestart_ask(PK_DEFAULT *pk,SOCKET sock);
	
	void		pk_movestart_rep(int nRoomIndex , int nInRoomIndex , PK_MOVESTART_REP rep );	// debuger_move�� ����;;;;
	
	void		pk_moveend_ask(PK_DEFAULT *pk,SOCKET sock);
	bool		pk_nextturn_rep(int nRoomIndex);
	void		pk_busmovechoose_rep(int nRoomIndex,char* szID);
	void		pk_busmoveselect_ask(PK_DEFAULT *pk,SOCKET sock);
	void		pk_busmoveend_ask(PK_DEFAULT *pk,SOCKET sock);
	void		pk_gameplayerinfo_rep (int nRoomIndex);
	void		pk_subGameplayerinfo_rep(int nRoomIndex,PK_GAMEPLAYERINFO_REP* rep);

	void		pk_gameend_rep(int nRoomIndex);

	void		pk_itemuse_ask(PK_DEFAULT *pk,SOCKET sock);

	void		pk_exit_ask(char*, SOCKET sock);//��������, �Ώ椻��
	void		pk_gologin_ask(PK_DEFAULT *pk,SOCKET sock);	

	//	void		pk_warpstart_ask (PK_DEFAULT *pk, SOCKET sock);
	void		pk_warpstart_rep (int nRoomIndex, int nInRoomIndex, int des);
	void		pk_warpend_ask (PK_DEFAULT *pk, SOCKET sock);
	void		pk_warpliststart_rep (int nRoomIndex, bool* bInRoomIndex, int* des);
	void		pk_warplistend_ask (PK_DEFAULT *pk, SOCKET sock);

	void		pk_itemusestart_ask(PK_DEFAULT *pk,SOCKET sock);
	void		pk_infochangeItem_rep(PK_ITEMUSE_ASK ask);								//item���� ��ġ����
	void		pk_infochangeTile_rep(int nRoomIndex, int nInRoomIndex , int stamina,int accomplishment , int coupleIndex = -1);	// coupleIndex�� -1�̸� �ѻ��, -1�� �ƴϸ� Ŀ���ε�����
	void		pk_infochangeend_ask(PK_DEFAULT *pk, SOCKET sock);


	void		pk_anscouple_ask(PK_DEFAULT *pk , SOCKET sock);
	void		pk_becoupleend_ask(PK_DEFAULT *pk , SOCKET sock );

	void		pk_askcouple_rep( int nRoomIndex , int playerIndex_a, int playerIndex_b);	//	 a, b : �÷��̾��� �ε�����	
	void		pk_becouple_rep (int nRoomIndex , PLAYER player_a , PLAYER player_b , bool bCouple , bool isBothBreak = false);

	bool		SetUp();
	bool		init(int nRoomIndex);
	void		Release();

	void				majorCount(int nRoomIndex);
	void				gameplayCount(int nRoomIndex);

	void				debuger_move(int nDis,char* szID);
	void				debuger_card(int nIndex,char* szID);
	void				debuger_turn(char* szID);

private:
	PK_BECOUPLE_REP		temp_becouple_rep;	//���� �ϵ��ڵ� ���� // Ŀ�ü���ɶ� warpend ��ٸ������� ��� ��....
	int					isWhoCouple;		//Ŀ�ü���ī��Ʈ
	
	int					delLovePoint[MAXROOM];
	int					m_rmWalk[MAXROOM];	//remain walk
	
	void				FirstTurn(int nRoomIndex);
	void				NextTurn(int nRoomIndex);

	int					meetGrade(int nRoomIndex,int subjectIndex ,int nInRoomIndex);  // subjectIndex = flag1
	int					meetItemCalculator(int nRoomIndex,int nInRoomIndex,int classType,int originalVal);
	void				GradeRankSyncronizer(int nRoomIndex);
	int					Rank(int nRoomIndex,int nInRoomIndex);

	int					staminaConvert(int nRoomIndex,int nInRoomIndex,int nPlusMinus);
	int					WhoIsRankOne(int nRoomIndex);
	void				pk_getItem_rep(int nRoomIndex, int nInRoomIndex,int nItemID = -1);
	void				pushItem(int nRoomIndex, int nInRoomIndex,int nItemID);
	void				releaseItemGlobal(int nRoomIndex);
	ItemUseState		itemUse (PK_ITEMUSE_ASK ask, int nRoomIndex, int nInRoomIndex, int itemIndex);
	// nInRoomIndex�� �������� ����� ����, itemIndex�� 0-19 ������ ���״����...
	// bool ����, nextturn�� �����ϴ� �� ����.
	// int �� �ٲ� ���ɼ�.

	void				movePlayer(int nRoomIndex,int nInRoomIndex,int des,MovePlayerState mpState);
	bool				isNokduFromPosByHardCoded(int nPos);

	// void		putTargetTrueForOther(int nRoomIndex,int nInRoomIndex, bool* getBarrInRoomIndex,ITEMTARGET target); 
	void		putTargetIntForOther(int nRoomIndex,int nInRoomIndex, int* getNarrDes,ITEMTARGET target,int nVal);
	// �� �Լ��� other�� ���� �۵��ϴ� ��¥ �Լ��̴�.

	int				putFavorCross(int nRoomIndex, int nInRoomIndex, int newDist , int nextDist);	//�ʱ길 ���ĵ� �ο�
			// ���ϰ� : �������� ��ѽ�û�̸� �� ��ġ ����
	bool				favorUpFunc ( int nRoomIndex , int playerIndex_a, int playerIndex_b , int upPoint = CROSS_FAVORPOINT);	//	 a, b : �÷��̾��� �ε�����	
			// ���ϰ� : �������� ���� �� Ŀ�ý�û�̸� true

	void				TileProcess(int nRoomIndex, int nInRoomIndex , int nDestPos);

};
