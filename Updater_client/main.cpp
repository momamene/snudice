#include "network.h"
#include "resource.h"
#include <stdio.h>
#include <string>
//#include <direct.h>
#include <wininet.h>

using namespace std;

HWND	hDlgMain = NULL;

SOCKET			sock = NULL;
SOCKADDR_IN		serverAddr;

DWORD			dwClientVer;
DWORD			dwServerVer;
char			szPath[MAX_PATH];
char			szURL[MAX_PATH];
PK_DEFAULT		m_pkDefault;

int				cur;
int				total;
FILE			*fp;

bool SetUp();
	
#define REG_DIRECTORY	"SOFTWARE\\Project N\\SNUDiCE"
bool GetReg();

BOOL CALLBACK MainDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

bool Send(WORD type, WORD size, void *buf);
void Recv();
bool SocketErrorMessage(LPARAM lParam);
void Receive(LPARAM lParam);
void ReadPacket();
bool HTTPDown(HWND hWnd,  char *url, char *path);

void AutoFolderMake(char *szPath);

HICON	hIcon;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND	hWndClient;
	hWndClient = FindWindow(NULL, "SNUDiCE Updater");
	if(hWndClient)
	{
		MessageBox(NULL, "이미 업데이터가 실행중입니다.", "에러", MB_OK);
		return false;
	}

	hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, MainDlgProc);
	exit(0);
}

BOOL CALLBACK MainDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{
		case WM_INITDIALOG:
			hDlgMain = hDlg;
			SendMessage(hDlg, WM_SETICON, (WPARAM)TRUE, (LPARAM)hIcon);
			if(!SetUp())
			{
				MessageBox(NULL, "서버와 접속할 수 없습니다.", "Error", MB_OK);
				EndDialog(hDlg, IDOK);
			}
			Sleep(100);
			if(!GetReg())
			{
				MessageBox(NULL, "설치 정보를 얻어 올 수 없습니다.", "Error", MB_OK);
				EndDialog(hDlg, IDOK);
			}
			// version  ask
			Sleep(1000);
			PK_UPDATESTART_ASK		ask;
			ask.dwVersion = dwClientVer;
			Send(PL_UPDATESTART_ASK, sizeof(ask), &ask);
			return TRUE;
		case WM_SOCKET:
			{
				Receive(lParam);
			}
			return FALSE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
				case IDCANCEL:
					EndDialog(hDlg, IDOK);
					return TRUE;
			}
			return FALSE;
	}
	return FALSE;
}

bool SetUp()
{
	char		szBuf[256];
	int			retVal;

	WSADATA		wsa;
	if(WSAStartup(WINSOCK_VERSION_2_2, &wsa) != 0)
		return false;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET)
	{
		OutputDebugStr("socket 생성 실패\n");
		return false;
	}

	retVal = WSAAsyncSelect(sock, hDlgMain, WM_SOCKET,
							FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
	if(retVal == SOCKET_ERROR)
	{
		OutputDebugStr("WSAAsyncSelect() Failed\n");
		closesocket(sock);
		return false;
	}

	serverAddr.sin_family		= AF_INET;
	serverAddr.sin_port			= htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr	= inet_addr(SERVER_IP);

	retVal = connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	// 비동기 connect는 바로 return 되면서 WSAEWOULDBLOCK 에러 발생시킨다.
	if( retVal == SOCKET_ERROR && WSAEWOULDBLOCK != WSAGetLastError() )
	{
		wsprintf(szBuf, "[Connect Error!] %s : %d\n", SERVER_IP, SERVER_PORT);
		OutputDebugStr(szBuf);
		closesocket(sock);
		return false;
	}
	return true;
}


