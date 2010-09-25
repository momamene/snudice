#include "LoginCore.h"
#include "MainWin.h"
#include "PlayerContainer.h"
#include "MysqlDB.h"
#include "ChannelContainer.h"
#include "ChannelCore.h"

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
	Put("test3","1111");
	Put("test4","1111");
	Put("test5","1111");
	Put("test6","1111");
	Put("test7","1111");
	Put("test8","1111");
	Put("test9","1111");
	Put("test10","1111");
	Put("test11","1111");
	Put("test12","1111");
	Put("test13","1111");
	Put("test14","1111");
	Put("test15","1111");
	Put("test16","1111");
	Put("test17","1111");
	Put("test18","1111");
	Put("test19","1111");
	Put("test20","1111");
	Put("빅토리아","1111");
	Put("장연수","1111");
	Put("sylairon","1111");
	Put("장난죄송","1111");
	Put("운영자","1111");

	return true;
}

void gLoginCore::Release()
{

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
	int finded;

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
					finded = gChannelContainer::GetIF()->FindPlayer(user->szID);
					if(finded==-1) {
						// 만약 finded가 -1이 나온다면 치명적인 오류.
						// 오류 체킹을 하고 있음.
						OutputDebugString("aftef USEROVER 치명적인 오류\n");
					}
						gChannelContainer::GetIF()->fullDebuger();	// 1부터 6까지 물어봐야지.
					// gChannelContainer end

					
					rep.channel = gChannelContainer::GetIF()->m_channelArray[finded];
					
					rep.error = ELE_SUCCESS;
					

					strcpy(rep.player.szID,user->szID);
					rep.player.classtype = CLASS_NONE;
					rep.player.coreWhere = ECM_BATTLENET;
					rep.player.nCoreFlag = 0;
					rep.player.sock = sock;
					rep.player.bReady = false;
					
					gPlayerContainer::GetIF()->AddPlayer(&rep.player);

				}
			}
		}
	}

	gMainWin::GetIF()->Send(PL_LOGIN_REP, sizeof(rep), &rep, sock);
	if(rep.error==ELE_SUCCESS)
		gChannelCore::GetIF()->pk_channelrefresh_rep(rep.channel.nChannelNum-1);
	


}
