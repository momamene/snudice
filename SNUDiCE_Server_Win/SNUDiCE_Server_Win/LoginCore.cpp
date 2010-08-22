#include "LoginCore.h"
#include "MainWin.h"
#include "PlayerContainer.h"
#include "MysqlDB.h"
#include "ChannelContainer.h"

static gLoginCore s_LoginCore;

gLoginCore *gLoginCore::GetIF()
{
	return &s_LoginCore;
}

gLoginCore::gLoginCore()
{

}

gLoginCore::~gLoginCore()
{

}

void gLoginCore::Put(char* id,char* pw) 
{

	gMysql::GetIF()->put(id,pw);
}

USER* gLoginCore::GetID(char* id)
{

	return gMysql::GetIF()->get(id);	
}



bool gLoginCore::SetUp()
{

	//for test. default 계정
	USER*	user;
	char	buf[1024];

	Put("test1","1111");
	Put("test2","1111");

	return true;
}

void gLoginCore::Release()
{
	/*
	USER	*userTemp;

	for(USER_LIST::iterator it = m_UserList.begin(); it != m_UserList.end(); it++)
	{
		userTemp = (USER*)(*it);
		delete userTemp;
		userTemp = NULL;
	}
	m_UserList.clear();
	*/
}

// packet
void gLoginCore::pk_login_ask(PK_DEFAULT *pk, SOCKET sock)
{
	PK_LOGIN_ASK		ask;		//from client

	// for print
	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_LOGIN_ASK*)pk->strPacket);

	sprintf(buf,"[PK_LOGIN_REP] %s\tid : %s\t pw : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID, ask.szPW);
	OutputDebugString(buf);

	PK_LOGIN_REP	rep;
	USER			*user;
	bool			bCanIn = false;

	user = GetID(ask.szID);

	if(user==NULL) {
		rep.error = ELE_NOID; 
	}
	else { 
		if(strcmp(user->szPW,ask.szPW)!=0) {
			rep.error	= ELE_PWERROR;
		}
		else {

			if(gPlayerContainer::GetIF()->isExistedPlayer(user->szID)) {
				rep.error = ELE_OVERCONNECT;
			}
			else {
				// gChannelContainer start
				bCanIn = gChannelContainer::GetIF()->Join(user->szID);

				if(!bCanIn) {
					rep.error = ELE_USEROVER;
				}
				else {
					int finded = gChannelContainer::GetIF()->FindPlayer(user->szID);
					if(finded==-1) {
						// 만약 finded가 -1이 나온다면 치명적인 오류.
						// 오류 체킹을 하고 있음.
						OutputDebugString("aftef USEROVER 치명적인 오류\n");
					}
					for(int i = 0 ; i < CHANNELMAX ; i++)
						gChannelContainer::GetIF()->debuger(i+1);	// 1부터 6까지 물어봐야지.
					// gChannelContainer end
					
					rep.channel = gChannelContainer::GetIF()->m_channelArray[finded-1];
					
					rep.error = ELE_SUCCESS;
					strcpy(rep.player.szID,user->szID);
					rep.player.coreWhere = ECM_BATTLENET;
					rep.player.nCoreFlag = 0;
					rep.player.sock = sock;
					gPlayerContainer::GetIF()->AddPlayer(&rep.player);
				}
			}
		}
	}
	
	gMainWin::GetIF()->Send(PL_LOGIN_REP, sizeof(rep), &rep, sock);
}
