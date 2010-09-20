
/*
 nCoreFlag
 (1) BATTLENET에서는 nCoreFlag는 채널
 권장 : nCoreFlag값이 Player에 있으면 훨씬 쉽게 찾을 수 있음.
 (2) ECM_ROOM 에서는 nCoreFlag는 방번호
 (3) ECM_ROOMJOIN 에서는 nCoreFlag는 방 리스트의 페이지

 09.16 3시 10분 : 가장 큰 문제는
 pk_roomlist_ask 가 잘 돌아가느냐 마느냐 하는 문제
 지금 어처구니 없는 연결을 만들었을지도.

 창규형에게 보내는 메세지
 창규형은 PK_ROOMJOIN_ASK 에 szID[IDLENGHT] 가 있다고 가정했을까?
 nIdx 는 0-5 일까?

 09.17
 일단 완성
 */

/*
SubjectContainer.cpp, h 추가

roomlist 를 물어볼때, 만약, 아무것도 없다면 씹기. // (괜찮을까?)

RoomCore 61줄의 문제 ; string이 NULL인 것을 어떻게 평가할 것인가?
m_rooms[index].szRoomMaxPlayer[i][0] != '\0'
strlen() 방법.
*/

// spacialService //
/*
1. 문제는 방을 만들다 누군가 나갔을 때
 . refresh가 안된다는 거
2. 근데 그 때 누군가 들어가면 그 방에 들어가진다는 거
3. 방에 들어가도 방은 지워져 있다는 거
*/


// 9월 19일 (일) 낮 12시의 문제
/*
1. (0)
- Bug fix

pk_roomrefresh_rep

-> 제대로 안 옴.





- change ; networkconst.h

2. (0) // loginCore.cpp (140) 의 정보만 수정하면 됨.
enum CLASSTYPE 추가
{
	CLASS_NONE = -1, // 선택안된거

	CLASS_LITERAL,  // 인문
	....
}
-> 플레이어의 캐릭터를 나타내는 정보
struct PLAYER 확장.
	-> 게임에 관련된 정보도 가져야 하므로.
	-> CLASSTYPE   classtype 추가
	-> 이넘은 처음에 캐릭터 선택 안된 상태이므로 CLASS_NONE == -1 임, 0이 아님

3. (0)
	ROOM 구조체
	-> 방장 관련 문제.. 지금은 szRoomMaxPlayer[0] 이 방장..
	그러나, 방장이 나가거나 그러면 sorting을 해서 새로운 방장을 szRoomMaxPlayer[0]으로 보내야 함.
	-짜증 짜증...............-
	-> int  nMakerIndex 추가. 얘로 방장의 index 해결

	-> 기존에는 방에 있는 아이들의 szID값만 가지므로,
	누군가가 어떤 캐릭터를 고르고 이런걸 알 수 없음.

	::

4. (0)
	PK_ROOMJOIN_REP
	PK_ROOMREFRESH_REP
	얘네들에다가 
	PLAYER  playerlist[ROOMMAXPLAYER]  추가
	-> 유저의 정보까지 받아옴.

	일단 szID[1] -> playerlist[1] 로 바로 매핑 (sort 없음, 즉 0이 없다고 해서 playerlist[0]으로 들어가지는 않음)

	(1) char* [8] -> PLAYER[8] 로 바뀌는 함수를 만들 수 없었음
 따라서, pk_roomjoin_rep 에 해당 소스를 넣었음
 거게다가, mainwin.cpp 의 userrelease가 참조하는
 gRoomCore::ExitTheRoom 에도 해당 소스를 넣었음 (을 예정)

 // l_playerlist code (정말로 함수로 만들고 싶은..)
 을 참조

(2) 사실, playerlist가 roomrefresh에 한정되는 문제였다면, 
 함수를 만들 수 있음,
 하지만, roomjoin에도 같은 문제가 존재하므로, (더 많은 변수가 존재)
 이대로 사용할 수 밖에 없음.
 근데 꽤 너지분한 코드가 됨.

(3) playerlist를 포인트로 넣어서... 어떻게 하는 함수를 창규형이 제안.
 그리고 그것이 실제로 일어났습니다.
*/

// 9월 19일 (일) 오후 03시 이후의 이야기
(1) Draw 함수를 만들고 있었는데, m_hWnd가 엉망으로 말을 잘 안듣는 사실을 깨닫거나,
혹은 hWnd를 가지고 gPlayerContainer에서 hdc와 ps를 만들어도 잘 안된다는 사실을 깨달았다.
귀찮으니까 나중에 확인해 볼것

