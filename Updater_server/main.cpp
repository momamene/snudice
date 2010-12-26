#include "network.h"
#include <vector>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4669)	// _CRT_SECURE_NO_WARNINGS

//#define DATABASEPATH		"E:\\Project N\\Release\\SNUDiCE_Update_Server"

SOCKET		listen_sock;

using namespace std;


DWORD		dwVer = 0;

struct UPDATEFILELIST
{
	DWORD			dwVersion;
	vector<string>	vFile;
};
vector<string>			vVersionList;
vector<UPDATEFILELIST>	vFileList;

struct UPDATEINFO
{
	vector<string>		vUpdateList;
	int					nCur;
	SOCKET				sock;
};

vector<UPDATEINFO>		vUpdate;

char	szCurrentPath[MAX_PATH];

bool	SetUpFolderList();
void	FindFile(char* path, vector<string> *strlist);

bool	SetUpSocket();
void	err_quit(char *msg);					// 소켓 함수 오류 출력후 종료
void	err_display(char *msg);					// 소켓 함수 오류 출력
DWORD WINAPI ProcessClient(LPVOID arg);				// server <-> client 간 통신. 스레드

bool	Send(DWORD type, DWORD size, void *buf, SOCKET sock);
void	Recv(PK_DEFAULT *pk, SOCKET sock);
void	GetUpdateList(vector<string> &str, DWORD dwClientVer);

bool	isExist(string str, vector<string> &list);

int main()
{
	if(!SetUpFolderList())
		return 0;

	if(!SetUpSocket())
		return 0;

	// listen
	SOCKET			client_sock;
	SOCKADDR_IN		clientAddr;
	int				addrLen;
	//	int				retVal;
	char			szBuf[BUFFERSIZE + 1];		// 왜 + 1인가??
	HANDLE			hThread;
	DWORD			dwThreadID;

	ZeroMemory(&clientAddr, sizeof(SOCKADDR_IN));

	MSG		Msg;
	char	buf[1024];

	OutputDebugString("Server Start\n");

	while(true)
	{
		// accept()

		addrLen = sizeof(clientAddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientAddr, &addrLen);
		if(client_sock == INVALID_SOCKET)
		{
			err_display("accept()");
			continue;
		}
		sprintf(buf,"\n[TCP Server] Client Connect : IP = %s\t Port = %d\n",
			inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		OutputDebugString(buf);

		// make thread
		hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)client_sock, 0, &dwThreadID);

		if(hThread == NULL) 
			OutputDebugString("Server-Client Thread failed\n");
		else
			CloseHandle(hThread);
	}


	return 0;
}

bool SetUpFolderList()
{
	HANDLE				hSrch;
	WIN32_FIND_DATA		wfd;
	TCHAR				szFile[MAX_PATH];
//	char				szPath[MAX_PATH] = DATABASEPATH;
	char				szPath[MAX_PATH];
	BOOL				bResult = TRUE;

	GetCurrentDirectory(MAX_PATH, szCurrentPath);

	//
//	strcpy(szCurrentPath, "E:\\Project N\\Release\\SNUDiCE_Update_Server");
	//

	strcpy(szPath, szCurrentPath);

	strcat(szPath, "\\*.*");
	hSrch = FindFirstFile(szPath, &wfd);
	if(hSrch == INVALID_HANDLE_VALUE)
	{
		printf("No Any Files\n");
		return false;
	}

	while(bResult)
	{
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(strlen(wfd.cFileName) > 3)
			{
				printf("%s\n", wfd.cFileName);
				string		add = wfd.cFileName;
				vVersionList.push_back(add);
			}
		}
		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);

	int			i;
//	char		szTemp[MAX_PATH] = DATABASEPATH;
	char		szTemp[MAX_PATH];

	strcpy(szTemp, szCurrentPath);

	for(i = 0; i < vVersionList.size(); i++)
	{
		char	szTemp2[MAX_PATH] = "";
		strcpy(szTemp2, szTemp);
		strcat(szTemp2, "\\");
		strcat(szTemp2, vVersionList[i].c_str());
		strcat(szTemp2, "\\*.*");
		UPDATEFILELIST		upd;
		int		ver = atoi(vVersionList[i].c_str());
		upd.dwVersion	= (DWORD)ver;
		FindFile(szTemp2, &upd.vFile);
		vFileList.push_back(upd);
	}

	int		ver = atoi(vVersionList[vVersionList.size() - 1].c_str());
	dwVer = (DWORD)ver;

	return true;
}

