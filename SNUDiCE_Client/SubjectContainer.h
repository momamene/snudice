//////////////////////////////////////////////////////////////////////////
/// SubjectContainer.h
/// Coder : �峭�˼�
/// 2010.09.18
/// Online Version���� �����鼭 ����...
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Map.h"

#define MAXSUBJECTINFOLENGTH 32
#define MAXSUBJECT_N 18

class SUBJECT {
public:
	int conPosIndex;
	int flag;
	char college[MAXSUBJECTINFOLENGTH];
	char building[MAXSUBJECTINFOLENGTH];
	char subject[MAXSUBJECTINFOLENGTH];

	SUBJECT();
};


class gSubjectContainer {
public:
	static gSubjectContainer *GetIF();

	//private:
	SUBJECT m_subject[MAXSUBJECT_N]; // -1�� ���, �׷��� �ʴٸ� i*LINEY+j

public:
	//bool SetUp();
	bool putSubject(gTile tile,int conPosIndex);
};

