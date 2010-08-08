#include "LoginCore.h"

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
	USER*	userTemp;

	for(USER_LIST::iterator it = m_UserList.begin(); it != m_UserList.end(); it++)
	{
		delete userTemp;
		m_UserList.erase(it);
	}
}

// packet
void gLoginCore::pk_login_rep(PK_DEFAULT *pk, SOCKET sock)
{
	PK_LOGIN_ASK		ask;		//from client

	ask = *((PK_LOGIN_ASK*)pk->strPacket);

	printf("[PK_LOGIN_REP] id : %s\t pw : %s\n", ask.szID, ask.szPW);
}
