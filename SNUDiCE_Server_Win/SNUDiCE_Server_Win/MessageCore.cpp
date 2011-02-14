#include "MessageCore.h"
#include "PlayerContainer.h"
#include "ChannelContainer.h"
#include "MainWin.h"
#include "MysqlDB.h"
#include "GamePlayerContainer.h"

#include <sstream>

#define GAMEPLAY_DEBUGER

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
	gMainWin::GetIF()->LogWrite(buf);

	PK_MESSAGE_REP	rep;
	eCOREMODE mode;
	int flag;

	mode = gPC->GetMode(ask.szID);
	flag = gPC->GetCoreFlag(ask.szID);
	if( mode==-1 || flag==-1 ) {
		// error
	}
	else if(ask.szMsg[0]=='/') {	//���� �ӽõ���׿�
		command(ask.szMsg,ask.szID);
	}
	else if(mode==ECM_BATTLENET || mode==ECM_ROOM || mode==ECM_GAME) {
		//int nChannelIndex = gCC->FindPlayer(ask.szID);
		strcpy(rep.szID,ask.szID);
		strcpy(rep.szMsg,ask.szMsg);
		gPC->SendSelect(PL_MESSAGE_REP,sizeof(PK_MESSAGE_REP),&rep,mode,flag);
	}
	else {
		// error
		gMainWin::GetIF()->LogWrite("(f)[pk_message_ask] Error in mode Problem\n");
	}
}

void gMessageCore::command(char* str,char* szID) {
	char szStr1[128];
	char szStr2[128];
	char szStr3[128];
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

	if(strcmp(szStr1,"w")==0)	{
		if (!strcmp(szStr2 , szID))	{	//���� ������ �Ӹ� -��-;
			msg_failMessage(szID , "�������� ������ �ڽſ��� �ӼӸ��� �� �� �����ϴ�.");
		}
		else	{
			char szStr4[1024] = {0,};
			do 
			{
				ss >> szStr3;
				strcat(szStr4 , szStr3);
				strcat(szStr4 , " ");
			} while (strcmp(szStr3 , ""));
			strcat(szStr4 , szStr3);
			msg_whisper(szID , szStr2 , szStr4);
		}
		return;
	}
#ifdef GAMEPLAY_DEBUGER
	nStr2 = atoi(szStr2);
	if(strcmp(szStr1,"move")==0) 
		gGPCt->debuger_move(nStr2,szID);
	else if(strcmp(szStr1,"card")==0) 
		gGPCt->debuger_card(nStr2,szID);
	else if (strcmp(szStr1,"turn")==0)
		gGPCt->debuger_turn(szID);
#endif
}

void gMessageCore::msg_whisper(char	 szToID[IDLENGTH] , char szFromID[IDLENGTH] , char szComment[MSGLENGTH] )
{

	PK_MESSAGE_REP rep1,rep2;	//rep1 : ������ rep2 : �޴³�
	
	char				buf [1024];

	SOCKET sock , sendsock;	//�������� ���� , toID�κ��� ���Ѵ�.
	
	sock		=	gPlayerContainer::GetIF()->GetPlayerFromID(szToID).sock;
	sendsock	=	gPlayerContainer::GetIF()->GetPlayerFromID(szFromID).sock;
	
	strcpy(rep1.szID,"To ");
	strcat(rep1.szID,szFromID);
	strcpy(rep1.szMsg,szComment);
	gMainWin::GetIF()->Send(PL_MESSAGE_REP, sizeof(rep1), &rep1, sock);

	strcpy(rep2.szID,"From ");
	strcat(rep2.szID,szToID);
	strcpy(rep2.szMsg,szComment);
	gMainWin::GetIF()->Send(PL_MESSAGE_REP, sizeof(rep2), &rep2, sendsock);

}


void gMessageCore::msg_failMessage(char	 szToID[IDLENGTH] , char szComment[MSGLENGTH] )
{

	PK_MESSAGE_REP rep1,rep2;	//rep1 : ������ rep2 : �޴³�

	char				buf [1024];

	SOCKET sock		=	gPlayerContainer::GetIF()->GetPlayerFromID(szToID).sock;

	strcpy(rep1.szID,"Fail");
	strcpy(rep1.szMsg,szComment);
	gMainWin::GetIF()->Send(PL_MESSAGE_REP, sizeof(rep1), &rep1, sock);

}

