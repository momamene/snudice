//////////////////////////////////////////////////////////////////////////
/// SubjectContainer.h
/// Coder : 장난죄송
/// 2010.09.18
/// Online Version으로 들어오면서 만든...
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Map.h"
#include "networkconst.h"

#define MAXSUBJECTINFOLENGTH	32

/* subject index
	언어계열
0		사회과학대학		16동		심리학개론
1		법과대학			17동		법의학
2		인문대학			1동			대학국어
3		사범대확			11동		교육과정
4		인문대학			7동			미학과 예술론
5		생활과학대학		222동		생활과학의 이해
6		경영대학			58동		국제경영
	수리계열
7		자연과학대학		25동		미적분학
8		자연과학대학		500동		화학실험
9		농업생명과학대학	200동		농업과환경
10		공과대학			37동		건축이론
11		공과대학			302동		논리설계실험
12		약학대학			29동		약물치료학
13		수의과대학			85동		수의외과학
	예술계열
14		음악대학			54동		음악학개론
15		미술대학			49동		색채학
16		사범대학			71동		댄스스포츠
17		미술대학			151동		미술관탐방

*/


class SUBJECT
{
public:
	int		conPosIndex;
	int		flag;
	char	college[MAXSUBJECTINFOLENGTH];
	char	building[MAXSUBJECTINFOLENGTH];
	char	subject[MAXSUBJECTINFOLENGTH];

	SUBJECT();
};


class gSubjectContainer
{
public:
	static gSubjectContainer *GetIF();

	SUBJECT		m_subject[CLASSNUM]; // -1은 빈거,

public:
	//bool SetUp();
	bool		putSubject(gTile tile,int conPosIndex);
};

