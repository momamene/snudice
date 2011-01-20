//------------------------------------------------------------------------------------
//	networkconst.h
//
//	2010. 08. 04	CoderK	
//
//	network 관련 define 및 프로토콜 및 패킷 구조체
//	ws2_32.lib 추가해야 함
//------------------------------------------------------------------------------------
#pragma once
#include <windows.h>

#define WM_SOCKET				WM_USER + 1

#define	WINSOCK_VERSION_2_2		MAKEWORD(2, 2)
#define SERVER_IP				"211.169.219.93"		// 승엽
//#define SERVER_IP				"211.169.219.86"		// 현탁
//#define SERVER_IP				"211.169.219.87"		// 창규
#define SERVER_PORT				9000
#define BUFFERSIZE				2048

#define PK_HEADER_SIZE			4

#define SNUDICE_VERSION			"0.9002"

//#define DEF_SERVER

//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//	통신 프로토콜
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
enum ePROTOCOL
{
	PL_LOGIN_ASK,
	PL_LOGIN_REP,
	PL_MESSAGE_ASK,
	PL_MESSAGE_REP,

	PL_CHANNELREFRESH_REP,

	PL_CHANNELCHANGE_ASK,
	PL_CHANNELCHANGE_REP,

	PL_ROOMMAKER_ASK,
	PL_ROOMMAKER_REP,

	PL_ROOMLIST_ASK,
	PL_ROOMLIST_REP,

	PL_ROOMJOIN_ASK,
	PL_ROOMJOIN_REP,

	PL_ROOMREFRESH_REP,

	PL_CHARSELECT_ASK,
	PL_GAMEREADY_ASK,
	PL_GAMESTART_ASK,
	PL_GAMESTART_REP,

	PL_SUBMIT_ASK,
	PL_SUBMIT_REP,

	PL_SUBMITREADY_ASK,
	PL_SUBMITREADY_REP,

	PL_SUBMITCOUNT_ASK,			// 수강신청모드, 일정시간 지나면 시간 지났다고 알려주는 용도

	PL_MAINGAMESTART_REP,

	PL_MOVESTART_ASK,
	PL_MOVESTART_REP,
	PL_MOVEEND_ASK,

	PL_BUSMOVECHOOSE_REP,
	PL_BUSMOVESELECT_ASK,
	PL_BUSMOVESTART_REP,
	PL_BUSMOVEEND_ASK,

	PL_GAMEPLAYERINFO_REP,

	PL_GAMEEND_REP,

	PL_NEXTTURN_REP,

	PL_ITEMUSE_ASK,
	PL_ITEMUSE_REP,

	PL_ITEMUSESTART_ASK,

	PL_WARPSTART_REP,			// 유저 하나.
	PL_WARPEND_ASK,

	PL_WARPLISTSTART_REP,		// 유저 여러명 워프시킬떄
	PL_WARPLISTEND_ASK,

	PL_INFOCHANGE_REP,			// 아이템 사용 -> 캐릭터 스탯같은 수치 변화 표시
	PL_INFOCHANGEEND_ASK,

	PL_ROOMBACK_ASK,			// 게임끝 -> 방으로
	PL_ROOMBACK_REP,			//

	PL_EXIT_REP,				// 게임중 강제종료 처리

	PL_GOLOGIN_ASK,

	//	PL_WHISPER_ASK,				// Whisper
	PL_FRIENDADD_ASK,			// 친구 추가
	PL_FRIENDDELETE_ASK,		// 친구 삭제
	PL_FRIENDWHISPER_ASK,		// 친구에게 귓말
	PL_FRIENDLIST_ASK,			// 친구 목록 나열

	PL_ASKCOUPLE_REP,			// 커플될건지 묻는다.
	PL_ANSCOUPLE_ASK,			// 답변

	PL_BECOUPLE_REP,			// 커플 되었다는 정보 출력
	PL_BECOUPLEEND_ASK,			// 정보 끗

	PL_MOVESTARTCOUPLE_REP,		// 주사위 굴려 이동. 커플모드
	PL_MOVEENDCOUPLE_ASK,

