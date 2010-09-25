//////////////////////////////////////////////////////////////////////////
/// SubjectContainer.h
/// Coder : 장난죄송
/// 2010.09.18
/// Online Version으로 들어오면서 만든...
//////////////////////////////////////////////////////////////////////////
#include "TILE.h"
#include "network.h"

#define MAXSUBJECTINFOLENGTH 32
//#define MAXSUBJECT_N 18

class SUBJECT {
public:
	int conPosIndex;
	int flag1;		// 언어인가 수리인가 예체능인가
	char college[MAXSUBJECTINFOLENGTH];
	char building[MAXSUBJECTINFOLENGTH];
	char subject[MAXSUBJECTINFOLENGTH];

	SUBJECT();
};


class gSubjectContainer {
public:
	static gSubjectContainer *GetIF();

//private:
	SUBJECT m_subject[CLASSNUM]; // -1은 빈거, 그렇지 않다면 i*LINEY+j


public:
	//bool SetUp();
	bool		putSubject(TILE tile,int conPosIndex);


	float		gradeExpectOne (int weightCount, int nRound);
	float		gradeAverage (int* weightCount, int nRound, int numberOfSubject);

private:
	float		gradification (float grade);
};

