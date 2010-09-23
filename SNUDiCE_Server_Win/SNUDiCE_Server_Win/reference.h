// 9월 19일 (일) 오후 03시 이후의 이야기
(1) Draw 함수를 만들고 있었는데, m_hWnd가 엉망으로 말을 잘 안듣는 사실을 깨닫거나,
혹은 hWnd를 가지고 gPlayerContainer에서 hdc와 ps를 만들어도 잘 안된다는 사실을 깨달았다.
귀찮으니까 나중에 확인해 볼것


// 9월 21일 (화) 오전 03시의 이야기
SendRoomRefreshCauseChange 를 만들었는데 잘 돌아갈까?

// 9월 22일 (수) 오후 10시 이후 야작의 이야기
// (1) 방장이 바뀌는데, ready한 녀석의 ready를 풀어야 하는 문제 : 해결
// (2) id가 없다는 이상한 문제 : 다시 켜니 해결
// (3) gamestart 패킷 : 임시방편으로 완성 

(4) submitCore를 만들자!
(5) subjectContainer는 비호환적인 시스템 (예컨대, 과목수를 서로 다른 define 값으로 결정) 을 가지고 있다.
 최신버전으로 바꾸도록 하자.

 (6) RoomCore의 p.324 정도의 sangwoo temp, 부분을 좀 더 유연성 있게 변경할 필요가 있을 것 같다.
  그러려면, isAllReadyInRoom 의 정보가 바뀌어야 겠지.
  그러려면, player가 room의 정보를 통합해야 겟지.
  지난번에, player와 channel과의 관계가 문제가 되었었지.
  으으으으으으음...