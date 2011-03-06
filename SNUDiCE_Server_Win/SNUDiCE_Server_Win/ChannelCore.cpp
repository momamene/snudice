#include "ChannelCore.h"
#include "RoomCore.h"
#include "ChannelContainer.h"
#include "PlayerContainer.h"
#include "MainWin.h"
#include "const.h"

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
					gMainWin::GetIF()->LogWrite("getSocket Error \n");
				}

				bTemp = gMainWin::GetIF()->Send(PL_CHANNELREFRESH_REP, sizeof(repOther), &repOther, getSock);
				
				if(!bTemp) {
					gMainWin::GetIF()->LogWrite("Send Error \n");
				}
		}
	}
}

//수정사항, ㄱㄱ!
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



	wsprintf(buf,"[PK_CHANNELCHANGE_ASK] %s\tid : %s\t message : %d\n", inet_ntoa(clientAddr.sin_addr), ask.szID, ask.nChannel);
	gMainWin::GetIF()->LogWrite(buf);

	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	gRoomCore *gRC = gRoomCore::GetIF();

	int channelBefore = gChannelContainer::GetIF()->FindPlayer(ask.szID);
	switch(gPC->GetMode(ask.szID))	{
		case ECM_BATTLENET : 				case ECM_ROOMJOIN :
			if(channelBefore == -1) {
				// 에러 처리
				gMainWin::GetIF()->LogWrite("(f)[pk_channelchange_ask] Cannot Find Player Error\n");
			}
			else {
				if(gChannelContainer::GetIF()->RoomClientNum(ask.nChannel-1)>=CHANNELUSERMAX) {
					rep.error = ECE_CHANNELISOVER;
				}	else	{
					rep.error = ECE_SUCCESS;
					gChannelContainer::GetIF()->DeletePlayer(ask.szID);
					gChannelContainer::GetIF()->AddPlayer(ask.nChannel-1,ask.szID);
					rep.channel = gChannelContainer::GetIF()->m_channelArray[ask.nChannel-1];
					pk_channelrefresh_rep (channelBefore);
					pk_channelrefresh_rep (ask.nChannel-1);
					gPC->PutCoreFlag(ask.szID,ask.nChannel-1);
					gPC->PutMode(ask.szID,ECM_BATTLENET);
					gRC->SendRoomListCauseChange(ask.nChannel-1);
				}
			}
			break;
		case ECM_ROOMMAKE :	
			break;
		case ECM_ROOM : case ECM_GAME :
			gRC->ExitTheRoom(ask.szID);
			gPC->PutMode(ask.szID,ECM_BATTLENET);
			gPC->PutBoolReady(ask.szID,false);
			gPC->PutClassType(ask.szID,CLASS_NONE);
			
			int		repChannel = ask.nChannel - 1;
			
			while(gChannelContainer::GetIF()->RoomClientNum(repChannel)>=CHANNELUSERMAX)	{
				repChannel ++ ;
				if (repChannel > CHANNELMAX)	//수정, 만약 사람꽉차면 뻑나겠지,, 하지만 그럴일이....ㅜ.ㅡ;;
					repChannel = 0 ;
			}
			
			gChannelContainer::GetIF()->AddPlayer(repChannel,ask.szID);
			rep.channel = gChannelContainer::GetIF()->m_channelArray[repChannel];
			gPC->PutCoreFlag(ask.szID,repChannel);
			gRC->SendRoomListCauseChange(repChannel);
			pk_channelrefresh_rep (repChannel);
			break;
	}

	gMainWin::GetIF()->Send(PL_CHANNELCHANGE_REP, sizeof(rep), &rep, sock);
	gChannelContainer::GetIF()->fullDebuger();

}