bool GetReg()
{
	HKEY			key;
	DWORD			dwDisp;
	DWORD			dwSize;

	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, REG_DIRECTORY, 0, NULL,
		REG_OPTION_VOLATILE, KEY_READ, NULL, &key, &dwDisp) != ERROR_SUCCESS)
		return false;

	dwSize = MAX_PATH;
	if(RegQueryValueEx(key, "directory", 0, NULL, (LPBYTE)szPath, &dwSize) != ERROR_SUCCESS)
		return false;

	RegCloseKey(key);

	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, REG_DIRECTORY, 0, NULL,
		REG_OPTION_VOLATILE, KEY_READ, NULL, &key, &dwDisp) != ERROR_SUCCESS)
		return false;

	dwSize = sizeof(dwSize);
	if(RegQueryValueEx(key, "version", 0, NULL, (LPBYTE)&dwClientVer, &dwSize) != ERROR_SUCCESS)
		return false;

	RegCloseKey(key);

	//
//	strcpy(szPath, "E:\\UpdateTest");
	//

	return true;
}

bool Send(WORD type, WORD size, void *buf)
{
	if(!sock)
		return false;

	char *temp = (char*)buf;

	m_pkDefault.dwProtocol = type;

	if(size)
		memcpy(m_pkDefault.strPacket, temp, size);

	m_pkDefault.dwSize = PK_HEADER_SIZE + size;

	int		r1 = 0, r2 = 0;
	int		fail_count = 0;

	while(true)
	{
		r2 = send(sock, (char*)&m_pkDefault, m_pkDefault.dwSize, 0);

		if(r2 != SOCKET_ERROR)
			r1 += r2;

		if(r1 == m_pkDefault.dwSize)
			break;

		fail_count++;

		if(fail_count > 10)
			return false;
	}
	return true;
}

