//////////////////////////////////////////////////////////////////////////
/// SubjectContainer.h
/// Coder : �峭�˼�
/// 2010.09.18
/// Online Version���� �����鼭 ����...
//////////////////////////////////////////////////////////////////////////
#include "TILE.h"
#include "network.h"

#define MAXSUBJECTINFOLENGTH 32
//#define MAXSUBJECT_N 18

class SUBJECT {
public:
	int conPosIndex;
	int flag1;		// ����ΰ� �����ΰ� ��ü���ΰ�
	char college[MAXSUBJECTINFOLENGTH];
	char building[MAXSUBJECTINFOLENGTH];
	char subject[MAXSUBJECTINFOLENGTH];

	SUBJECT();
};


class gSubjectContainer {
public:
	static gSubjectContainer *GetIF();

//private:
	SUBJECT m_subject[CLASSNUM]; // -1�� ���, �׷��� �ʴٸ� i*LINEY+j


public:
	//bool SetUp();
	bool		putSubject(TILE tile,int conPosIndex);


	float		gradeExpectOne (int weightCount, int nRound);
	float		gradeAverage (int* weightCount, int nRound, int numberOfSubject);

private:
	float		gradification (float grade);
};