void FindFile(char *path, vector<string> *strlist)
{
	HANDLE				hSrch;
	WIN32_FIND_DATA		wfd;
	char				szFile[MAX_PATH];
	BOOL				bResult = TRUE;
	char				szDrive[_MAX_DRIVE];
	char				szDir[MAX_PATH];
	char				szNewPath[MAX_PATH];

	hSrch = FindFirstFile(path, &wfd);
	if(hSrch == INVALID_HANDLE_VALUE)
		return;

	_splitpath(path, szDrive, szDir, NULL, NULL);
	while(bResult)
	{
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(strcmp(wfd.cFileName, ".") && strcmp(wfd.cFileName, ".."))
			{
				sprintf(szNewPath, "%s%s%s\\*.*", szDrive, szDir, wfd.cFileName);
				FindFile(szNewPath, strlist);
			}
		}
		else
		{
			sprintf(szFile, "%s%s%s", szDrive, szDir, wfd.cFileName);
			//printf("%s\n", wfd.cFileName);
			string	add = szFile;
			add = add.substr(strlen(szCurrentPath) + 1, add.length());
			strlist->push_back(add);
			
		}
		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);
}


bool SetUpSocket()
{
	int		retVal;

	// Winsock 초기화
	WSADATA	wsa;

	if(WSAStartup(WINSOCK_VERSION_2_2, &wsa) != 0)	// WSAStartup은 리턴값만으로 오류를 처리한다.
	{
		MessageBox(NULL, "WinSock 초기화 실패", "Error", MB_OK);
		return false;
	}

	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);	// af ; 주소체계, type ; 소켓타입, protocol ; 프로토콜
	// AF_INET, SOCK_STREAM -> TCP	; 신뢰성, 연결형 프로토콜
	//			SOCK_DGRAM	-> UDP	; 비신뢰, 비연결	"

	if(listen_sock == INVALID_SOCKET)
		err_quit("socket()");

	// bind()
	SOCKADDR_IN		serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family		= AF_INET;					//hton ; host bytes to network bytes(Big Endian)
	serverAddr.sin_port			= htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr	= inet_addr(SERVER_IP);
	retVal = bind(listen_sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));


	if(retVal == SOCKET_ERROR)
		err_quit("bind()");

	// listen()
	retVal = listen(listen_sock, SOMAXCONN);
	if(retVal == SOCKET_ERROR)
		err_quit("listen()");

	return true;

}

void err_quit(char *msg)
{
	LPVOID	lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(-1);

}

void err_display(char *msg)
{
	LPVOID	lpMsgBuf;
	char	buf [1024];

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	sprintf(buf,"[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	OutputDebugString(buf);

	LocalFree(lpMsgBuf);

}

DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET			client_sock = (SOCKET)arg;
	SOCKADDR_IN		clientAddr;
	char			szBuf[BUFFERSIZE + 1];
	int				addrLen;
	int				retVal;
	PK_DEFAULT		pkDefault;

	// 클라이언트 정보 얻기
	addrLen = sizeof(clientAddr);
	getpeername(client_sock, (SOCKADDR*)&clientAddr, &addrLen);

	while(true)
	{
		int		r1 = 0, r2 = 0;
		int		fail_count = 0;

		retVal = recv(client_sock, (char*)&pkDefault, PK_HEADER_SIZE, 0);
		//OutputDebugString("a.");
		if(retVal == SOCKET_ERROR)	// 임시방편
			break;
		//	continue;
		if(retVal == 0)		// 보통 종료할 때 이 메세지가 뜨던데?
			break;

		r1 += PK_HEADER_SIZE;

		while(true)
		{
			r2 = recv(client_sock, pkDefault.strPacket, pkDefault.dwSize - PK_HEADER_SIZE, 0);
//			OutputDebugString("b\n");

			if(r2 != SOCKET_ERROR)
				r1 += r2;

			if(r1 == pkDefault.dwSize)
				break;

			fail_count++;

			if(fail_count > 10)
				break;
		}

		if(fail_count <= 10)
			Recv(&pkDefault, client_sock);
	}

	vector<UPDATEINFO>::iterator	it;
	for(it = vUpdate.begin(); it != vUpdate.end(); it++)
	{
		if(it->sock == client_sock)
		{
			vUpdate.erase(it);
			break;
		}
	}

	closesocket(client_sock);
	return 0;
}

