// nFlagCore�� �ǹ� ����ϴ�?
��Ʋ�� : ä��
������ : ������
�� : ���ȣ
����� : ���ȣ
���� : ���ȣ

// 9�� 19�� (��) ���� 03�� ������ �̾߱�
(1) Draw �Լ��� ����� �־��µ�, m_hWnd�� �������� ���� �� �ȵ�� ����� ���ݰų�,
Ȥ�� hWnd�� ������ gPlayerContainer���� hdc�� ps�� ���� �� �ȵȴٴ� ����� ���޾Ҵ�.
�������ϱ� ���߿� Ȯ���� ����


// 9�� 21�� (ȭ) ���� 03���� �̾߱�
// SendRoomRefreshCauseChange �� ������µ� �� ���ư���?

// 9�� 22�� (��) ���� 10�� ���� ������ �̾߱�
// (1) ������ �ٲ�µ�, ready�� �༮�� ready�� Ǯ��� �ϴ� ���� : �ذ�
// (2) id�� ���ٴ� �̻��� ���� : �ٽ� �Ѵ� �ذ�
// (3) gamestart ��Ŷ : �ӽù������� �ϼ� 

// (4) submitCore�� ������!
// (5) subjectContainer�� ��ȣȯ���� �ý��� (������, ������� ���� �ٸ� define ������ ����) �� ������ �ִ�.
// �ֽŹ������� �ٲٵ��� ����.

 (6) RoomCore�� p.324 ������ sangwoo temp, �κ��� �� �� ������ �ְ� ������ �ʿ䰡 ���� �� ����.
  �׷�����, isAllReadyInRoom �� ������ �ٲ��� ����.
  �׷�����, player�� room�� ������ �����ؾ� ����.
  ��������, player�� channel���� ���谡 ������ �Ǿ�����.
  ��������������...

// 9�� 23��
// (1) �ƴ� load.xy�� ���µ� �� ���ư��� ���̾�?
// (2) ������� ��Ŷ�� ó��
 �߿�! put�� push �� �����Ǿ����.
 ����, ȣ���Ҷ��� **Subject�� ȣ���ؾ� �ϸ� ToPlayer�� ȣ������ ����.
 m_submitSubject�� m_submitSubjectPlayer����..
 ���� �̷� ���� �Ѱɱ�...
// (3) �����Ϸ� ��Ŷ�� ó�� - 
// �����Ϸ�Ǹ� ���� ��û�� �Ұ����� ���̱�.
// (0) ��û�� ���� - ���� ���� ������µ�, �� ���� �ʴ� �ɱ�?
(4) ���������� ó�� 
// (6) 6�� �ٸ� define������ ����
// (5) ���� �߿��Ѱǵ�, ECM_ROOM �� �ƴ϶� ECM_SUBMIT���� �ٲ����!
(7) gRC->m_rooms[nRoomIndex].szRoomMaxPlayer[i][0] != '\0' �� ��ü�Ҹ��� �Լ�...

// 9�� 24��
// (1) Ŭ���̾�Ʈ - ��
// (2) ���� - pk_movestart_ask

// 9�� 25�� (��)
// (1) gGPC���� m_Round�� �߰��Ǹ鼭...
// (2) Client Scroll�� �������� �Դ�.
/*
(3)	  float		fAvGrade;
	  BYTE		bySubIdx[MAXSUBJECT];
	  int		nRank;
	  GAMEPLAYER class���� �߰�..
*/
// (4) bool		m_isGamePlayer[MAXROOM][ROOMMAXPLAYER]; �� ����ϵ��� ����!
// �ʱ� ������ �ڵ����� ����Ұ�!

/*
(5) client�� ���� �ߴ�.
�� ������ �ٽ� clientŸ�� ������ ���� �´�.
������ �ƴ� Ÿ��
���
��� - �����Ÿ��� ���� �κ�
��� - ���� ��û�� ��
����
"
"
����
"
"
*/ // ������ ����...

(6)
++
channel�� �ִ� �ְ� �游���, ä�ο� �� �ְ� ��������

(7)
// ������ ��������!
// . moveend �ڿ� isbSynAllTrue �ȿ��� ���𰡸� �����ؾ���. next�� �Ѿ�� ���
// pk_nextturn_rep �и�.
// pk_busmovechoose_rep �ż�

