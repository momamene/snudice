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