// nFlagCore의 의미 기억하니?
배틀넷 : 채널
룸조인 : 페이지
룸 : 방번호
서브밋 : 방번호
게임 : 방번호

// 9월 19일 (일) 오후 03시 이후의 이야기
(1) Draw 함수를 만들고 있었는데, m_hWnd가 엉망으로 말을 잘 안듣는 사실을 깨닫거나,
혹은 hWnd를 가지고 gPlayerContainer에서 hdc와 ps를 만들어도 잘 안된다는 사실을 깨달았다.
귀찮으니까 나중에 확인해 볼것


// 9월 21일 (화) 오전 03시의 이야기
// SendRoomRefreshCauseChange 를 만들었는데 잘 돌아갈까?

// 9월 22일 (수) 오후 10시 이후 야작의 이야기
// (1) 방장이 바뀌는데, ready한 녀석의 ready를 풀어야 하는 문제 : 해결
// (2) id가 없다는 이상한 문제 : 다시 켜니 해결
// (3) gamestart 패킷 : 임시방편으로 완성 

// (4) submitCore를 만들자!
// (5) subjectContainer는 비호환적인 시스템 (예컨대, 과목수를 서로 다른 define 값으로 결정) 을 가지고 있다.
// 최신버전으로 바꾸도록 하자.

 (6) RoomCore의 p.324 정도의 sangwoo temp, 부분을 좀 더 유연성 있게 변경할 필요가 있을 것 같다.
  그러려면, isAllReadyInRoom 의 정보가 바뀌어야 겠지.
  그러려면, player가 room의 정보를 통합해야 겟지.
  지난번에, player와 channel과의 관계가 문제가 되었었지.
  으으으으으으음...

// 9월 23일
// (1) 아니 load.xy가 없는데 잘 돌아갔단 말이야?
// (2) 수강취소 패킷을 처리
 중요! put과 push 는 연동되어야함.
 따라서, 호출할때는 **Subject를 호출해야 하며 ToPlayer는 호출하지 말것.
 m_submitSubject와 m_submitSubjectPlayer에서..
 괜히 이런 짓을 한걸까...
// (3) 수강완료 패킷을 처리 - 
// 수강완료되면 수강 신청은 불가능한 셈이군.
// (0) 엄청난 버그 - 남이 방을 만들었는데, 왜 뜨지 않는 걸까?
(4) 수강정원을 처리 
// (6) 6을 다른 define값으로 제안
// (5) 정말 중요한건데, ECM_ROOM 이 아니라 ECM_SUBMIT으로 바꿔야지!
(7) gRC->m_rooms[nRoomIndex].szRoomMaxPlayer[i][0] != '\0' 를 대체할만한 함수...

// 9월 24일
// (1) 클라이언트 - 맵
// (2) 서버 - pk_movestart_ask

// 9월 25일 (토)
// (1) gGPC에서 m_Round가 추가되면서...
// (2) Client Scroll을 원정갔다 왔다.
/*
(3)	  float		fAvGrade;
	  BYTE		bySubIdx[MAXSUBJECT];
	  int		nRank;
	  GAMEPLAYER class에서 추가..
*/
// (4) bool		m_isGamePlayer[MAXROOM][ROOMMAXPLAYER]; 를 사용하도록 하자!
// 초기 연동된 코드임을 기억할것!

/*
(5) client로 무언가 했다.
그 다음에 다시 client타일 원정을 갔다 온다.
수업이 아닌 타일
언어
언어 - 깜빡거릴떄 밝은 부분
언어 - 내가 신청한 거
수리
"
"
예술
"
"
*/ // 간신히 성공...

(6)
++
channel에 있던 애가 방만들면, 채널에 그 애가 남아있음

(7)
// 버스를 구현하자!
// . moveend 뒤에 isbSynAllTrue 안에서 무언가를 구현해야지. next로 넘어가는 통로
// pk_nextturn_rep 분리.
// pk_busmovechoose_rep 신설

(8)
// 녹두는 실패. -> 성공

 pk_busmoveselect_ask 에 녹두 관련 하드코딩이 존재 (// hard coding)


(9)
학점 정보가 바뀌면, 쏴주는 패킷이 따로 존재.
근데 이건 not syncronized packet임.

(10)
 학점을 구현중!
 - 1
// SubjectContainer를 만들고.
 - 2
// meetGrade 함수를 gameplayercontainer에서 구현하면 되네 ㅋㅋ

 - 3
 GradeRankSyncronizer()	
  이 함수의 존재로 인해, grade와 rank는 비동기화된 개념임.
  count만이 진정한 동기화된 개념.
  어떻게 동기화된 개념을 만들 수 있을것인가.

 // 여튼 gGamePlayerContainer의 기본적인 grade 관련 함수를 다 만드는데 성공!

- 4 
// 동기화는 중요. 동기화를 어떻게 이끌어 낼 것인가?
1> nPos는 client와 server 모두 다음 턴이지만, m_nTurn 이 갱신되지 않은 상황이
, moveend 패킷을 다 모았을 때이다.
이 때 정보 갱신, 정보를 보냄.
그 뒤, NextTurn 패킷을 보냄.

즉, 
 case 1 : moveend 이후, nextturn 이전

- 5
1> server : 10 9 , client : 15 11 player : test1 
2> 학점은 test1의 0,1 index가 다르고, test1도 이름이 test2로 뜬다.
// 3> 채널에 test11과 test12가 있었다. test12가 들어갔따. 그런데 test11은 test12가 있다고 본다.
// test13이 들어오면 비로서 test12의 부재를 파악한다.

(11) Stamina!
//1> staminaConvert (int nRoomIndex,int nInRoomIndex,int nPlusMinus) 만들기
//2> stamina를 수업 들을 때 깍기. 
// a: moveend에서만
//3> stamina를 녹두를 거닐 때 깍기. 
// a: moveend에서만
//4> stamina를 stamina를 거닐 때 올리기. 
// a:moveend에서만
//5> stamina의 처리는 movestart 대신 turnNext만 보낼것. (역시 정보 갱신된다는 점을 참고...)
// a:PK_MOVESTART_ASK 에서만
//6> 3-5 모든 경우에서 popinfo 연동. (2는 되었던 상태)
7> 6을 만족하면 popinfo 는 모두 연동 된 것일까?
8> bus 끝날 때 pk_gameplayerinfo_rep 함수를 준다면 모든 경우에서 pk_nextturn_rep를 할 때, 하는 셈이 되는데
그럴 꺼라면 그냥 pk_nextturn_rep 함수에 너면 되지 -_-
9> pk_popinfo_rep에 id가 결국 필요하지 않을까?
10> 미친, 근데 스태미너 안깍이잖아


// (12) 버스 자기 자신을 찍으면 왠지 0이 아니라 1로 처리하는 것 같은 에러
//[pk_moveend_ask] 심각한 Error, 보안 주의 요망, 서버와 클라이언트의 연산 결과가 다름
//server : 7 13 , client : 7 12 player : test2 room : 0
//		 이 방은 더 이상 동작하지 않습니다.

(13) 가끔씩 로그인이 안되는 에러

(14) 의구심 : 언어계열만 오르고 나머지는 오르지 않는다?
 학점이 안되더라도 계속해서 패킷은 쏴줘야지 ㅇ

 (15)
 <time.h>
 세번째 srand
 bool gGamePlayerContainer::SetUp()
{
	srand((unsigned)time(NULL));

(16) 버그 나면 다 쳐야해?
 방들어간거 알고 있는 ...

 
 (18)
 겹치는 하지만 서버에서는 겹치지 않는 버그

 // 10월 1일
 (1) 
  아이템...