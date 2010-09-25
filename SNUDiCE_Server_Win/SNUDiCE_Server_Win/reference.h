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
(5) subjectContainer는 비호환적인 시스템 (예컨대, 과목수를 서로 다른 define 값으로 결정) 을 가지고 있다.
 최신버전으로 바꾸도록 하자.

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