void Recv()
{
	switch(m_pkDefault.dwProtocol)
	{
		case PL_UPDATESTART_REP:
			{
				PK_UPDATESTART_REP		*rep = (PK_UPDATESTART_REP*)m_pkDefault.strPacket;

				if(rep->bRemainUpdate)
				{
					PK_FILENAME_ASK		ask;

					total = rep->nTotalFile;
					cur = 0;

					char	szBuf[128];
					wsprintf(szBuf, "%d / %d", cur + 1, total);
					SetDlgItemText(hDlgMain, IDC_STATIC1, szBuf);

					strcpy(szURL, rep->szURL);
					ask.nCur = cur;
					dwServerVer = rep->nNewVer;
					Send(PL_FILENAME_ASK, sizeof(ask), &ask);
				}
				else
				{
					// release 후
					// 걍 게임 실행시키면 됨
					char	szTemp[MAX_PATH] = "";
					strcpy(szTemp, szPath);
					strcat(szTemp, "\\");
					strcat(szTemp, "SNUDiCE_Client.exe");// RunByUpdate");
//					strcat(szTemp, "notepad.exe");// RunByUpdate");

//					WinExec((LPCSTR)szPath, SW_SHOW);

					SHELLEXECUTEINFO		si;
					memset(&si, 0, sizeof(si));
					si.cbSize = sizeof(si);
					si.lpVerb = "open";
					si.lpFile = szTemp;
					si.lpParameters = "RunByUpdater";
					si.lpDirectory = szPath;
					si.nShow = SW_SHOWDEFAULT;

					ShellExecuteEx(&si);

					EndDialog(hDlgMain, IDOK);

// 					PROCESS_INFORMATION	pi;
// 					STARTUPINFO			sui;
// 
// 					memset(&sui, 0, sizeof(sui));
// 
// 					CreateProcess(szTemp, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sui, &pi);


				}
			}
			break;
		case PL_FILENAME_REP:
			{
				PK_FILENAME_REP		*rep = (PK_FILENAME_REP*)m_pkDefault.strPacket;

				char		szFolderCheck[MAX_PATH] = "";
				strcpy(szFolderCheck, szPath);
				strcat(szFolderCheck, "\\");

				string tempstr = rep->szPath;
				int	i;

				for(i = 0; i < tempstr.length(); i++)
				{
					if(tempstr[i] == '\\')
					{
						tempstr = tempstr.substr(i + 1, tempstr.length());
						break;
					}
				}
				strcat(szFolderCheck, tempstr.c_str());


				tempstr = szFolderCheck;
				for(i = tempstr.length() - 1; i >= 0; i--)
				{
					if(tempstr[i] == '\\')
					{
						tempstr = tempstr.substr(0, i);
						break;
					}
				}
				char	szBufMakeFolder[MAX_PATH];
				strcpy(szBufMakeFolder, tempstr.c_str());

				AutoFolderMake(szBufMakeFolder);
	
				char		szBufURL[MAX_PATH] = "";
				strcpy(szBufURL, szURL);
				strcat(szBufURL, rep->szPath);
				for(i = 0; i < strlen(szBufURL); i++)
				{
					if(szBufURL[i] == '\\')
						szBufURL[i] = '/';
				}

				if(HTTPDown(hDlgMain, szBufURL, szFolderCheck))
				{
					if(cur < total - 1)
					{
						cur++;
						PK_FILENAME_ASK		ask;
						ask.nCur = cur;
						char	szBuf[128];
						wsprintf(szBuf, "%d / %d", cur, total);
						SetDlgItemText(hDlgMain, IDC_STATIC1, szBuf);
						Send(PL_FILENAME_ASK, sizeof(ask), &ask);
					}
					else
					{
						// finish
						cur++;
						char	szBuf[128];
						wsprintf(szBuf, "%d / %d", cur, total);
						SetDlgItemText(hDlgMain, IDC_STATIC1, szBuf);

						// set new reg
						HKEY		key;
						DWORD		dwDisp;

						if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, REG_DIRECTORY, 0, NULL,
							REG_OPTION_VOLATILE, KEY_WRITE, NULL, &key, &dwDisp) != ERROR_SUCCESS)
							return;

						if(RegSetValueEx(key, "version", 0, REG_DWORD, (LPBYTE)&dwServerVer, sizeof(DWORD)) != ERROR_SUCCESS)
							return;

						RegCloseKey(key);

						char	szTemp[MAX_PATH] = "";
						strcpy(szTemp, szPath);
						strcat(szTemp, "\\");
						strcat(szTemp, "SNUDiCE_Client.exe");// RunByUpdate");

						SHELLEXECUTEINFO		si;
						memset(&si, 0, sizeof(si));
						si.cbSize = sizeof(si);
						si.lpVerb = "open";
						si.lpFile = szTemp;
						si.lpParameters = "RunByUpdater";
						si.lpDirectory = szPath;
						si.nShow = SW_SHOWDEFAULT;

						ShellExecuteEx(&si);

						EndDialog(hDlgMain, IDOK);
					}
				}
				else
				{
					MessageBox(NULL, "Error : 다운 실패", "Error", MB_OK);
				}
			}
			break;
			/*
		case PL_FILE_REP:
			{
				PK_FILE_REP		*rep = (PK_FILE_REP*)m_pkDefault.strPacket;

				fwrite(rep->szData, sizeof(BYTE), rep->dwSize, fp);
			}
			break;
		case PL_FILEEND_REP:
			{
				PK_FILEEND_REP	*rep = (PK_FILEEND_REP*)m_pkDefault.strPacket;
				fclose(fp);

				if(rep->bEnd || cur >= total - 1)
				{

				}
				else
				{
					cur++;
					char	szBuf[128];
					wsprintf(szBuf, "%d / %d", cur + 1, total);
					SetDlgItemText(hDlgMain, IDC_STATIC1, szBuf);

					PK_FILESTART_ASK		ask;
					ask.nCur = cur;
					Send(PL_FILESTART_ASK, sizeof(ask), &ask);
				}
			}
			break;
			*/

	}
}