	PL_BUSMOVESTARTCOUPLE_REP,	// 버스타고 이동. 커플모드
	PL_BUSMOVEENDCOUPLE_ASK,
};

enum eCOREMODE
{
	ECM_NONLOGIN,			// login 안한상태

	ECM_LOGIN,

	ECM_BATTLENET,			// LOGIN 하면 이 모드

	ECM_ROOMMAKE,
	ECM_ROOMJOIN,
	ECM_ROOM,

	ECM_SUBMIT,				// 수강신청

	ECM_GAME,				// 메인게임
};

struct PK_DEFAULT
{
	WORD	dwSize;
	WORD	dwProtocol;
	char	strPacket[BUFFERSIZE];
};

#define MSGLENGTH				128			// 채팅할때 메시지 길이제한
#define IDLENGTH				16			// ID 길이 제한
#define CHANNELUSERMAX			10			// 한 채널에 있는 사람 수 최대
#define CHANNELMAX				6			// 채널 개수

struct USER
{
	char		szID[IDLENGTH];
	char		szPW[33];
};

enum CLASSTYPE
{
	CLASS_NONE = -1,		// 선택안된거
	// 언어
	CLASS_LITERAL,			// 인문
	CLASS_SOCIAL,			// 사회
	CLASS_MANAGE,			// 경영
	CLASS_LAW,				// 법
	CLASS_LIFE,				// 생활과학
	CLASS_TEACH,			// 사범대
	CLASS_FREE,				// 자유전공

	// 수리
	CLASS_ENGINE,			// 공
	CLASS_NATURE,			// 자연
	CLASS_DOCTOR,			// 의사
	CLASS_ANIMAL,			// 수의사
	CLASS_DRUG,				// 약
	CLASS_NURSE,			// 간호
	CLASS_FARM,				// 농

	// 예술
	CLASS_MUSIC,			// 음
	CLASS_ART,				// 미

	CLASS_END,

};

#define CHARNAMELENGTH		16
#define CHARCOLLEGENAME		16
#define MAXCHARNUM			16		// 캐릭터 갯수

struct CHARINFO
{
	char		szName[CHARNAMELENGTH];
	char		szCollege[CHARCOLLEGENAME];
	bool		bMale;
	// 학습력
	int			nLang;
	int			nMath;
	int			nArt;
	// 체력
	int			nStamina;
	// 이동력
	int			nDice4;
	int			nDice6;
};

struct PLAYER
{
	char		szID[IDLENGTH];
	eCOREMODE	coreWhere;
	int			nCoreFlag;		//이놈 뭐하는 놈이냐
	SOCKET		sock;

	// 게임관련 정보
	CLASSTYPE	classtype;
	bool		bReady;
};

struct PK_LOGIN_ASK
{
	char		szID[IDLENGTH];
	char		szPW[33];
};

enum LOGIN_ERROR
{
	ELE_NOID,			// id 없음
	ELE_PWERROR,		// pw 에러
	ELE_OVERCONNECT,	// 중복접속
	ELE_USEROVER,		// 서버 수용 인원 초과
	ELE_SUCCESS,		// login 성공
};

struct CHANNEL
{
	int				nChannelNum;
	int				nUserNum;
	char			szUserInCh[CHANNELUSERMAX][IDLENGTH];		// 채널에 있는 유저 ID 들
};

struct PK_LOGIN_REP
{
	PLAYER			player;
	LOGIN_ERROR		error;
	CHANNEL			channel;
};

typedef struct
{
	char	szID[IDLENGTH];
	char	szMsg[MSGLENGTH];

} PK_MESSAGE_ASK, PK_MESSAGE_REP;


typedef struct
{
	CHANNEL			channel;

} PK_CHANNELREFRESH_REP;

enum CH_CHANGE_ERROR
{
	ECE_SUCCESS,
	ECE_CHANNELISOVER,
};

struct PK_CHANNELCHANGE_ASK
{
	char			szID[IDLENGTH];
	int				nChannel;
};

struct PK_CHANNELCHANGE_REP
{
	CH_CHANGE_ERROR	error;
	CHANNEL			channel;
};

