#include "PlayerContainer.h"
#include "GamePlayerContainer.h"	//수정사항, 에라 모르겟다 춤이나 추자
#include "MainWin.h"

static gPlayerContainer s_PlayerContainer;

gPlayerContainer *gPlayerContainer::GetIF()
{
	return &s_PlayerContainer;
}

gPlayerContainer::gPlayerContainer()
{

}

gPlayerContainer::~gPlayerContainer()
{

}

bool gPlayerContainer::SetUp()
{
	return true;
}

void gPlayerContainer::Release()
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;
		delete temp;
		temp = NULL;
	}
	m_PlayerList.clear();
}

void gPlayerContainer::AddPlayer(PLAYER* player)
{
	PLAYER*		add;
	add = new PLAYER;

	memcpy(add, player, sizeof(PLAYER));

	m_PlayerList.push_back(add);
}

bool gPlayerContainer::isExistedPlayer(char* id)
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;

		if(strcmp(temp->szID, id) == 0)
			return true;
	}
	return false;
}

bool gPlayerContainer::DeletePlayer(SOCKET sock,char clientID[IDLENGTH])
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;

		if(temp->sock == sock)
		{
			strcpy(clientID,temp->szID);
			gGamePlayerContainer::GetIF()->pk_exit_ask(clientID , sock);
			delete temp;
			temp = NULL;
			m_PlayerList.erase(it);
			
			return true;
			//break;
		}
	}

	return false;
}

bool gPlayerContainer::FindSocketFromID(char* id, SOCKET* getSock)
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;
		
		if(strcmp(temp->szID,id)==0)
		{
			*getSock = temp->sock;
			return true;
		}
	}

	return false;

}

bool gPlayerContainer::PutMode(char* id,eCOREMODE mode)
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;

		if(strcmp(temp->szID,id)==0)
		{
			temp->coreWhere = mode;
			return true;
		}
	}

	return false;
}

void gPlayerContainer::PutModeToModeForAll(eCOREMODE befMode, int flag,eCOREMODE newMode)
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;

		if(temp->nCoreFlag==flag && temp->coreWhere==befMode)
		{
			temp->coreWhere = newMode;
		}
	}
}

bool gPlayerContainer::PutCoreFlag (char* id,int flag)
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;

		if(strcmp(temp->szID,id)==0)
		{
			temp->nCoreFlag = flag;
			return true;
		}
	}

	return false;
}

bool gPlayerContainer::PutBoolReady (char* id,bool bReady)
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;

		if(strcmp(temp->szID,id)==0)
		{
			temp->bReady = bReady;
			return true;
		}
	}

	return false;
}

bool gPlayerContainer::PutClassType (char* id,CLASSTYPE classtype)
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;

		if(strcmp(temp->szID,id)==0)
		{
			temp->classtype = classtype;
			return true;
		}
	}

	return false;
}

CLASSTYPE gPlayerContainer::GetClassType (char* id)
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;

		if(strcmp(temp->szID,id)==0)
		{
			return temp->classtype;
		}
	}

	return CLASS_NONE;
}


int gPlayerContainer::GetCoreFlag(char* id) {
	PLAYER*		temp;
	for(PLAYER_LIST::iterator it = m_PlayerList.begin() ; 
		it != m_PlayerList.end() ; it++)
	{
		temp = *it;
		if(strcmp(temp->szID,id)==0)
		{
			return temp->nCoreFlag;
		}
	}
	return -1;
}

eCOREMODE gPlayerContainer::GetMode(char* id) {
	PLAYER*		temp;
	for(PLAYER_LIST::iterator it = m_PlayerList.begin() ; 
		it != m_PlayerList.end() ; it++)
	{
		temp = *it;
		if(strcmp(temp->szID,id)==0)
		{
			return temp->coreWhere;
		}
	}
	return (eCOREMODE)-1;
}

