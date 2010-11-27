#include "MessageCore.h"
#include "PlayerContainer.h"
#include "ChannelContainer.h"
#include "MainWin.h"
#include "MysqlDB.h"
#include "GamePlayerContainer.h"

#include <sstream>

static gMessageCore s_MessageCore;

gMessageCore *gMessageCore::GetIF()
{
	return &s_MessageCore;
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
//	else if(ask.szMsg[0]=='/') {	//수정 임시디버그용
//		debuger(ask.szMsg,ask.szID);
//	}
	else if(mode==ECM_BATTLENET || mode==ECM_ROOM || mode==ECM_GAME) {
		//int nChannelIndex = gCC->FindPlayer(ask.szID);
		strcpy(rep.szID,ask.szID);
		strcpy(rep.szMsg,ask.szMsg);
		gPC->SendSelect(PL_MESSAGE_REP,sizeof(PK_MESSAGE_REP),&rep,mode,flag);
	}
	else {
		// error
		OutputDebugString("(f)[pk_message_ask] Error in mode Problem\n");
	}
}

void gMessageCore::debuger(char* str,char* szID) {
	char szStr1[128];
	char szStr2[128];
	int nStr2;

	gGamePlayerContainer *gGPCt = gGamePlayerContainer::GetIF();

	memset(szStr1,0,128*sizeof(char));
	memset(szStr2,0,128*sizeof(char));

	stringstream ss;
	ss << str;

	ss >> szStr1;
	int n = strlen(szStr1);
	for(int i = 0 ; i < n-1 ; i++) {
		szStr1[i] = szStr1[i+1];
	}
	szStr1[n-1]='\0';

	ss >> szStr2;
	nStr2 = atoi(szStr2);

	if(strcmp(szStr1,"move")==0) 
		gGPCt->debuger_move(nStr2,szID);
	else if(strcmp(szStr1,"card")==0) 
		gGPCt->debuger_card(nStr2,szID);
	else if (strcmp(szStr1,"turn")==0)
		gGPCt->debuger_turn(szID);
}



void gMessageCore::pk_whisper_ask(PK_DEFAULT *pk, SOCKET sock)
{
	PK_WHISPER_ASK		ask;		//from client

	// for print
	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_WHISPER_ASK*)pk->strPacket);

	wsprintf(buf,"[PK_WHISPER_ASK] %s\tid : %s\t toId %s\tmessage : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szFromID,ask.szToID, ask.szComment);
	OutputDebugString(buf);


	PK_MESSAGE_REP rep1,rep2;	//rep1 : 보낸놈 rep2 : 받는놈

	SOCKET sendsock;	//보내려는 소켓 , toID로부터 구한다.
	PLAYER toPlayer = gPlayerContainer::GetIF()->GetPlayerFromID(ask.szToID);
	sendsock = toPlayer.sock;
	
	wsprintf(buf,"[PK_WHISPER_REP] %s\t \n", inet_ntoa(clientAddr.sin_addr));
	OutputDebugString(buf);

	strcpy(rep1.szID,"To ");
	strcat(rep1.szID,ask.szToID);
	strcpy(rep1.szMsg,ask.szComment);
	gMainWin::GetIF()->Send(PL_MESSAGE_REP, sizeof(rep1), &rep1, sock);

	strcpy(rep2.szID,"From ");
	strcat(rep2.szID,ask.szFromID);
	strcpy(rep2.szMsg,ask.szComment);
	gMainWin::GetIF()->Send(PL_MESSAGE_REP, sizeof(rep2), &rep2, sendsock);

}
