#pragma once
#include "network.h"


class gMessageCore
{
public:
	static gMessageCore *GetIF();

	gMessageCore();
	virtual ~gMessageCore();


public:
	bool			SetUp();
	void			Release();

	// packet

	void			pk_message_ask(PK_DEFAULT *pk, SOCKET sock);

	
private:
	//void			Put(char* id, char* pw);
	//USER*			GetID(char* id);
};