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
	void			msg_whisper(char	 szToID[IDLENGTH] , char szFromID[IDLENGTH] , char szComment[MSGLENGTH] );

	void			pk_friendwhisper_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_friendlist_ask(PK_DEFAULT *pk, SOCKET sock);
	
	void			command(char* str,char* szID);
	
};