(8)
// ��δ� ����. -> ����

 pk_busmoveselect_ask �� ��� ���� �ϵ��ڵ��� ���� (// hard coding)


(9)
���� ������ �ٲ��, ���ִ� ��Ŷ�� ���� ����.
�ٵ� �̰� not syncronized packet��.

(10)
 ������ ������!
 - 1
// SubjectContainer�� �����.
 - 2
// meetGrade �Լ��� gameplayercontainer���� �����ϸ� �ǳ� ����

 - 3
 GradeRankSyncronizer()	
  �� �Լ��� ����� ����, grade�� rank�� �񵿱�ȭ�� ������.
  count���� ������ ����ȭ�� ����.
  ��� ����ȭ�� ������ ���� �� �������ΰ�.

 // ��ư gGamePlayerContainer�� �⺻���� grade ���� �Լ��� �� ����µ� ����!

- 4 
// ����ȭ�� �߿�. ����ȭ�� ��� �̲��� �� ���ΰ�?
1> nPos�� client�� server ��� ���� ��������, m_nTurn �� ���ŵ��� ���� ��Ȳ��
, moveend ��Ŷ�� �� ����� ���̴�.
�� �� ���� ����, ������ ����.
�� ��, NextTurn ��Ŷ�� ����.

��, 
 case 1 : moveend ����, nextturn ����

- 5
1> server : 10 9 , client : 15 11 player : test1 
2> ������ test1�� 0,1 index�� �ٸ���, test1�� �̸��� test2�� ���.
// 3> ä�ο� test11�� test12�� �־���. test12�� ����. �׷��� test11�� test12�� �ִٰ� ����.
// test13�� ������ ��μ� test12�� ���縦 �ľ��Ѵ�.

(11) Stamina!
//1> staminaConvert (int nRoomIndex,int nInRoomIndex,int nPlusMinus) �����
//2> stamina�� ���� ���� �� ���. 
// a: moveend������
//3> stamina�� ��θ� �Ŵ� �� ���. 
// a: moveend������
//4> stamina�� stamina�� �Ŵ� �� �ø���. 
// a:moveend������
//5> stamina�� ó���� movestart ��� turnNext�� ������. (���� ���� ���ŵȴٴ� ���� ����...)
// a:PK_MOVESTART_ASK ������
//6> 3-5 ��� ��쿡�� popinfo ����. (2�� �Ǿ��� ����)
7> 6�� �����ϸ� popinfo �� ��� ���� �� ���ϱ�?
8> bus ���� �� pk_gameplayerinfo_rep �Լ��� �شٸ� ��� ��쿡�� pk_nextturn_rep�� �� ��, �ϴ� ���� �Ǵµ�
�׷� ����� �׳� pk_nextturn_rep �Լ��� �ʸ� ���� -_-
9> pk_popinfo_rep�� id�� �ᱹ �ʿ����� ������?
10> ��ģ, �ٵ� ���¹̳� �ȱ����ݾ�


// (12) ���� �ڱ� �ڽ��� ������ ���� 0�� �ƴ϶� 1�� ó���ϴ� �� ���� ����
//[pk_moveend_ask] �ɰ��� Error, ���� ���� ���, ������ Ŭ���̾�Ʈ�� ���� ����� �ٸ�
//server : 7 13 , client : 7 12 player : test2 room : 0
//		 �� ���� �� �̻� �������� �ʽ��ϴ�.

(13) ������ �α����� �ȵǴ� ����

(14) �Ǳ��� : ���迭�� ������ �������� ������ �ʴ´�?
 ������ �ȵǴ��� ����ؼ� ��Ŷ�� ������� ��

 (15)
 <time.h>
 ����° srand
 bool gGamePlayerContainer::SetUp()
{
	srand((unsigned)time(NULL));

(16) ���� ���� �� �ľ���?
 ����� �˰� �ִ� ...

 
 (18)
 ��ġ�� ������ ���������� ��ġ�� �ʴ� ����

 // 10�� 1��
 (1) 
  ������... start �پ��� �͵��� �����ߴµ�.
  ������ ��������.. (�ּ� 10�� 5��)

(2) ����
// - ������ 3��° ĭ��...
// - �÷��̾�1�� �Ծ��µ�, �÷��̾�2�� ������...
// - �������� �ȸԾ���
// - ���¹̳ʰ� �� á�µ��� ����.

 // [10�� 5��]
  (1)
//	ITEM_STAT �迭�� ������ ����� �Ϸ�
//  ITEM_STAMINA �迭�� ������ ����� �Ϸ�

  (2) itemUse �� ����.
  bool ����, nextturn�� �����ϴ� �� ����.
  int �� �ٲ� ���ɼ�.
  ��, �������� bTemp���� �� �پ��ϰ� ������ �;��ϴ�...

  (3) 
// releaseItemGlobal �Լ�����, cooltime 100�� �Ѵ� ������ ���� �����Ѵ�.
//  m_ItemCoolTime������ 0~99 �� 0~800 �� ���� ���� ó���ϰ� �Ǿ���...

//  �̰���, cooltime2�� ����� �����Ƽ� ��ȵ� ��.
//  if(m_ItemCoolTime[nRoomIndex][i][j] > 100) {
//	  m_ItemCoolTime[nRoomIndex][i][j]--;
//	  if(m_ItemCoolTime[nRoomIndex][i][j]%100 == 0)
//		  m_ItemCoolTime[nRoomIndex][i][j] = 0;
 
// m_ItemCoolTime[MAXROOM][ROOMMAXPLAYER][ITEMNUM];
// �� Ÿ������ ��������,
// 100�������� flag�� ���Ǳ⵵ ��
// ������, 3��° ������ ��Ÿ�� 4�� 304 ������ �����
// releaseItemGlobal �Լ��� �����Ǵ� ����
   ���������� m_ItemCoolTimeSub �� ����� ���� ��õ
   �Ƹ�, ITEM_TOGETHERCLASS �� ITEM_CLASS �׸��� ITEM_MOVEPLACE �� 100�� ������ ����� ������ ����
	ITEM_MOVESELECT�� �� �𸣰���. 

  (4) ���� ����
  ���� ������ ��κ� itemUse �Լ����� �̷������ �ֽ��ϴ�.

//  (5) ITEM_TOGETHERCLASS ���� ��Ʈ�� �ϱ� ����, meetGrade �Լ��� �ϵ��ڵ��� ������.
//  �׷��� item_togetherclass ��� �Լ��� ��Ʈ�� �ϹǷ�, for�� ������ ���...
//  ����� �������� ����� �н� ���븦 ���� �л��� �н� ����� �����ϰ� �ص�.

  (6)
  �� 99�� ������ ������ �ǹ̷� ���
  (ITEM_NOCLASS������ ����)
  �������� (3) �������� ���� ����

  (7) ItemUse����...
  switch ���� (type�� ���� �����ϴ�..)
  �� ������������ ����.
  �� �ϵ��ڵ� ����.
  � if������ case TARGET_OTHER �� ������ �Ǿ� ����.

//  (8) ITEM_NOCLASS ����
//  meetGrade ���� �̷���� ����.! (meetGrade �� �߿��ϴ�)
//  ����!

   (9) GamePlayerContainer�� itemUse���� 
   gRC->FindPlayerIndexInTheRoom �κ��� �ϳ��� ������ ���� �ϴ� ���� ��õ

   (10) ITEM_MOVEPLACE �� �������Դϴ�.
   case�� ���� �ϴ� �� �����߽��ϴ�.
   PK_WARPSTART_ASK �� ����� �ֽ��ϴ�. �����߽��ϴ�.

   // [10�� 8��]
// (1) ������ ����ǵ�, full���� playing���� ������ �ʴ� ���� (���������� ����Ʈ�� ���� �ִ»���鿡��) ����

   (2) refactoring fail.
   1> CHARINFO class �� �и��� ���� �ǰ�
//  2> move ����� �и��� ���� �ǰ�
   3> m_cooltime ����, flag �κ��� ������ ���� �ǰ�
   

	//		[10�� 9��]
	//   (1) move ��� �и��� ���� - ����� ���غ�.

   (2) �Ϲ� ������ ���� ��Ģ�� ���� ����غ���.
	- ��ư �߰� �ɰ��� �ɷδ� �Ѱ谡 ���� �� ����.
	- int m_arr[30] ���ٴ� int30class m_cla �� �� ���ƺ����� �ʴ���?!

	(3) ������ LOGIN���� NOID ERROR�� �ߴµ�, ������ �ǰԵǴ� ��찡 �ִ�...
	=> ���� Ű�� ���� �ð��� ������ �׷� ������ ���� �� ������?


	//(4) clinet map ��� ���� �Ϸ�

----- ���⼭���� ���� ----- (10�� 24����) ������ ���� ���� �� ��Ÿ...

	[���� ����]
	network.h ����
	GamePlayerContianer.h �� State �ΰ�
	pk_itemuse_ask() �Ʒ� �� ����
	MainWin.cpp ask signal.
	movePlayer �� ����
	pk_moveend_ask() �� �����Ϸ��� ��, �̰Ŵ� ��ü �� ����. ����

	// [10�� 9��] (2) - item popinfoarr ����.. (�̰� Ŀ���� ������ ���ε� �ؼ�. ... �ؾ���;)
	network.h network������ ����. // (10�� 24��) �̰� â������ �ٲ۰Ŵ�. �ٵ� network.h �� ���� �ٲ������. ����	
	GamePlayerContainer.cpp ���� state�� ����. 

	[10�� 24��]	��� ���� item use ����.. �ϴܺ��� �Ͼ�� �ֽ��ϴ�.
	(1) pk_itemuse_ask() ���� ���� �ֽ��ϴ�.
	1> ���� : �׷��� pk_itemuse_ask ���� ITEMUSE_ERROR �� �ƴϸ� Send�� �����ش� ���̿���? 
	2> if(iuState == IUS_NONE) ���, �׳� success�� ������ �ž�, �׷��� ��Ŷ�� �� ������ ������...
	 �׷��� itemUse���� itemUse�� success�ߴٰ� ������ ��..
	3> iuState Ȯ��... 
	4> pk_warpstart_ask, pk_warpstart_rep, , pk_warpend_ask,  ���� �۾� ����
	... MainWin.cpp ���� �̹� ����� �� ���°� ���..
//	Ȥ���� �ߴ��ϰ� �ʹٸ�... �ּ� ó�� �ϰ� ���� �ִ� ���� �Լ� ���� �ּ�ó���ϸ� ���ư���.
	1�� �н�.
	5> �ɰ��� ���� :
	 ��� ó���� ��� �ؾ��� �� �𸣰ڴ�.
	 ��� . (1) movePlayer�� state�� bool ���� mPState = {move,bus,warp} �� ����
	 (2) warp �� ó���ϴ� �Լ��� ����.

    6> �̰� �ּ�ó�� �س���. pk_moveend_ask() ����..
	 PushbSynAllPlayer(nRoomIndex,false); 
	 �׸��� pk_busmoveselect_ask() �ּ�
	PushSynAllPlayer(nRoomIndex,false); �� �����ض�.
	 �׸��� ���� ���� �Լ����� 
	 PushbSynAllPlayer(nRoomIndex,false); �� �༮ �ּ� ó���� �س��.
	�ƴ� �ֳ��ϸ�, �̰� �⺻ ���� true��! /* */
	(�ٵ� �⺻ ���� false�� �Ǿ ��� �� �� ������ �ȵǾ� ���̱�� �Ѵ�.)
	����Ǵ� ���� : �� �ֻ����� �����µ�, �ȳѾ�ٴ���..
	����Ǵ� ����2 : ���� ����
	��ư ���� ������ �̰� �ٽ� �ּ� ���� �ǰڳ�. �ƴ� ���� ���ߴ�. ����

	7> ����!
	// pk_warplistend_rep, pk_warplistend_ask
    7-1>
	struct PK_WARPLISTEND_ASK �̳༮ �� id �߰� ��û

	�� ��ư �ϼ�!!
	�ٵ� ������� �Ϸ� ���� ��...


----- ���⼭���� ���� ----- (10�� 31����) ����� ��
(1) �����Ӱ� ����Ÿ� ����� �ֽ��ϴ�.
- MessageCore.cpp ���� �۾��� �ϰ� �ִµ�,
- debuger_move ��, debuger_card �� GamePlayerContainer.h �� �Űܰ� �� �մϴ�.

���� �ϼ�!
���� ����� �׷��� ����.

(2)
�ٲ� ��Ŷ��� �ٽ� ������ �����ϰ� �ֽ��ϴ�.
��Ŷ�� ��� �ʹ� �ٺ������� �ٲ�����Ƿ� ��� ���ɼ��� ����ؾ� �� ��.
/*
(1) ITEMUSE_ASK Series�� �� ITEMUSESTART_ASK �� ����

(3) ITEMUSE_ASK ITEMUSE_REP Series�� �����.

(2) INFOCHANGEEND_ASK �� �����.

(4) INFOCHANGE_REP �� �ڿ� Turn End�� �� INFOCHANGEEND_ASK �� �����.

�� �׳� �ٽ� �� ¥���ҵ�;;;

(5)	struct PK_WARPSTART_REP ���� ����!
*/

(3)
 0> notice
 MainWin ó���� ���� ���� �ȵ�����.
 ... ���� �ϰ� �־��µ� ...
 nInRoomIndex �� �ް��� ���ɼ��� �� ���ٰ� ���� ��...

 1> itemuse_ask -> itemuse_rep -> itemusestart_ask ... �ϴٰ�...

 m_struct_itemuse_ask �� ����...
 m_struct_itemuse_ask[nRoomIndex] = ask;	// �̰� �� �ǰ���?

 �� �ϴ� ���� �ϼ�

 

 2> itemusestart_sk ���� moveselect �κ�...

 !! ITEM_MOVEPLACE �� TARGE_OTHER �� �����Ǿ� ���� ����
 !! �Ƹ�, ��� ���� item case�� �ϵ� �ڵ��� ���ɼ�...

// putTargetTrue, putTargetInt ���� �� 
// ������ �̰��� other case �� �����ϴ� ��¥ �Լ�
 putTargetIntforOther �� ������ ����� ����...

 ���� �ϼ���
 
 5> ����... warplistend_rep �κп��� turnnext �ϴ� �κ�.
 �ϼ� �� �� ������?

 6> warpend_rep ���� turnnext ������ infochange_rep2 �ϴ� �κ�.
 �ϼ��߾�.

 3> itemusestart_ask �� infochange_rep (1) �κ�...
  ���� �ϼ���
 

 4> noclass, togetherclass ���� 
  �ϼ��� ��.

 7> ������ infochangeend_ask �Լ�
 �ϼ�!

 8> ������ �ܰ�
 gMainWin ó�� �ؾ���?
 �Լ��� �� �� �ְ�.


 ----- ���⼭���� ���� ----- (10�� 31����) ����
 (1) testset : 0�� ������
  �������� ���µ�, �� �ؽ�Ʈ�� �ƴϳ�.
  info�� �ȿ���.

  (1-1) ����1 : 
 �������� ���µ�, �� ���Ը� ���� �κ� itemuse_ask ����.. : �ذ�

	 [PK_ITEMUSE_ASK] 211.169.219.68	 itemIndex : test1 0 
	 a.b
	 [PK_ITEMUSESTART_ASK] 211.169.219.68	 test2 
	 a.b
	 [PK_ITEMUSESTART_ASK] 211.169.219.68	 test1 
	 itemUse(f) - nItemID : 0 type : ITEM_STAT
	 IUS_INFOCHANGEpk_infochangeItem_rep(f) 
	 a.b
	 [PK_INFOCHANGEEND_ASK] 211.169.219.68	 message : test1
	 [PK_WARPEND_ASK] 211.169.219.68	 test1 
	 [PK_WARPEND_ASK] 211.169.219.68	 test1 
	 [pk_warpend_ask] �ɰ��� Error, ���� ���� ���, ������ Ŭ���̾�Ʈ�� ���� ����� �ٸ�
server : 5 14 , client : -45210182 -2 player : test1 etc : 0 0
		 �� ���� �� �̻� �������� �ʽ��ϴ�.
		 a.b
		 [PK_INFOCHANGEEND_ASK] 211.169.219.68	 message : test2
		 [PK_WARPEND_ASK] 211.169.219.68	 test2 
		 [PK_WARPEND_ASK] 211.169.219.68	 test2 
		 [pk_warpend_ask] �ɰ��� Error, ���� ���� ���, ������ Ŭ���̾�Ʈ�� ���� ����� �ٸ�
server : 5 14 , client : 13 16 player : test2 etc : 0 0
		 �� ���� �� �̻� �������� �ʽ��ϴ�.


		p"stat�� multi�� ������� ����

------ �豳�� (11�� 2��) ----

��� : ������ ���� ����

	 1. ������ ��� -> �ٷ� ������� �ʴ´�.
//	 => ������ ����ϸ�, ������ PK_ITEMUSE_REP �� ���.
//	 �� ��鼭 PK_GAMEPLAYERINFO_REP �� �� ��.

	 2. debug ����
//	 => /card n,    ��ɾ��� ��� index n�� ī�尡 ���� �ʰ�, �������� �̻��ϰ� �´�.

//	 => ����� ��ɾ� ���� ��, �ش� turn�� �ƴ� ���� ������ ������ ��.
// �ذ�
/*
	 network.h
 struct GAMEPLAYER

	 ���� BYTE�� �Ǿ��ִ� ���� �ִ��͵� int�� �ٲ���.
	 �ֳ��ϸ� BYTE�� unsinged int ó�� ������ ���� ���������......
	 => �ϲ� �ҽ��� �� �ٲ����. �˰� ������ �ɵ�. ��ĥ �� ����.
*/

	 =========== �÷��̾� 2���� �� �׽�Ʈ ===========
	 card 00 - Ŀ��������
//	 PK_INFOCHANGE_REP ���� id���� ����, nLang�̷��͵��� 0���� �´�.
   -  �ӽù��� ���� : ��� ���̽��� �����ϰ� ����� �ƴϴ�!
   -  nMulti �� ���Ǵ� ��� TARGET_ME ������ ��ȿ�ϴ�!
   
   -  �ٺ��� ���� : �������� �ߺ� ����ϴ� ��츦 �������� �ʾҴ�.
   - ������, Ŀ�������۸� �� �� ����� �� ���µ�, �ɷ�ġ�� ���� �����Ǵ� ������ ���´�.

	pk_gameplayerinfo_rep ���� �н�. ����. ��ü�� �ɷ��� �����ۿ� ���� ���ŵ��� �ʴ´�.


	 card 03 - ���߿����� ���� å
	 card 04 - �߾ӵ�����
	 /*
	 PK_INFOCHANGE_REP�� �� ��.
	 �׷���, PK_INFOCHANGE_REP�� ����, PK_GAMEPLAYERINFO_REP�� ���� ����.
	�ذ�. pk_gameplayerinfo_rep�� �� �°� �ƴ϶�. ������ �Ⱥ����� �ִ� ��. ���� ����.
	 */
 

	 card 07 - ���ڶ� �츮 �ư�
	 ex) test1 ��  test2���� ���.
	 �׷���, PK_INFOCHANGE_REP ���� test2�� �;ߵǴµ�, test1, test2 �ٿ�.

	 card 08 - ������
	 ex) test1 ��  test2���� ���.
	 �׷���, PK_INFOCHANGE_REP ���� test2�� �;ߵǴµ�, test1, test2 �ٿ�.

	 card 12 - ���� ���� �Ұ���
	 card 14 - ��ī��
