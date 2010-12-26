#pragma once
#include <winsock.h>
#include <windows.h>

#define	WINSOCK_VERSION_2_2		MAKEWORD(2, 2)
//#define SERVER_IP				"211.169.219.86"		// ��Ź
//#define SERVER_IP				"211.169.219.87"		// â��
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
	PL_UPDATESTART_ASK,			// ���� ���� ���
	PL_UPDATESTART_REP,			// ���� ����, �ֽŹ����̳� �˷���

	PL_FILENAME_ASK,			// n��° ���� �̸� ���
	PL_FILENAME_REP,
};

struct PK_UPDATESTART_ASK
{
	DWORD		dwVersion;
};

struct PK_UPDATESTART_REP
{
	int			nNewVer;
	bool		bRemainUpdate;		// true�� ������Ʈ, false�� �ֽŹ���
	int			nTotalFile;
	char		szURL[MAX_PATH];
};

struct PK_FILENAME_ASK
{
	int			nCur;
};

struct PK_FILENAME_REP
{
	char		szPath[MAX_PATH];		// ��ġ�� path
};