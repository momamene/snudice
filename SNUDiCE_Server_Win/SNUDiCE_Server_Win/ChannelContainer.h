//////////////////////////////////////////////////////////////////////////
/// 장난죄송
/// 문제는 잘 결맞지 않는 channel 값 (0~5) vs (1~6) 문제 해결
/// 지금은 전방위 전송에서 문제가 있을지도.
//////////////////////////////////////////////////////////////////////////

#include "network.h"

class gChannelContainer
{
public:
	static gChannelContainer *GetIF();

	//	gPlayerContainer();
	//	virtual ~gPlayerContainer();

public:
	//	PLAYER_LIST		m_PlayerList;
	bool			m_isExisted		[CHANNELMAX][CHANNELUSERMAX];
	CHANNEL			m_channelArray	[CHANNELMAX]; // 0-5 까지의 방번호
	// 둘의 관계는 결맞음! (결맞아야함)

public:
	bool			SetUp();
	void			Release();

	bool			Join (char*id);
	void			DeletePlayer(char* id);

	int				FindPlayer(char* id); // Output : -1은 유저가 없는거... 0~5 까지는 방 번호
//
	void			debuger(int channel); // channel은 0~5 까지 

	int				RoomClientNum(int channel); // 방안에 몇명의 사람이 있는가?
	bool			AddPlayer(int channel, char* id); // bool true로 바꿀것.
	void			fullDebuger () ;
										
private:
	
	
	
	// 우리식대로
	int				AbleRoomNum();	// Output : -1은 방이 없는거... 0~5 까지는 방 번호
	//
	


};