#include "LoginCore.h"
#include "Server.h"

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

bool gLoginCore::SetUp()
{
	//for test. default °èÁ¤
	USER*	userTemp;

	userTemp = new USER;
	strcpy(userTemp->szID, "test1");
	strcpy(userTemp->szPW, "1111");
	userTemp->coreWhere = ECM_NONLOGIN;
	userTemp->nCoreFlag	= 0;

	m_UserList.push_back(userTemp);

	userTemp = new USER;
	strcpy(userTemp->szID, "test2");
	strcpy(userTemp->szPW, "1111");
	userTemp->coreWhere = ECM_NONLOGIN;
	userTemp->nCoreFlag	= 0;
	
	m_UserList.push_back(userTemp);

	USER_LIST::iterator it;

	for(it = m_UserList.begin() ; it != m_UserList.end() ; it++)
	{
		printf("id : %s\tpw : %s\n", (*it)->szID, (*it)->szPW);
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

	addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);

	ask = *((PK_LOGIN_ASK*)pk->strPacket);

	printf("[PK_LOGIN_REP] %s\tid : %s\t pw : %s\n", inet_ntoa(clientAddr.sin_addr), ask.szID, ask.szPW);


	PK_LOGIN_REP	rep;
	USER			*user;
	bool			bFind = false;

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

	gServer::GetIF()->Send(PL_LOGIN_REP, sizeof(rep), &rep, sock);
}
