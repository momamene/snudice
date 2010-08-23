#include "ChannelContainer.h"

static gChannelContainer s_ChannelContainer;

gChannelContainer *gChannelContainer::GetIF()
{
	return &s_ChannelContainer;
}

bool gChannelContainer::SetUp()
{
	memset(m_channelArray,0,sizeof(CHANNEL)*CHANNELMAX);
	for(int i = 0 ; i < CHANNELMAX ; i++){
		m_channelArray[i].nChannelNum = i+1;
		m_channelArray[i].nUserNum = 0;
		for (int j = 0 ; j < CHANNELUSERMAX ; j ++) {
			m_isExisted[i][j] = false;
		}
	}
	

	return true;
}

void gChannelContainer::Release()
{
	
}

//////////////////////////////////////////////////////////////////////////
/// 
//////////////////////////////////////////////////////////////////////////

bool gChannelContainer::Join(char* id)
{
	int able = AbleRoomNum();
	if(able==-1) {
		OutputDebugString("Join Fail을 내부에서 알립니다. \n");
		return false;
	}
	else {
		return AddPlayer(able,id);
		//return true;
	}

}


bool gChannelContainer::AddPlayer(int channel, char* id)
{

	for(int j = 0 ; j < CHANNELUSERMAX ; j++){
		if(!m_isExisted[channel][j]) {
			m_isExisted[channel][j] = true;
			//m_channelArray[channel-1].nChannelNum = channel;
			m_channelArray[channel].nUserNum = RoomClientNum(channel);
			strcpy(m_channelArray[channel].szUserInCh[j],id);

			return true;
		}
	}

	return false;
}

int gChannelContainer::RoomClientNum (int channel)
{
	int count = 0;
	for(int j = 0 ; j < CHANNELUSERMAX ; j++) {
		if(m_isExisted[channel][j]) count++;
	}
	return count;
}

int	gChannelContainer::AbleRoomNum() {
	for(int i = 0 ; i < CHANNELMAX ; i++) {
		for(int j = 0 ; j < CHANNELUSERMAX ; j++ ){
			if(!m_isExisted[i][j]) {
				return i;
			}
		}
	}
	return -1;
}

void gChannelContainer::DeletePlayer(char* id)
{
	for(int i = 0 ; i < CHANNELMAX ; i++) {
		for(int j = 0 ; j < CHANNELUSERMAX ; j++ ){


			if(strcmp(m_channelArray[i].szUserInCh[j],id)==0) {
				if(!m_isExisted[i][j]) {
					OutputDebugString("DeletePlayer 치명적 오류 \n");
				}
				else {
					j++;
					m_channelArray[i].nUserNum = RoomClientNum(i);

					for(; j < CHANNELUSERMAX && m_isExisted[i][j] == true ; j++)
						strcpy(m_channelArray[i].szUserInCh[j-1],m_channelArray[i].szUserInCh[j]);
					m_isExisted[i][j-1] = false;
					strcpy(m_channelArray[i].szUserInCh[j-1],"");
				}
			}
		}
	}
}

int gChannelContainer::FindPlayer (char* id) {
	for(int i = 0 ; i < CHANNELMAX ; i++) {
		for(int j = 0 ; j < CHANNELUSERMAX ; j++ ){
			if(m_isExisted[i][j]&&strcmp(m_channelArray[i].szUserInCh[j],id)==0) {
				return i;
			}
		}
	}
	return -1;
}

void gChannelContainer::debuger (int channel)
{
	char buf[128];

	wsprintf(buf,"debuger channel : %d \n",channel);
	OutputDebugString(buf);
	for(int j = 0 ; j < CHANNELUSERMAX ; j++ ) {
		if(m_isExisted[channel][j]) {
			OutputDebugString(m_channelArray[channel].szUserInCh[j]);
			OutputDebugString(" . ");
		}
		else{
			OutputDebugString("/");
		}
	}
	OutputDebugString("\n");
}

void gChannelContainer::fullDebuger () 
{
	for (int i = 0 ; i < CHANNELMAX ; i++)
		debuger(i);
}