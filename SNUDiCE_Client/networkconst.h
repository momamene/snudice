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
#define BUFFERSIZE				1024

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

struct PLAYER
{
	char		szID[IDLENGTH];
	eCOREMODE	coreWhere;
	int			nCoreFlag;
	SOCKET		sock;
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

#define MAXROOMFORPAGE		6								// 한 페이지에 표시될 수 있는 방 개수
#define MAXROOM				100								// 만들 수 있는 방 개수
#define MAXROOMNAME			32
#define ROOMPASSWORD		16
#define ROOMMAXPLAYER		8

struct ROOM
{
	bool	isGaming;										// 게임중
	bool	isPass;
	char	szRoomName[MAXROOMNAME];
	char	szRoomPass[ROOMPASSWORD];
	int		nMaxPlayer;
	int		nNowPlayer;
	char	szRoomMaxPlayer[ROOMMAXPLAYER][IDLENGTH];		// 0번째가 방장
};

struct PK_ROOMMAKER_ASK
{
	ROOM	room;
};

enum ERROR_ROOMMAKE
{
	ERM_USINGNAME,		// 방이름 중복
	ERM_SUCCESS,
};

struct PK_ROOMMAKER_REP
{
	ERROR_ROOMMAKE	result;
};

struct SIMPLE_ROOMLISTINFO									// 방 들어가기 모드에서, 방 리스트들 room list
{
	bool	isGaming;
	bool	isPass;
	char	szRoomName[MAXROOMNAME];
	int		nMaxPlayer;
	int		nNowPlayer;
};

struct PK_ROOMLIST_ASK
{
	SIMPLE_ROOMLISTINFO		info[MAXROOM];
};