#define MAXROOMFORPAGE		8								// 한 페이지에 표시될 수 있는 방 개수
#define MAXROOM				40								// 만들 수 있는 방 개수
#define MAXROOMNAME			32
#define MAXROOMPASS			16
#define ROOMMAXPLAYER		6
#define MAXPAGE				(MAXROOM / MAXROOMFORPAGE)

struct ROOM
{
	bool	isGaming;										// 게임중
	bool	isPass;
	char	szRoomName[MAXROOMNAME];
	char	szRoomPass[MAXROOMPASS];
	int		nMaxPlayer;
	int		nNowPlayer;
	int		nMakerIndex;									// 방장의index
	char	szRoomMaxPlayer[ROOMMAXPLAYER][IDLENGTH];		// 기본적으로 0번째가 방장
};

struct PK_ROOMMAKER_ASK
{
	char		szID[IDLENGTH];
	ROOM		room;
};

enum ERROR_ROOMMAKE
{
	ERM_USINGNAME,		// 방이름 중복
	ERM_SUCCESS,
};

struct PK_ROOMMAKER_REP
{
	ERROR_ROOMMAKE	result;
	ROOM		room;
	PLAYER		playerlist[ROOMMAXPLAYER];
};

struct PK_ROOMLIST_ASK
{
	char		szID[IDLENGTH];
	int			nPage;
};

struct PK_ROOMLIST_REP
{
	int			nPage;
	ROOM		roomlist[MAXROOMFORPAGE];
};

struct PK_ROOMJOIN_ASK
{
	char		szID[IDLENGTH];
	int			nPage;					// 페이지
	int			nIdx;					// 페이지에서 몇번째냐
	char		szPass[MAXROOMPASS];
};

enum ERROR_ROOMJOIN
{
	ERJ_SUCCESS,
	ERJ_PASSWRONG,
	ERJ_FULL,
	ERJ_PLAYING,
	ERJ_NOROOM,
};

struct PK_ROOMJOIN_REP
{
	ERROR_ROOMJOIN		result;
	ROOM				joinroom;
	PLAYER				playerlist[ROOMMAXPLAYER];
};


//방나가고돌아오기수정

struct PK_ROOMBACK_ASK
{
	char		szID[IDLENGTH];	
};

struct PK_ROOMBACK_REP
{
	ROOM		room;
	PLAYER				playerlist[ROOMMAXPLAYER];
};


struct PK_ROOMREFRESH_REP
{
	ROOM				room;
	PLAYER				playerlist[ROOMMAXPLAYER];
};

struct PK_CHARSELECT_ASK
{
	char				szID[IDLENGTH];
	CLASSTYPE			classtype;
};

typedef struct
{
	char				szID[IDLENGTH];
	bool				bReady;

} PK_GAMEREADY_ASK, PK_GAMESTART_ASK;

enum ERRORGAMESTART
{
	EGS_NOREADY,			// 방장이 준비가 안됨..(방장이 캐릭터 선택 x)
	EGS_NOREADYUSER,		// 유저들이 준비가 안됨.
	EGS_ONEUSER,			// 유저가 방장 한명이라 시작 불가.(한명으로 게임 시작 불가)
	EGS_SUCCESS,
};

#define AVAILSEAT		255
#define CLASSNUM		18
#define CLASSSEAT		3
#define NOSEAT			99

struct PK_GAMESTART_REP
{
	ERRORGAMESTART		result;
	BYTE				subject[CLASSNUM][CLASSSEAT];
};

#define	SUBMITTICK		20000

// 수강 신청
struct PK_SUBMIT_ASK
{
	char			szID[IDLENGTH];
	BYTE			nSubjectIdx;			// 신청한 과목 index
	bool			bSubmit;				// true면 신청, false면 취소
};

struct PK_SUBMIT_REP
{
	BYTE			subject[CLASSNUM][CLASSSEAT];
};

struct PK_SUBMITREADY_ASK
{
	char			szID[IDLENGTH];
};

enum ESUBMITERROR
{
	ESUB_LESSCLASS,					// 수강과목이 6개 아래다.
	ESUB_SUCCESS,
};