bool Send(DWORD type, DWORD size, void *buf, SOCKET sock)
{
	PK_DEFAULT		pk;

	if(!sock) {
		OutputDebugString("gMainWin::Send Sock fail error\n");
		return false;
	}
	char *temp = (char*)buf;

	pk.dwProtocol = type;

	if(size)
		memcpy(pk.strPacket, temp, size);

	pk.dwSize = PK_HEADER_SIZE + size;

	int		r1 = 0, r2 = 0;
	int		fail_count = 0;

	while(true)
	{
		r2 = send(sock, (char*)&pk, pk.dwSize, 0);

		if(r2 != SOCKET_ERROR)
			r1 += r2;

		if(r1 == pk.dwSize)
			break;

		fail_count++;

		if(fail_count > 10) {
			OutputDebugString("gMainWin::Send fail count error\n");
			return false;
		}
	}
	return true;
}

void Recv(PK_DEFAULT *pk, SOCKET sock)
{
	switch(pk->dwProtocol)
	{
		case PL_UPDATESTART_ASK:
			{
				PK_UPDATESTART_ASK		*ask = (PK_UPDATESTART_ASK*)pk->strPacket;

				PK_UPDATESTART_REP	rep;
				if(ask->dwVersion < dwVer)
				{
					rep.bRemainUpdate = true;
				}
				else
				{
					rep.bRemainUpdate = false;
				}

				if(rep.bRemainUpdate)
				{
					UPDATEINFO		info;
					info.nCur = 0;
					info.sock = sock;
					info.vUpdateList.clear();
					GetUpdateList(info.vUpdateList, ask->dwVersion);
					vUpdate.push_back(info);
					rep.nTotalFile = info.vUpdateList.size();
					strcpy(rep.szURL, FILEPATH_UPDATE);
					rep.nNewVer = dwVer;
				}

				Send(PL_UPDATESTART_REP, sizeof(rep), &rep, sock);
			}
			break;
		case PL_FILENAME_ASK:
			{
				PK_FILENAME_ASK	*ask = (PK_FILENAME_ASK*)pk->strPacket;
				for(int i = 0; i < vUpdate.size(); i++)
				{
					if(vUpdate[i].sock == sock)
					{
						PK_FILENAME_REP		rep;
						string	path = vUpdate[i].vUpdateList[ask->nCur];
						strcpy(rep.szPath, path.c_str());
						Send(PL_FILENAME_REP, sizeof(rep), &rep, sock);
					}
				}
			}
			break;
	}
}

void GetUpdateList(vector<string> &str, DWORD dwClientVer)
{
	int		i, j;

	for(i = 0; i < vFileList.size(); i++)
	{
		if(vFileList[i].dwVersion <= dwClientVer)
			continue;

		for(j = 0; j < vFileList[i].vFile.size(); j++)
		{
			string	temp = vFileList[i].vFile[j];
			if(!isExist(temp, str))
				str.push_back(temp);
		}
	}
}

bool isExist(string str, vector<string> &list)
{
// 	string	path = szCurrentPath;
// 
// 	str = str.substr(path.length() + 1, str.length());
// 	int cur = str.find("\\", 0);
// 	str = str.substr(cur + 1, str.length());

	int cur;

	for(int i = 0; i < list.size(); i++)
	{
		cur = list[i].find(str, 0);
		if(cur != -1)
			return true;
	}
	return false;
}