void Receive(LPARAM lParam)
{
	if(!SocketErrorMessage(lParam))
		return;

	char	szBuf[256];
//	int		retVal;

	switch( WSAGETSELECTEVENT(lParam) )
	{
		case FD_CONNECT:
			wsprintf(szBuf, "[Connect] %s : %d\n",
				inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));
			OutputDebugStr(szBuf);
			break;
		case FD_READ:
			ReadPacket();
			break;
		case FD_WRITE:
			break;
		case FD_CLOSE:
			wsprintf(szBuf, "[Close] %s : %d\n",
				inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));
			OutputDebugStr(szBuf);
			break;
	}
}

void ReadPacket()
{
	int		r1 = 0, r2 = 0;
	int		fail_count = 0;

	r2 = recv(sock, (char*)&m_pkDefault, PK_HEADER_SIZE, 0);
	if(r2 == SOCKET_ERROR)
		return;
	if(r2 == 0)
		return;

	r1 += PK_HEADER_SIZE;

	while(true)
	{
		r2 = recv(sock, m_pkDefault.strPacket, m_pkDefault.dwSize - PK_HEADER_SIZE, 0);

		if(r2 != SOCKET_ERROR)
			r1 += r2;

		if(r1 == m_pkDefault.dwSize)
			break;

		fail_count++;

		if(fail_count > 10)
			break;
	}

	if(fail_count <= 10)
		Recv();
}

bool SocketErrorMessage(LPARAM lParam)
{
	char	szBuf[256];
	//	int		retVal;

	if( WSAGETSELECTERROR(lParam) )
	{
		if( ( WSAGETSELECTERROR(lParam) == WSAECONNREFUSED ) ||		// 10061 :Connection refused. 서버 프로그램이 실행 X
			( WSAGETSELECTERROR(lParam) == WSAENETUNREACH ) ||		// 10051 :Network is unreachable.
			( WSAGETSELECTERROR(lParam) == WSAETIMEDOUT ) )//||		// 10060 :Connection timed out.
		{
			EndDialog(hDlgMain, IDOK);
			return false;
		}
		closesocket(sock);
		if( WSAGETSELECTERROR(lParam) == WSAECONNABORTED)			// 10053 :서버가 종료됨.. 아마도
		{
			OutputDebugStr("서버와의 연결이 끊김\n");
			EndDialog(hDlgMain, IDOK);
			return false;
		}
		else
			wsprintf(szBuf, "WM_SOCKET error: %d\n", WSAGETSELECTERROR(lParam));
		OutputDebugStr(szBuf);
		EndDialog(hDlgMain, IDOK);
		return false;
	}
	return true;
}

void AutoFolderMake(char *szPath)
{
	char	szFolder[MAX_PATH];
	char	*p = szPath;
	char	*pFolder = szFolder;

	while(*p)
	{
		if(('\\' == *p) || ('/') == *p)
		{
			if(':' != *(p - 1))
			{
				CreateDirectory(szFolder, NULL);
			}
		}
		*pFolder++ = *p++;
		*pFolder = '\0';
	}
	CreateDirectory(szFolder, NULL);
}

bool HTTPDown(HWND hWnd,  char *url, char *path)
{
	HINTERNET	hInternet, hURL;
	HANDLE		hFile;
	DWORD		Size;
	DWORD		dwRead, dwWritten, Recv = 0;
	char		szBuf[100000];

	// 인터넷 연결
	hInternet = InternetOpen("SNUDICE", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(!hInternet)
		return false;

	// open url
	hURL = InternetOpenUrl(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);

if(!hURL)
	{
		InternetCloseHandle(hInternet);
		return false;
	}

	hFile = CreateFile(path, GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	do 
	{
		// 다운로드 받아서 로컬 파일에 기록
		InternetQueryDataAvailable(hURL, &Size, 0, 0);
		InternetReadFile(hURL, szBuf, Size, &dwRead);
		WriteFile(hFile, szBuf, dwRead, &dwWritten, NULL);

		Recv += dwWritten;
	} while (dwRead != 0);

	InternetCloseHandle(hURL);
	InternetCloseHandle(hInternet);
	CloseHandle(hFile);

	return true;

}