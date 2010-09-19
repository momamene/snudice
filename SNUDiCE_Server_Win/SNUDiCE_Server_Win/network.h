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
#define SERVER_IP				"211.169.219.71"
#define SERVER_PORT				9000
#define BUFFERSIZE				2048

#define PK_HEADER_SIZE			4

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
};


enum eCOREMODE
{
	ECM_NONLOGIN,			// login 안한상태
	ECM_LOGIN,
	ECM_BATTLENET,			// LOGIN 하면 이 모드
	ECM_ROOMMAKE,
	ECM_ROOMJOIN,
	ECM_ROOM,


	ECM_TITLE,				// 타이틀
	ECM_PSEL,				// 플레이어 고르자
	ECM_CSEL,				// 캐릭터 고르자
	ECM_SUBMIT,				// 수강신청
	ECM_GAME,				// 게임
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
	char		szPW[IDLENGTH];
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

struct PLAYER
{
	char		szID[IDLENGTH];
	eCOREMODE	coreWhere;
	int			nCoreFlag;
	SOCKET		sock;

	// 게임관련 정보
	CLASSTYPE	classtype;
};

struct PK_LOGIN_ASK
{
	char		szID[IDLENGTH];
	char		szPW[IDLENGTH];
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
#define ROOMMAXPLAYER		8
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

struct PK_ROOMREFRESH_REP
{
	ROOM				room;
	PLAYER				playerlist[ROOMMAXPLAYER];
};
