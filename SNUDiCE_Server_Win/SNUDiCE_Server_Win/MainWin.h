//------------------------------------------------------------------------------------
//	gMainWin Class													MainWin -> Server
//
//	2010. 08. 15	�峭�˼�
//
//	������ ���� ����.
//	���� �¾� �� ������ ����.
//	Windows �⺻ Classȭ �ϼ�
//-------------------i-----------------------------------------------------------------

#pragma once
#include <windows.h>
#include <ddraw.h>
#include "network.h"

#define	WNDSIZEW		640
#define WNDSIZEH		480
#define WNDNAME			"SNU Dice Server"
#define WNDSTYLE		(WS_CAPTION | WS_SYSMENU)

class gMainWin  
{
public:
	static gMainWin		*GetIF();			// Use Singleton
	
	gMainWin();
	virtual ~gMainWin();

// ������
public:
	SOCKET		m_listen_sock;

	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	BOOL		m_Keys[256];				// keyboard
	RECT		m_rcScr;					// screen ��� ����
	bool		m_bActive;					// ����(������)�� Ȱ��ȭ �Ǿ��ֳ�
	
	bool		Send(DWORD type, DWORD size, void *buf, SOCKET sock);
	void		Recv(PK_DEFAULT *pk, SOCKET	sock);

	bool		SetUp(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow);
	void		Release();
	void		Exit();
	
private:
	char		m_szTempReg[128];	
	
// �Լ���
public:
	bool		MakeListenThread();
	int			Run();
	void		MainLoop();
	//void		ExitPlayer(SOCKET client_sock,char* clientID,SOCKADDR_IN clientAddr);

private:
	void		SetUpWindow(HINSTANCE hInstance, LPSTR lpszCmdParam, int nCmdShow);
	bool		SetUpWinsock();
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static void err_quit(char *msg);					// ���� �Լ� ���� ����� ����
static void err_display(char *msg);					// ���� �Լ� ���� ���

DWORD WINAPI ProcessClient(LPVOID arg);				// server <-> client �� ���. ������
DWORD WINAPI Listen(LPVOID prc);					// Ŭ���� ���ӿ�û �޾� ó���ϴ� ������