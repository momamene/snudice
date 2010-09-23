//////////////////////////////////////////////////////////////////////////
/// SubjectContainer.h
/// Coder : �峭�˼�
/// 2010.09.18
/// Online Version���� �����鼭 ����...
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Map.h"
#include "networkconst.h"

#define MAXSUBJECTINFOLENGTH	32

/* subject index
	���迭
0		��ȸ���д���		16��		�ɸ��а���
1		��������			17��		������
2		�ι�����			1��			���б���
3		�����Ȯ			11��		��������
4		�ι�����			7��			���а� ������
5		��Ȱ���д���		222��		��Ȱ������ ����
6		�濵����			58��		�����濵
	�����迭
7		�ڿ����д���		25��		��������
8		�ڿ����д���		500��		ȭ�н���
9		���������д���	200��		�����ȯ��
10		��������			37��		�����̷�
11		��������			302��		���������
12		���д���			29��		�๰ġ����
13		���ǰ�����			85��		���ǿܰ���
	�����迭
14		���Ǵ���			54��		�����а���
15		�̼�����			49��		��ä��
16		�������			71��		��������
17		�̼�����			151��		�̼���Ž��

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

	SUBJECT		m_subject[CLASSNUM]; // -1�� ���,

public:
	//bool SetUp();
	bool		putSubject(gTile tile,int conPosIndex);
};