struct PK_SUBMITREADY_REP
{
	ESUBMITERROR	result;
};

struct PK_SUBMITCOUNT_ASK
{
	char			szID[IDLENGTH];
};

#define MAXSUBJECT				6	// 한사람당 들을수잇는 과목수
#define MAXITEMNUM				4	// 한사람당 갖고있을 수 있는 아이템 수

struct GAMEPLAYER
{
	char		szID[IDLENGTH];
	// 게임정보
	CLASSTYPE	ctype;

	int			nLang;
	int			nMath;
	int			nArt;
	int			nStamina, nMaxStamina;
	int			nDice4, nDice6;

	float		fGrade[MAXSUBJECT];
	float		fAvGrade;
	BYTE		bySubIdx[MAXSUBJECT];
	int			nRank;

	int			nItem[MAXITEMNUM];		// 없으면 -1

	int			nLove;					// 애정도.			커플 아니면 - 1
	char		szCouple[IDLENGTH];		// 커플 아이디		커플 아니면 memset 0

	WORD		nPos;
};

struct PK_MAINGAMESTART_REP
{
	GAMEPLAYER	list[ROOMMAXPLAYER];
	int			nTurn;						// 누구 턴
};

// 메인 게임

struct PK_MOVESTART_ASK
{
	char		szID[IDLENGTH];
	int			nCurPos;			// 출발 좌표
};

typedef struct
{
	int			nDist;
	BYTE		Dice4_1;
	BYTE		Dice4_2;
	BYTE		Dice6_1;
	BYTE		Dice6_2;
}
PK_MOVESTART_REP, PK_MOVESTARTCOUPLE_REP;

typedef struct
{
	char		szID[IDLENGTH];
	int			nDestPos;			// 도착 좌표
}
PK_MOVEEND_ASK,  PK_MOVEENDCOUPLE_ASK;

struct PK_NEXTTURN_REP
{
	int			nNowTurn;			// 현재 턴
	int			nNextTurn;			// 다음 턴
};

struct PK_BUSMOVECHOOSE_REP			// 이동한 칸이 버스다. 이동할 곳 찍어라 라고 서버가 보내주는 패킷(해당 플레이어만)
{
	int			nNowTurn;
};

struct PK_BUSMOVESELECT_ASK
{
	char		szID[IDLENGTH];
	int			nPos;
};

typedef struct			// 모든 애들한테 이동시켜라 라고 뿌려줌
{
	int			nDist;
}
PK_BUSMOVESTART_REP, PK_BUSMOVESTARTCOUPLE_REP;

typedef struct			// 모든 애들한테 받아서 다 받으면, nextturn
{
	char		szID[IDLENGTH];
	int			nDestPos;
}
PK_BUSMOVEEND_ASK, PK_BUSMOVEENDCOUPLE_ASK;

struct PK_GAMEPLAYERINFO_REP
{
	GAMEPLAYER	list[ROOMMAXPLAYER];
};

struct CHANGEINFO
{
	char		szID[IDLENGTH];
	int			nLang;
	int			nMath;
	int			nArt;
	int			nStamina;
	int			nGrade;				// 성취도. 학점이 아님
	int			nLove;
};

struct PK_GAMEEND_REP
{
	char		szID[IDLENGTH];		// 이긴넘
};

#ifdef DEF_SERVER
#define ITEMNUM		29 +1			// 
#else
#define ITEMNUM		29
#endif

enum ITEMTARGET
{
	TARGET_ME,				// 나
	TARGET_ALL,				// 나 포함 모든 유저
	TARGET_ALLEXCEPTME,		// 나 빼고 모든 유저
	TARGET_OTHER,			// 다른 유저 하나
	TARGET_MEOTHER,			// 나랑 상대
	TARGET_OTHERSEX,		// 이성
	TARGET_MYCOUPLE,		// 내 애인
	TARGET_OTHERCOUPLE,		// 다른 커플
	TARGET_ALLCOUPLE,		// 모든 커플
	TARGET_ALLSINGLE,		// 모든 싱글

};

