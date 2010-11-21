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
  아이템... start 다양한 것들을 구현했는데.
  이제는 오리무중.. (주석 10월 5일)

(2) 버그
// - 아이템 3번째 칸에...
// - 플레이어1이 먹었는데, 플레이어2가 가지고...
// - 아이템이 안먹어짐
// - 스태미너가 다 찼는데도 오름.

 // [10월 5일]
  (1)
//	ITEM_STAT 계열의 아이템 사용을 완료
//  ITEM_STAMINA 계열의 아이템 사용을 완료

  (2) itemUse 의 난점.
  bool 값은, nextturn을 시전하는 지 여부.
  int 로 바뀔 가능성.
  즉, 통제권을 bTemp에서 더 다양하게 가지고 싶어하는...

  (3) 
// releaseItemGlobal 함수에서, cooltime 100이 넘는 값들을 따로 관리한다.
//  m_ItemCoolTime에서는 0~99 와 0~800 의 값을 따로 처리하게 되었다...

//  이것은, cooltime2를 만들기 귀찮아서 고안된 것.
//  if(m_ItemCoolTime[nRoomIndex][i][j] > 100) {
//	  m_ItemCoolTime[nRoomIndex][i][j]--;
//	  if(m_ItemCoolTime[nRoomIndex][i][j]%100 == 0)
//		  m_ItemCoolTime[nRoomIndex][i][j] = 0;
 
// m_ItemCoolTime[MAXROOM][ROOMMAXPLAYER][ITEMNUM];
// 쿨 타임으로 사용되지만,
// 100단위에서 flag로 사용되기도 함
// 예컨대, 3번째 유저의 쿨타임 4는 304 값으로 저장됨
// releaseItemGlobal 함수와 연동되니 참고
   개인적으로 m_ItemCoolTimeSub 를 만드는 것을 추천
   아마, ITEM_TOGETHERCLASS 와 ITEM_CLASS 그리고 ITEM_MOVEPLACE 가 100대 단위를 사용할 것으로 추정
	ITEM_MOVESELECT는 잘 모르겠음. 

  (4) 진행 보고
  현재 진행은 대부분 itemUse 함수에서 이루어지고 있습니다.

//  (5) ITEM_TOGETHERCLASS 쪽을 컨트롤 하기 위해, meetGrade 함수에 하드코딩을 진행중.
//  그래도 item_togetherclass 모든 함수를 컨트롤 하므로, for문 정도는 사용...
//  현재는 대출해준 사람의 학습 성취를 실제 학생의 학습 성취와 동일하게 해둠.

  (6)
  턴 99가 영원한 지속을 의미로 사용
  (ITEM_NOCLASS에서도 사용됨)
  오늘자의 (3) 구현과도 관계 있음

  (7) ItemUse에서...
  switch 구문 (type에 따라서 구분하는..)
  이 범용적이지는 않음.
  좀 하드코딩 적임.
  어떤 if문에는 case TARGET_OTHER 만 구현이 되어 있음.

//  (8) ITEM_NOCLASS 역시
//  meetGrade 에서 이루어질 예정.! (meetGrade 는 중요하다)
//  성공!

   (9) GamePlayerContainer의 itemUse에서 
   gRC->FindPlayerIndexInTheRoom 부분을 하나의 변수로 통일 하는 것을 추천

   (10) ITEM_MOVEPLACE 가 진행중입니다.
   case에 삽입 하는 데 성공했습니다.
   PK_WARPSTART_ASK 를 만들고 있습니다. 실패했습니다.

   // [10월 8일]
// (1) 게임이 실행되도, full에서 playing으로 변하지 않는 버그 (방페이지의 리스트를 보고 있는사람들에게) 수정

   (2) refactoring fail.
   1> CHARINFO class 를 분리할 것을 권고
