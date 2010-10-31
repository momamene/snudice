#pragma once
#include "network.h"


class gMessageCore
{
public:
	static gMessageCore *GetIF();

public:
	bool			SetUp();
	void			Release();

	void			pk_message_ask(PK_DEFAULT *pk, SOCKET sock);
	void			debuger(char* str,char* szID);
};