/*
	 PK_INFOCHANGE_REP�� ���� 0���� ��.
*/
/*
	 @ PK_INFOCHANGE_REP�� ȭ�鿡  + 3 �̷��� ����ִ� �� ���̴� ��.
	 @ ���� ���� ������ PK_GAMEPLAYERINFO_REP �� �̷����..

	 �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	 ���� �������ۿ� ������.....
	 �ذ��ϰ� ����ٶ�. Ŭ���̾�Ʈ �����ϼ���������, ������ �߸����� �ʾ�����
	 ������(�Ƹ� �ƴҵ�.. ����׷� ��� üũ�ϸ鼭 ������).
	 �ϰ� ������.

	 Ŭ���̾�Ʈ update�ް� �۾��Ұ�.
*/
	 card 17 -
	 ����. pk_itemuse_ask ���� rep�� corrupted �Ǿ��ٰ� �Ѵ�.
	 strcpy(rep.szTarget,ask.szTarget) �� �ּ�ó���ϸ�, server������ ��� �Ѿ�µ�,
	 client���� ������ ������.

	 card 18 - 
	 �� ��
	 card 19 -
	 ����.

//	 [����1] TARGET_OTHER ����
//	 => itemUse �κ�
//	 => pk_infochangeItem_rep
//	 [����2] ITEM_STAMINA case
	 [����3] ����뼺
	 [����4] �ߺ� ����� ����
	 (�� �� ������ ������ �ƴ�)