bool gPlayerContainer::isClasstypeExistedInRoom(int nRoomIndex,CLASSTYPE classtype)
{
	PLAYER*		temp;
	for(PLAYER_LIST::iterator it = m_PlayerList.begin() ; 
		it != m_PlayerList.end() ; it++)
	{
		temp = *it;
		if(temp->coreWhere==ECM_ROOM && temp->nCoreFlag==nRoomIndex)
		{
			if(temp->classtype==classtype)
				return true;
		}
	}
	return false;
}

bool gPlayerContainer::isAllReadyInRoom(int nRoomIndex)
{
	PLAYER*		temp;
	for(PLAYER_LIST::iterator it = m_PlayerList.begin() ; 
		it != m_PlayerList.end() ; it++)
	{
		temp = *it;
		if(temp->coreWhere==ECM_ROOM && temp->nCoreFlag==nRoomIndex)
		{
			if(temp->bReady==false)
				return false;
		}
	}
	return true;
}


PLAYER gPlayerContainer::GetPlayerFromID(char* szID) {
	PLAYER*		temp;
	PLAYER		player;
	memset(&player,0,sizeof(PLAYER));
	
	for(PLAYER_LIST::iterator it = m_PlayerList.begin() ; 
		it != m_PlayerList.end() ; it++)
		{
			temp = *it;
			if(strcmp(temp->szID,szID)==0)
			{
				//player = *temp; 
				memcpy(&player,temp,sizeof(PLAYER));
				break;
			}
		}	
	return player;
} 

PLAYER gPlayerContainer::GetPlayerFromSocket(SOCKET sock)
{

	PLAYER*		temp;
	PLAYER		player;
	memset(&player,0,sizeof(PLAYER));

	for(PLAYER_LIST::iterator it = m_PlayerList.begin() ; 
		it != m_PlayerList.end() ; it++)
	{
		temp = *it;
		if(temp->sock == sock)
		{
			//player = *temp; 
			memcpy(&player,temp,sizeof(PLAYER));
			break;
		}
	}	
	return player;
} 


void gPlayerContainer::SendSelect (ePROTOCOL prot,int pkSize,void *pk,eCOREMODE mode,int nPage)
{
	PLAYER*		temp;

	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;

		if(temp->coreWhere==mode && temp->nCoreFlag == nPage)
		{
			gMainWin::GetIF()->Send(prot, pkSize, pk, temp->szID);
		}
	}
}


void gPlayerContainer::Draw (HDC hdc) 
{
	PLAYER*		temp;
	char printo[128];
	char buf [128];
	int count = 0;
	for(PLAYER_LIST::iterator it = m_PlayerList.begin();
		it != m_PlayerList.end(); it++)
	{
		temp = *it;
		if(temp->szID[0]!='\0') {
			strcpy(printo,"coreWhere : ");
			if(temp->coreWhere == ECM_NONLOGIN) {
				strcat(printo,"ECM_NONLOGIN");
			}
			else if(temp->coreWhere == ECM_LOGIN) {
				strcat(printo,"ECM_LOGIN");
			}
			else if(temp->coreWhere == ECM_BATTLENET) {
				strcat(printo,"ECM_BATTLENET");
			}
			else if(temp->coreWhere == ECM_ROOMMAKE) {
				strcat(printo,"ECM_ROOMMAKE");
			}
			else if(temp->coreWhere == ECM_ROOMJOIN) {
				strcat(printo,"ECM_ROOMJOIN");
			}
			else if(temp->coreWhere == ECM_ROOM) {
				strcat(printo,"ECM_ROOM");
			}
			else if(temp->coreWhere == ECM_SUBMIT) {
				strcat(printo,"ECM_SUBMIT");
			}
			else if(temp->coreWhere == ECM_GAME) {
				strcat(printo,"ECM_GAME");
			}
			sprintf(buf," Flag : %d Sock : %d Char : %d ID : %s",temp->nCoreFlag,temp->sock,temp->classtype,temp->szID);
			strcat(printo,buf);
			TextOut(hdc,0,count*15+15,printo,strlen(printo));
		}
		count++;
	}
	TextOut(hdc,0,0,"Player Infomation",strlen("Player Infomation"));
}

