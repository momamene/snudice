//////////////////////////////////////////////////////////////////////////
/// 장난죄송
/// 22일 오후 3:33
/// nChannel을 1-6 으로 channel을 0-5 로 상정합니다.
/// pk_channelrefresh_rep 에 szID 예외 사항을 상정할 수 있도록 합니다.
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

	void			pk_channelchange_ask (PK_DEFAULT *pk, SOCKET sock); // 방을 나갈때도 이 패킷을 쏜다는 점이 중요!
	void			pk_channelrefresh_rep (int channel);


};