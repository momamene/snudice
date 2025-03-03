//------------------------------------------------------------------------------------
//	gMainWin Class													MainWin -> Server
//
//	2010. 08. 15	장난죄송
//
//	윈도우 관련 정보.
//	각종 셋업 및 게임의 주축.
//	Windows 기본 Class화 완성
//-------------------i-----------------------------------------------------------------

#pragma once
#include <windows.h>
#include <ddraw.h>
#include "network.h"
#include <stdio.h>

#define USE_LOG


#define	WNDSIZEW		640
#define WNDSIZEH		480
#define WNDNAME			"SNU Dice Server"
#define WNDSTYLE		(WS_CAPTION | WS_SYSMENU)

#define LOG_FILE_NAME	"Log.log"

//#define CRITICAL_SECTION_GOGO

class gMainWin  
{
public:
	static gMainWin		*GetIF();			// Use Singleton
	
	gMainWin();
	virtual ~gMainWin();

// 변수들
public:
	SOCKET		m_listen_sock;
	CRITICAL_SECTION crit[MAXROOM];	

	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	BOOL		m_Keys[256];				// keyboard
	RECT		m_rcScr;					// screen 출력 영역
	bool		m_bActive;					// 게임(윈도우)가 활성화 되어있나
	
	bool		Send(DWORD type, DWORD size, void *buf, SOCKET sock);
	bool		Send(DWORD type, DWORD size, void *buf, char* szID);
	void		Recv(PK_DEFAULT *pk, SOCKET	sock);

	void		UserRelease(SOCKET client_sock, SOCKADDR_IN clientAddr);

	bool		SetUp(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow);
	void		Release();
	void		Exit();
	
private:
	char		m_szTempReg[128];	
	
	FILE		*logFile;
	
// 함수들
public:

	bool		MakeListenThread();
	int			Run();
	void		MainLoop();
	//void		ExitPlayer(SOCKET client_sock,char* clientID,SOCKADDR_IN clientAddr);

	void		LogWrite(char * buf);
	
private:
	void		SetUpWindow(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow);
	bool		SetUpWinsock();
	
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static void err_quit(char *msg);					// 소켓 함수 오류 출력후 종료
static void err_display(char *msg);					// 소켓 함수 오류 출력

DWORD WINAPI ProcessClient(LPVOID arg);				// server <-> client 간 통신. 스레드
DWORD WINAPI Listen(LPVOID prc);					// 클라의 접속요청 받아 처리하는 쓰레드