
/*
 nCoreFlag
 (1) BATTLENET������ nCoreFlag�� ä��
 ���� : nCoreFlag���� Player�� ������ �ξ� ���� ã�� �� ����.
 (2) ECM_ROOM ������ nCoreFlag�� ���ȣ
 (3) ECM_ROOMJOIN ������ nCoreFlag�� �� ����Ʈ�� ������

 09.16 3�� 10�� : ���� ū ������
 pk_roomlist_ask �� �� ���ư����� ������ �ϴ� ����
 ���� ��ó���� ���� ������ �����������.

 â�������� ������ �޼���
 â������ PK_ROOMJOIN_ASK �� szID[IDLENGHT] �� �ִٰ� ����������?
 nIdx �� 0-5 �ϱ�?

 09.17
 �ϴ� �ϼ�
 */

/*
SubjectContainer.cpp, h �߰�

roomlist �� �����, ����, �ƹ��͵� ���ٸ� �ñ�. // (��������?)

RoomCore 61���� ���� ; string�� NULL�� ���� ��� ���� ���ΰ�?
m_rooms[index].szRoomMaxPlayer[i][0] != '\0'
strlen() ���.
*/

// spacialService //
/*
1. ������ ���� ����� ������ ������ ��
 . refresh�� �ȵȴٴ� ��
2. �ٵ� �� �� ������ ���� �� �濡 �����ٴ� ��
3. �濡 ���� ���� ������ �ִٴ� ��
*/


// 9�� 19�� (��) �� 12���� ����
/*
1. (0)
- Bug fix

pk_roomrefresh_rep

-> ����� �� ��.





- change ; networkconst.h

2. (0) // loginCore.cpp (140) �� ������ �����ϸ� ��.
enum CLASSTYPE �߰�
{
	CLASS_NONE = -1, // ���þȵȰ�

	CLASS_LITERAL,  // �ι�
	....
}
-> �÷��̾��� ĳ���͸� ��Ÿ���� ����
struct PLAYER Ȯ��.
	-> ���ӿ� ���õ� ������ ������ �ϹǷ�.
	-> CLASSTYPE   classtype �߰�
	-> �̳��� ó���� ĳ���� ���� �ȵ� �����̹Ƿ� CLASS_NONE == -1 ��, 0�� �ƴ�

3. (0)
	ROOM ����ü
	-> ���� ���� ����.. ������ szRoomMaxPlayer[0] �� ����..
	�׷���, ������ �����ų� �׷��� sorting�� �ؼ� ���ο� ������ szRoomMaxPlayer[0]���� ������ ��.
	-¥�� ¥��...............-
	-> int  nMakerIndex �߰�. ��� ������ index �ذ�

	-> �������� �濡 �ִ� ���̵��� szID���� �����Ƿ�,
	�������� � ĳ���͸� ���� �̷��� �� �� ����.

	::

4. (0)
	PK_ROOMJOIN_REP
	PK_ROOMREFRESH_REP
	��׵鿡�ٰ� 
	PLAYER  playerlist[ROOMMAXPLAYER]  �߰�
	-> ������ �������� �޾ƿ�.

	�ϴ� szID[1] -> playerlist[1] �� �ٷ� ���� (sort ����, �� 0�� ���ٰ� �ؼ� playerlist[0]���� ������ ����)

	(1) char* [8] -> PLAYER[8] �� �ٲ�� �Լ��� ���� �� ������
 ����, pk_roomjoin_rep �� �ش� �ҽ��� �־���
 �ŰԴٰ�, mainwin.cpp �� userrelease�� �����ϴ�
 gRoomCore::ExitTheRoom ���� �ش� �ҽ��� �־��� (�� ����)

 // l_playerlist code (������ �Լ��� ����� ����..)
 �� ����

(2) ���, playerlist�� roomrefresh�� �����Ǵ� �������ٸ�, 
 �Լ��� ���� �� ����,
 ������, roomjoin���� ���� ������ �����ϹǷ�, (�� ���� ������ ����)
 �̴�� ����� �� �ۿ� ����.
 �ٵ� �� �������� �ڵ尡 ��.

(3) playerlist�� ����Ʈ�� �־... ��� �ϴ� �Լ��� â������ ����.
 �׸��� �װ��� ������ �Ͼ���ϴ�.
*/

// 9�� 19�� (��) ���� 03�� ������ �̾߱�
(1) Draw �Լ��� ����� �־��µ�, m_hWnd�� �������� ���� �� �ȵ�� ����� ���ݰų�,
Ȥ�� hWnd�� ������ gPlayerContainer���� hdc�� ps�� ���� �� �ȵȴٴ� ����� ���޾Ҵ�.
�������ϱ� ���߿� Ȯ���� ����

