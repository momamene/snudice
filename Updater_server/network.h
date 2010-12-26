#pragma once
#include <winsock.h>
#include <windows.h>

#define	WINSOCK_VERSION_2_2		MAKEWORD(2, 2)
//#define SERVER_IP				"211.169.219.86"		// 현탁
//#define SERVER_IP				"211.169.219.87"		// 창규
#define SERVER_IP				"211.169.219.93"
#define SERVER_PORT				9010

#define BUFFERSIZE				2048
#define PK_HEADER_SIZE			4

#define FILEPATH_UPDATE			"http://211.169.219.93:8080/snudiceWebpage/clientFile/update/"

struct PK_DEFAULT
{
	WORD	dwSize;
	WORD	dwProtocol;
	char	strPacket[BUFFERSIZE];
};

enum PROTOCOL
{
	PL_UPDATESTART_ASK,			// 버젼 정보 물어봄
	PL_UPDATESTART_REP,			// 파일 갯수, 최신버젼이냐 알려줌

	PL_FILENAME_ASK,			// n번째 파일 이름 물어봄
	PL_FILENAME_REP,
};

struct PK_UPDATESTART_ASK
{
	DWORD		dwVersion;
};

struct PK_UPDATESTART_REP
{
	int			nNewVer;
	bool		bRemainUpdate;		// true면 업데이트, false면 최신버젼
	int			nTotalFile;
	char		szURL[MAX_PATH];
};

struct PK_FILENAME_ASK
{
	int			nCur;
};

struct PK_FILENAME_REP
{
	char		szPath[MAX_PATH];		// 설치할 path
};