void gMessageCore::pk_friendwhisper_ask(PK_DEFAULT *pk, SOCKET sock)
{
	PK_FRIENDWHISPER_ASK		ask;		//from client

	// for print
	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_FRIENDWHISPER_ASK*)pk->strPacket);

	sprintf(buf,"[PK_FRIENDWHISPER_ASK] %s\tMYID : %s", inet_ntoa(clientAddr.sin_addr), ask.szMyID);
	gMainWin::GetIF()->LogWrite(buf);

	stringstream ss;
	PK_MESSAGE_REP rep1,rep2;	//rep1 : ������ rep2 : �޴³�

	char *userFriendList = gMysql::GetIF()->friendGet(ask.szMyID);
	if (!userFriendList)	{
		strcpy(rep1.szID,"To ");
		strcat(rep1.szID,"Friends");
		strcpy(rep1.szMsg,ask.szComment);
		gMainWin::GetIF()->Send(PL_MESSAGE_REP, sizeof(rep1), &rep1, sock);
		
		msg_failMessage(ask.szMyID , "�׷��� ���� ��ħ�� �ܷο� �޾Ƹ����� �����־���.");
		return;
	}
	ss << userFriendList;
	
	char friendid[IDLENGTH];

	friendid[0] = 0;
	
	SOCKET sendsock;

	strcpy(rep1.szID,"To ");
	strcat(rep1.szID,"Friends");
	strcpy(rep1.szMsg,ask.szComment);
	gMainWin::GetIF()->Send(PL_MESSAGE_REP, sizeof(rep1), &rep1, sock);
	
	
	do //�Ľ� ����
	{
		ss >> friendid;
		if (!friendid[0])	break;
		
		strcpy(rep2.szID,"From ");
		strcat(rep2.szID,ask.szMyID);
		strcpy(rep2.szMsg,ask.szComment);

		sendsock	=	gPlayerContainer::GetIF()->GetPlayerFromID(friendid).sock;
		gMainWin::GetIF()->Send(PL_MESSAGE_REP, sizeof(rep2), &rep2, sendsock);

		friendid [0] = 0;
	
	} while (ss);

	delete userFriendList;
}

void gMessageCore::pk_friendlist_ask(PK_DEFAULT *pk, SOCKET sock)
{
	PK_FRIENDLIST_ASK		ask;		//from client

	// for print
	SOCKADDR_IN			clientAddr;
	int					addrLen;
	char				buf [1024];

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_FRIENDLIST_ASK*)pk->strPacket);

	sprintf(buf,"[PK_FRIENDWHISPER_ASK] %s\tMYID : %s", inet_ntoa(clientAddr.sin_addr), ask.szMyID);
	gMainWin::GetIF()->LogWrite(buf);

	stringstream ss;
	
	char *userFriendList = gMysql::GetIF()->friendGet(ask.szMyID);

	PK_MESSAGE_REP rep;
	
	if (!userFriendList)	{
		msg_failMessage(ask.szMyID , "ģ���� ������ �̤�");
		return;
	}
	ss << userFriendList;

	char friendid[IDLENGTH];

	char FriendNum[5]; 
		
	friendid[0] = 0;

	strcpy(rep.szID,ask.szMyID);
	strcpy(rep.szMsg,"���� ģ�� ���");
	gMainWin::GetIF()->Send(PL_MESSAGE_REP, sizeof(rep), &rep, sock);
	
	for (int i=1; ss ; i++ )	{
		ss >> friendid;
		if (!friendid[0])
			break;

		strcpy(rep.szID,ask.szMyID);
		strcpy(rep.szMsg,"*");
		itoa(i,FriendNum,10);
		strcat(rep.szMsg,FriendNum);
		strcat(rep.szMsg,".  ");

		strcat(rep.szMsg,friendid);

		gMainWin::GetIF()->Send(PL_MESSAGE_REP, sizeof(rep), &rep, sock);
		friendid [0] = 0;

	}
}


