//////////////////////////////////////////////////////////////////////////
/// �峭�˼�
/// 22�� ���� 3:33
/// nChannel�� 1-6 ���� channel�� 0-5 �� �����մϴ�.
/// pk_channelrefresh_rep �� szID ���� ������ ������ �� �ֵ��� �մϴ�.
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "network.h"


class gChannelCore
{
public:
	static gChannelCore *GetIF();

	gChannelCore();


public:
//	bool			SetUp();
	void			Release();

	// packet

	void			pk_channelchange_ask (PK_DEFAULT *pk, SOCKET sock); // ���� �������� �� ��Ŷ�� ��ٴ� ���� �߿�!
	void			pk_channelrefresh_rep (int channel);


};