enum ITEMTYPE
{
	ITEM_STAT,
	ITEM_STAMINA,
	ITEM_MOVESELECT,		// 내가 선택한 칸으로 이동
	ITEM_MOVEPLACE,			// 스크립트에 지정된 장소로 이동
	ITEM_NOCLASS,			// 휴강. 상대의 다음 수업을 무효화
	ITEM_TOGETHERCLASS,		// 상대가 내 수업과 겹칠 때, 나도 성취도 +
	ITEM_LOVE,				// 애정도
	ITEM_DASH,				// 거절가능 대쉬
	ITEM_POWERDASH,			// 거절불가 대쉬
};

struct ITEMCARD
{
	ITEMTYPE	type;
	ITEMTARGET	target;
	int			nLang;			// ITEM_STAT
	int			nMath;			//
	int			nArt;			//
	int			nMove;			// 얜 지금 안쓸거야
	int			nStamina;		// ITEM_STAMINA
	int			nMulti;			// ITEM_STAT		*
	int			nExistTurn;		// 지속 턴
	int			nPos;			// ITEM_MOVEPLACE
	int			nLove;			// 애정도
};

struct PK_ITEMUSE_ASK
{
	char		szID[IDLENGTH];			// 사용자
	char		szTarget[IDLENGTH];		// 대상
	int			nItemID;
	int			nStartPos;				// move일 때
	int			nDestPos;				// move일 때
};

struct PK_ITEMUSE_REP
{
	char		szUser[IDLENGTH];		// 사용자
	char		szTarget[IDLENGTH];		// 대상
	int			nItemID;
};

struct PK_ITEMUSESTART_ASK
{
	char		szID[IDLENGTH];
};


struct PK_WARPSTART_REP
{
	char		szID[IDLENGTH];  // 움직이는 넘.
	int			nDest;    // 도착 좌표
};

struct PK_WARPEND_ASK
{
	char		szID[IDLENGTH];
	int			nDestPos;			// 도착 좌표
};

struct PK_WARPLISTSTART_REP
{
	int			nDestPos[ROOMMAXPLAYER];		// 해당사항 없는 놈은 -1로 채워서.
};

struct PK_WARPLISTEND_ASK
{
	char		szID[IDLENGTH];
	int			nDestPos[ROOMMAXPLAYER];		// 해당사항 없는 놈은 -1로 채워서 보냄
};

struct PK_INFOCHANGE_REP
{
	CHANGEINFO	info[ROOMMAXPLAYER];			// 해당 없는 놈 memset(info , 0)
};

struct PK_INFOCHANGEEND_ASK
{
	char		szID[IDLENGTH];
};

struct PK_GOLOGIN_ASK
{
	char		szID[IDLENGTH];
};

struct PK_EXIT_REP
{
	char		szID[IDLENGTH];
	int			flag;							// 남은 사람 수 //아직까지는 그닥 있어야 할 이유는 없다.
};

/*//WHISPER 구현
struct PK_WHISPER_ASK
{
char		szToID[IDLENGTH];
char		szFromID[IDLENGTH];
char		szComment[MSGLENGTH];
};
*/
typedef struct
{
	char		szMyID[IDLENGTH];
	char		szFriendID[IDLENGTH];
} PK_FRIENDADD_ASK, PK_FRIENDDELETE_ASK;

struct PK_FRIENDWHISPER_ASK
{
	char		szMyID[IDLENGTH];
	char		szComment[MSGLENGTH];
};

struct PK_FRIENDLIST_ASK
{
	char		szMyID[IDLENGTH];
};


// couple
struct PK_ASKCOUPLE_REP
{
	char		szCouple[IDLENGTH];				// 나랑 커플될 넘의 id
};

struct PK_ANSCOUPLE_ASK
{
	bool		bYes;
};

struct PK_BECOUPLE_REP
{
	char		szMale[IDLENGTH];
	char		szFeMale[IDLENGTH];
	bool		bCouple;						// true면 커플, false면 깨짐
};

struct PK_BECOUPLEEND_ASK
{
	char		szID[IDLENGTH];
};

#define COUPLE_DEBUFFTURN      5
#define COUPLE_MINUS_STAT      -5