#include "ChannelCore.h"
#include "ChannelContainer.h"
#include "PlayerContainer.h"
#include "MainWin.h"

static gChannelCore s_ChannelCore;

gChannelCore *gChannelCore::GetIF()
{
	return &s_ChannelCore;
}

gChannelCore::gChannelCore()
{

}

void gChannelCore::Release()
{

}

void gChannelCore::pk_channelrefresh_rep (int channel) {
	PK_CHANNELREFRESH_REP repOther;
	
	repOther.channel = gChannelContainer::GetIF()->m_channelArray[channel];
	//char getID [IDLENGTH];
	SOCKET getSock;
	bool bTemp;
	bool bTem;

//	char tempLoadID[IDLENGTH];

	for(int j = 0 ; j < CHANNELUSERMAX ; j++) {
		if(gChannelContainer::GetIF()->m_isExisted[channel][j]
			/*strcmp(gChannelContainer::GetIF()->m_channelArray[channel].szUserInCh[j],rep.player.szID)!=0*/) {
				
				bTem = gPlayerContainer::GetIF()->FindSocketFromID
					(gChannelContainer::GetIF()->m_channelArray[channel].szUserInCh[j],&getSock);
				
				if(!bTem) {
					OutputDebugString("getSocket Error \n");
				}

				bTemp = gMainWin::GetIF()->Send(PL_CHANNELREFRESH_REP, sizeof(repOther), &repOther, getSock);
				
				if(!bTemp) {
					OutputDebugString("Send Error \n");
				}
		}
	}
}

void gChannelCore::pk_channelchange_ask (PK_DEFAULT *pk, SOCKET sock)
{
	PK_CHANNELCHANGE_ASK		ask;		//from client
	PK_CHANNELCHANGE_REP		rep;		//from client


	// for print (무슨 말이여 이게)
	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_CHANNELCHANGE_ASK*)pk->strPacket);

	sprintf(buf,"[PK_CHANNELCHANGE_ASK] %s\tid : %s\t message : %d\n", inet_ntoa(clientAddr.sin_addr), ask.szID, ask.nChannel);
	OutputDebugString(buf);

	
	if(gChannelContainer::GetIF()->RoomClientNum(ask.nChannel-1)>=CHANNELUSERMAX) {
		rep.error = ECE_CHANNELISOVER;
	}
	else {
		int channelBefore = gChannelContainer::GetIF()->FindPlayer(ask.szID);
		if(channelBefore == -1) {
			// 에러 처리
		}
		else {
			rep.error = ECE_SUCCESS;
			
			gChannelContainer::GetIF()->DeletePlayer(ask.szID);
			gChannelContainer::GetIF()->AddPlayer(ask.nChannel-1,ask.szID);
			rep.channel = gChannelContainer::GetIF()->m_channelArray[ask.nChannel-1];
			pk_channelrefresh_rep (channelBefore);
			pk_channelrefresh_rep (ask.nChannel-1);
		}
	}	
	gMainWin::GetIF()->Send(PL_CHANNELCHANGE_REP, sizeof(rep), &rep, sock);
	gChannelContainer::GetIF()->fullDebuger();

}


