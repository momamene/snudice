#include "MessageCore.h"
#include "PlayerContainer.h"
#include "ChannelContainer.h"
#include "MainWin.h"
#include "MysqlDB.h"

static gMessageCore s_MessageCore;

gMessageCore *gMessageCore::GetIF()
{
	return &s_MessageCore;
}

gMessageCore::gMessageCore()
{
//	gMysql::GetIF()->init();
}

gMessageCore::~gMessageCore()
{

}

bool gMessageCore::SetUp()
{
	return true;
}

void gMessageCore::Release()
{
	gMysql::GetIF()->release();
}

void gMessageCore::pk_message_ask(PK_DEFAULT *pk, SOCKET sock)
{
	PK_MESSAGE_ASK		ask;		//from client
	gPlayerContainer	*gPC	= gPlayerContainer::GetIF();
	gChannelContainer	*gCC	= gChannelContainer::GetIF();
	PLAYER*				temp;

	// for print
	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_MESSAGE_ASK*)pk->strPacket);

	sprintf(buf,"[PK_MESSAGE_ASK] %s\tid : %s\t message : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID, ask.szMsg);
	OutputDebugString(buf);

	PK_MESSAGE_REP	rep;
	eCOREMODE mode;
	int flag;

	mode = gPC->GetMode(ask.szID);
	flag = gPC->GetCoreFlag(ask.szID);
	if( mode==-1 || flag==-1 ) {
		// error
	}
	else if(mode==ECM_BATTLENET || mode==ECM_ROOM) {
		//int nChannelIndex = gCC->FindPlayer(ask.szID);
		strcpy(rep.szID,ask.szID);
		strcpy(rep.szMsg,ask.szMsg);
		gPC->SendSelect(PL_MESSAGE_REP,sizeof(PK_MESSAGE_REP),&rep,mode,flag);
	}
	/*
	else if(mode==ECM_ROOM) {
		strcpy(rep.szID,ask.szID);
		strcpy(rep.szMsg,ask.szMsg);
		gPC->SendSelect(PL_MESSAGE_REP,sizeof(PK_MESSAGE_REP),&rep,ECM_ROOM,flag);
	}
	*/
	else {
		// error
		OutputDebugString("(f)[pk_message_ask] Error in mode Problem\n");
	}
}