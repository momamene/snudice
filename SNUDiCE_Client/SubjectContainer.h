//////////////////////////////////////////////////////////////////////////
/// SubjectContainer.h
/// Coder : 장난죄송
/// 2010.09.18
/// Online Version으로 들어오면서 만든...
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Map.h"

#define MAXSUBJECTINFOLENGTH 32
#define MAXSUBJECT_N 18

class SUBJECT {
public:
	int		conPosIndex;
	int		flag;
	char	college[MAXSUBJECTINFOLENGTH];
	char	building[MAXSUBJECTINFOLENGTH];
	char	subject[MAXSUBJECTINFOLENGTH];

	SUBJECT();
};


class gSubjectContainer {
public:
	static gSubjectContainer *GetIF();

	SUBJECT		m_subject[MAXSUBJECT_N]; // -1은 빈거,

public:
	//bool SetUp();
	bool		putSubject(gTile tile,int conPosIndex);
};

