#include "LoginCore.h"
#include "MainWin.h"
#include "PlayerContainer.h"

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
	USER* userTemp = new USER;
	strcpy(userTemp->szID,id);
	strcpy(userTemp->szPW,pw);
	userTemp->coreWhere = ECM_NONLOGIN;
	userTemp->nCoreFlag = 0;
	m_UserList.push_back(userTemp);
}

USER* gLoginCore::GetID(char* id)
{
	USER	*user;
	for(USER_LIST::iterator it = m_UserList.begin() ; it != m_UserList.end(); it++ ) {
		user = *it;
		if(strcmp(user->szID,id)==0) {
			return user;
		}
	}
	return NULL;
}



bool gLoginCore::SetUp()
{
	//for test. default °èÁ¤
	//USER*	userTemp;
	char	buf[1024];

	Put("test1","1111");
	Put("test2","1111");

	USER_LIST::iterator it;

	for(it = m_UserList.begin() ; it != m_UserList.end() ; it++)
	{

		sprintf(buf,"id : %s\tpw : %s\n", (*it)->szID, (*it)->szPW);
		OutputDebugString(buf);
	}

	return true;
}

void gLoginCore::Release()
{
	USER	*userTemp;

	for(USER_LIST::iterator it = m_UserList.begin(); it != m_UserList.end(); it++)
	{
		userTemp = (USER*)(*it);
		delete userTemp;
		userTemp = NULL;
	}
	m_UserList.clear();
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
	bool			bFind = false;
	bool			bSuccess = false;

	user = GetID(ask.szID);

	if(user==NULL) {
		rep.error = ELE_NOID; 
	}
	else { 
		bFind = true;
		if(strcmp(user->szPW,ask.szPW)!=0) {

			rep.error	= ELE_PWERROR;
		}
		else {
			if(user->coreWhere != ECM_NONLOGIN) {

				rep.error = ELE_OVERCONNECT;
			}
			else {
				bSuccess = true;
				rep.error = ELE_SUCCESS;
				strcpy(rep.player.szID,user->szID);
				rep.player.coreWhere = ECM_BATTLENET;
				rep.player.nCoreFlag = 0;
				rep.player.sock = sock;
				gPlayerContainer::GetIF()->AddPlayer(&rep.player);
			}
		}
	}
	
	
/*
	for(USER_LIST::iterator it = m_UserList.begin(); it != m_UserList.end(); it++)
	{
		user = *it;

		if(strcmp(user->szID, ask.szID) == 0)
		{
			if(strcmp(user->szPW, ask.szPW) == 0)
			{
				if(user->coreWhere != ECM_NONLOGIN)
					rep.error	= ELE_OVERCONNECT;
				else
					bSuccess = true;
					rep.error	= ELE_SUCCESS;
					strcpy(rep.player.szID, user->szID);
					rep.player.coreWhere = ECM_BATTLENET;
					rep.player.nCoreFlag = 0;
					bFind = true;
					break;
			}
			else
			{
				rep.error	= ELE_PWERROR;
				bFind = true;
				break;
			}
		}
	}

	if(!bFind)
		rep.error = ELE_NOID;

	if(bSuccess) 
	{

		rep.player.sock = sock;
		gPlayerContainer::GetIF()->AddPlayer(&rep.player);
	}
*/
	gMainWin::GetIF()->Send(PL_LOGIN_REP, sizeof(rep), &rep, sock);
}
