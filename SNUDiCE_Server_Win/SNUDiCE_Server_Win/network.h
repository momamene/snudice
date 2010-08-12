#pragma once
#include <windows.h>
#pragma comment(lib, "ws2_32.lib") 

#define	WINSOCK_VERSION_2_2		MAKEWORD(2, 2)
#define SERVER_IP				"127.0.0.1"
#define SERVER_PORT				9000
#define BUFFERSIZE				1024

#define PK_HEADER_SIZE		4

#define CHATMSG_LENGTH			64
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//	통신 프로토콜
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
enum ePROTOCOL
{
	PL_LOGIN_ASK,
	PL_LOGIN_REP,
	PL_NORMALMSG_ASK,
	PL_NORMALMSG_REP,
};


enum eCOREMODE
{
	ECM_NONLOGIN,			// login 안한상태
	ECM_LOGIN,				// 얘는 걍 클라이언트에서 로그인 하기 위해 필요한 모드. 네트워크엔 관계없음
	ECM_BATTLENET,			// LOGIN 하면 이 모드
	
	
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


struct USER
{
	char		szID[16];
	char		szPW[16];
	eCOREMODE	coreWhere;
	int			nCoreFlag;
};

struct PLAYER
{
	char		szID[16];
	eCOREMODE	coreWhere;
	int			nCoreFlag;
	SOCKET		sock;
};

struct PK_LOGIN_ASK
{
	char		szID[16];
	char		szPW[16];
};

enum LOGIN_ERROR
{
	ELE_NOID,			// id 없음
	ELE_PWERROR,		// pw 에러
	ELE_OVERCONNECT,	// 중복접속
	ELE_SUCCESS,		// login 성공
};

struct PK_LOGIN_REP
{
	PLAYER			player;
	LOGIN_ERROR		error;
};

typedef struct
{
	char	szID[16];
	char	szMsg[CHATMSG_LENGTH];	

}	PK_NORMALMSG_ASK,	PK_NORMALMSG_REP;
