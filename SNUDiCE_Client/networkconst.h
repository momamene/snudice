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

#define WINSOCK_VERSION_2_2		MAKEWORD(2, 2)
#define SERVER_IP				"127.0.0.1"
#define SERVER_PORT				9000
#define BUFFERSIZE				512

#define WM_SOCKET				WM_USER + 1