//////////////////////////////////////////////////////////////////////////
/// �峭�˼�
/// ������ �� ����� �ʴ� channel �� (0~5) vs (1~6) ���� �ذ�
/// ������ ������ ���ۿ��� ������ ��������.
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
	CHANNEL			m_channelArray	[CHANNELMAX]; // 0-5 ������ ���ȣ
	// ���� ����� �����! (��¾ƾ���)

public:
	bool			SetUp();
	void			Release();

	bool			Join (char*id);
	void			DeletePlayer(char* id);

	int				FindPlayer(char* id); // Output : -1�� ������ ���°�... 0~5 ������ �� ��ȣ
//
	void			debuger(int channel); // channel�� 0~5 ���� 

	int				RoomClientNum(int channel); // ��ȿ� ����� ����� �ִ°�?
	bool			AddPlayer(int channel, char* id); // bool true�� �ٲܰ�.
	void			fullDebuger () ;
										
private:
	
	
	
	// �츮�Ĵ��
	int				AbleRoomNum();	// Output : -1�� ���� ���°�... 0~5 ������ �� ��ȣ
	//
	


};