//  2> move 모듈을 분리할 것을 권고
   3> m_cooltime 에서, flag 부분을 변경할 것을 권고
   

	//		[10월 9일]
	//   (1) move 모듈 분리에 성공 - 디버깅 안해봄.

   (2) 일반 디자인 패턴 원칙에 대해 고민해보다.
	- 여튼 잘게 쪼개는 걸로는 한계가 있을 것 같다.
	- int m_arr[30] 보다는 int30class m_cla 이 더 좋아보이지 않느냐?!

	(3) 가끔씩 LOGIN에서 NOID ERROR가 뜨는데, 접속은 되게되는 경우가 있다...
	=> 서버 키고 오랜 시간이 지나면 그런 오류가 나는 것 같은데?


	//(4) clinet map 출력 문제 완료

----- 여기서부터 시작 ----- (10월 24일자) 아이템 워프 관련 등 기타...

	[참고 파일]
	network.h 파일
	GamePlayerContianer.h 의 State 두개
	pk_itemuse_ask() 아래 쪽 부터
	MainWin.cpp ask signal.
	movePlayer 쪽 변경
	pk_moveend_ask() 쪽 변경하려다 맘, 이거는 합체 뒤 변경. ㅇㅇ

	// [10월 9일] (2) - item popinfoarr 관련.. (이건 커밋한 파일을 리로드 해서. ... 해야함;)
	network.h network파일이 변경. // (10월 24일) 이거 창규형이 바꾼거다. 근데 network.h 뭐 많이 바뀌었더만. ㅇㅇ	
	GamePlayerContainer.cpp 에서 state를 변경. 

	[10월 24일]	모든 일은 item use 부터.. 하단부터 일어나고 있습니다.
	(1) pk_itemuse_ask() 쪽을 들어가고 있습니다.
	1> 질문 : 그래서 pk_itemuse_ask 에서 ITEMUSE_ERROR 가 아니면 Send도 안해준단 말이에요? 
	2> if(iuState == IUS_NONE) 라면, 그냥 success만 내뿜을 거야, 그러면 패킷이 그 다음에 오겠지...
	 그래서 itemUse에서 itemUse가 success했다고 보내지 뭐..
	3> iuState 확장... 
	4> pk_warpstart_ask, pk_warpstart_rep, , pk_warpend_ask,  동시 작업 시작
	... MainWin.cpp 에도 이미 등록이 된 상태가 됬네..
//	혹여나 중단하고 싶다면... 주석 처리 하고 위에 있는 관련 함수 역시 주석처리하면 돌아갈듯.
	1차 패스.
	5> 심각한 문제 :
	 녹두 처리를 어떻게 해야할 지 모르겠다.
	 방법 . (1) movePlayer의 state를 bool 에서 mPState = {move,bus,warp} 로 변경
	 (2) warp 시 처리하는 함수를 만듬.

    6> 이거 주석처리 해놔라. pk_moveend_ask() 에서..
	 PushbSynAllPlayer(nRoomIndex,false); 
	 그리고 pk_busmoveselect_ask() 애서
	PushSynAllPlayer(nRoomIndex,false); 를 구현해라.
	 그리고 새로 만든 함수에서 
	 PushbSynAllPlayer(nRoomIndex,false); 이 녀석 주석 처리를 해노렴.
	아니 왜냐하면, 이거 기본 값이 true야! /* */
	(근데 기본 값이 false가 되어도 사실 상 별 문제가 안되어 보이기는 한다.)
	예상되는 문제 : 뭐 주사위를 던졌는데, 안넘어간다던지..
	예상되는 문제2 : 버스 문제
	여튼 문제 있으면 이거 다시 주석 빼면 되겠네. 아니 수정 안했다. ㅇㅇ

	7> 시작!
	// pk_warplistend_rep, pk_warplistend_ask
    7-1>
	struct PK_WARPLISTEND_ASK 이녀석 에 id 추가 요청

	뭐 여튼 완성!!
	근데 디버깅은 하루 예상 중...


