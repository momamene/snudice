#pragma once
#include "network.h"


class gSubmitCore
{
public:
	static gSubmitCore *GetIF();

public:
	bool			m_isValidSubmitSubject[MAXROOM];
	BYTE			m_submitSubject[MAXROOM][CLASSNUM][CLASSSEAT];
	BYTE			m_submitSubjectPlayer[MAXROOM][ROOMMAXPLAYER][MAXSUBJECT];
	bool			m_isFinishSubmitSubject[MAXROOM][ROOMMAXPLAYER];

public:
	bool			SetUp();
	void			init(int nRoomindex);
	void			Release();

	void			pk_gamestart_rep(int nRoomIndex);
	void			pk_submit_ask(PK_DEFAULT *pk, SOCKET sock);
	void			pk_submitready_ask(PK_DEFAULT *pk,SOCKET sock);
	
	bool			isFinishAllSubmit(int nRoomIndex);

	// packet

	//void			pk_message_ask(PK_DEFAULT *pk, SOCKET sock);

	// 중요! put과 push 는 연동되어야함.
	// 따라서, 호출할때는 **Subject를 호출해야 하며 ToPlayer는 호출하지 말것.
	// m_submitSubject와 m_submitSubjectPlayer에서..
	// 괜히 이런 짓을 한걸까...

private:
	bool			putSubject(int nRoomIndex,int nInRoomIndex,int nSubjectIndex);
	void			putSubjectToPlayer(int nRoomIndex, int nInRoomIndex, int nSubjectIndex);
	bool			pushSubject(int nRoomIndex,int nInRoomIndex,int nSubjectIndex);
	void			pushSubjectToPlayer(int nRoomIndex,int nInRoomIndex,int nSubjectIndex);
	bool			isSubjectFull(int nRoomIndex,int nInRoomIndex);
	bool			isSubjectExisted(int nRoomIndex,int nInRoomIndex,int nSubjectIndex);

	void			putFavorsameclass(int nRoomIndex);	//같은Class 들으면 호감도 상승
};