----- 여기서부터 시작 ----- (10월 31일자) 디버깅 툴
(1) 순조롭게 디버거를 만들고 있습니다.
- MessageCore.cpp 에서 작업을 하고 있는데,
- debuger_move 나, debuger_card 는 GamePlayerContainer.h 로 옮겨갈 듯 합니다.

ㅇㅇ 완성!
물론 디버깅 그런건 없음.

(2)
바뀐 패킷대로 다시 서버를 조정하고 있습니다.
패킷이 모두 너무 근본적으로 바뀌었으므로 모든 가능성을 고려해야 할 듯.
/*
(1) ITEMUSE_ASK Series를 다 ITEMUSESTART_ASK 로 변경

(3) ITEMUSE_ASK ITEMUSE_REP Series를 만든다.

(2) INFOCHANGEEND_ASK 를 만든다.

(4) INFOCHANGE_REP 등 뒤에 Turn End를 다 INFOCHANGEEND_ASK 로 만든다.

아 그냥 다시 다 짜야할듯;;;

(5)	struct PK_WARPSTART_REP 변경 공고!
*/

(3)
 0> notice
 MainWin 처리는 아직 전혀 안되있음.
 ... 뭔가 하고 있었는데 ...
 nInRoomIndex 가 햇갈릴 가능성이 꽤 높다고 생각 중...

 1> itemuse_ask -> itemuse_rep -> itemusestart_ask ... 하다가...

 m_struct_itemuse_ask 의 등장...
 m_struct_itemuse_ask[nRoomIndex] = ask;	// 이거 잘 되겠지?

 뭐 일단 대충 완성

 

 2> itemusestart_sk 에서 moveselect 부분...

 !! ITEM_MOVEPLACE 의 TARGE_OTHER 는 구현되어 있지 않음
 !! 아마, 상당 수의 item case가 하드 코딩일 가능성...

// putTargetTrue, putTargetInt 구현 중 
// 하지만 이것은 other case 만 만족하는 가짜 함수
 putTargetIntforOther 만 간신히 명맥을 유지...

 대충 완성됨
 
 5> 이제... warplistend_rep 부분에서 turnnext 하는 부분.
 완성 된 것 같던데?

 6> warpend_rep 에서 turnnext 내지는 infochange_rep2 하는 부분.
 완성했어.

 3> itemusestart_ask 의 infochange_rep (1) 부분...
  대충 완성됨
 

 4> noclass, togetherclass 쪽이 
  완성된 셈.

 7> 간단한 infochangeend_ask 함수
 완성!

 8> 마무리 단계
 gMainWin 처리 해야지?
 함수도 다 잘 넣고.


 ----- 여기서부터 시작 ----- (10월 31일자) 버그
 (1) testset : 0번 아이템
  아이템을 썻는데, 턴 넥스트가 아니네.
  info도 안오네.

  (1-1) 문제1 : 
 아이템을 썻는데, 한 명에게만 오는 부분 itemuse_ask 에서.. : 해결

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
	 [pk_warpend_ask] 심각한 Error, 보안 주의 요망, 서버와 클라이언트의 연산 결과가 다름
server : 5 14 , client : -45210182 -2 player : test1 etc : 0 0
		 이 방은 더 이상 동작하지 않습니다.
		 a.b
		 [PK_INFOCHANGEEND_ASK] 211.169.219.68	 message : test2
		 [PK_WARPEND_ASK] 211.169.219.68	 test2 
		 [PK_WARPEND_ASK] 211.169.219.68	 test2 
		 [pk_warpend_ask] 심각한 Error, 보안 주의 요망, 서버와 클라이언트의 연산 결과가 다름
server : 5 14 , client : 13 16 player : test2 etc : 0 0
		 이 방은 더 이상 동작하지 않습니다.


		p"stat에 multi가 적용되지 않음

------ 배교파 (11월 2일) ----

상우 : 아이템 관련 버그

	 1. 아이템 사용 -> 바로 사라지지 않는다.
//	 => 아이템 사용하면, 서버는 PK_ITEMUSE_REP 를 쏜다.
//	 쟤 쏘면서 PK_GAMEPLAYERINFO_REP 쏴 줄 것.

	 2. debug 관련
//	 => /card n,    명령어의 경우 index n의 카드가 오지 않고, 랜덤으로 이상하게 온다.

//	 => 디버그 명령어 보낼 때, 해당 turn이 아닌 넘이 보내면 무시할 것.
// 해결
/*
	 network.h
 struct GAMEPLAYER

	 에서 BYTE로 되어있는 정보 있던것들 int로 바꿨음.
	 왜냐하면 BYTE가 unsinged int 처럼 쓰여서 음수 쓸수가없어서......
	 => 니꺼 소스도 걍 바꿔놨음. 알고만 있으면 될듯. 고칠 거 없이.
*/

	 =========== 플레이어 2명일 때 테스트 ===========
	 card 00 - 커닝페이퍼
//	 PK_INFOCHANGE_REP 에서 id값만 오고, nLang이런것들이 0으로 온다.
   -  임시방편 문제 : 모든 케이스를 생각하고 만든게 아니다!
   -  nMulti 가 사용되는 경우 TARGET_ME 에서만 유효하다!
   
   -  근본적 문제 : 아이템을 중복 사용하는 경우를 생각하지 않았다.
   - 예컨대, 커닝페이퍼를 두 번 사용할 수 없는데, 능력치는 뭔가 증가되는 것으로 나온다.

	pk_gameplayerinfo_rep 문제 학습. 수리. 예체능 능력이 아이템에 의해 갱신되지 않는다.


	 card 03 - 대중예술의 이해 책
	 card 04 - 중앙도서관
	 /*
	 PK_INFOCHANGE_REP는 잘 옴.
	 그런데, PK_INFOCHANGE_REP만 오고, PK_GAMEPLAYERINFO_REP가 오지 않음.
	해결. pk_gameplayerinfo_rep가 안 온게 아니라. 정보를 안보내고 있던 것. 오류 수정.
	 */
 

	 card 07 - 잘자라 우리 아가
	 ex) test1 이  test2에게 사용.
	 그런데, PK_INFOCHANGE_REP 에는 test2만 와야되는데, test1, test2 다옴.

	 card 08 - 아이폰
	 ex) test1 이  test2에게 사용.
	 그런데, PK_INFOCHANGE_REP 에는 test2만 와야되는데, test1, test2 다옴.

	 card 12 - 옳지 않은 소개팅
	 card 14 - 박카스
/*
	 PK_INFOCHANGE_REP가 전부 0으로 옴.
*/
/*
	 @ PK_INFOCHANGE_REP는 화면에  + 3 이렇게 띄워주는 데 쓰이는 거.
	 @ 실제 정보 변동은 PK_GAMEPLAYERINFO_REP 로 이루어짐..

	 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	 아직 이정도밖에 못했음.....
	 해결하고 보고바람. 클라이언트 문제일수도있으니, 서버가 잘못되지 않았으면
	 말해줘(아마 아닐듯.. 디버그로 계속 체크하면서 했으니).
	 하고 말해줘.

	 클라이언트 update받고 작업할것.
*/
	 card 17 -
	 뻑남. pk_itemuse_ask 에서 rep가 corrupted 되었다고 한다.
	 strcpy(rep.szTarget,ask.szTarget) 을 주석처리하면, server에서는 어떻게 넘어가는데,
	 client에서 여전히 뻑난다.

	 card 18 - 
	 잘 됨
	 card 19 -
	 뻑남.

//	 [문제1] TARGET_OTHER 문제
//	 => itemUse 부분
//	 => pk_infochangeItem_rep
//	 [문제2] ITEM_STAMINA case
	 [문제3] 비범용성
	 [문제4] 중복 사용의 문제
	 (둘 다 현실의 문제는 아님)