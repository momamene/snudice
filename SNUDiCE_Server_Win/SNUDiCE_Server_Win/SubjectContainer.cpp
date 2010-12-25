#include "SubjectContainer.h"

SUBJECT::SUBJECT()
{
	conPosIndex = -1;
	flag1 = -1;
	memset(college,0,sizeof(char)*MAXSUBJECTINFOLENGTH);
	memset(building,0,sizeof(char)*MAXSUBJECTINFOLENGTH);
	memset(subject,0,sizeof(char)*MAXSUBJECTINFOLENGTH);
}

/*
bool gSubjectContainer::SetUp()
{
	for(int i = 0 ; i < MAXSUBJECT_N ; i++) {
		m_subject[i] = -1;
	}

}
*/

static gSubjectContainer s_subjectContainer; // 2

gSubjectContainer *gSubjectContainer::GetIF() // 3
{
	return &s_subjectContainer;
}
bool gSubjectContainer::putSubject(TILE tile, int conPosIndex) {
	if(tile.flag2 < CLASSNUM && m_subject[tile.flag2].conPosIndex == -1) {
		m_subject[tile.flag2].conPosIndex = conPosIndex;
		m_subject[tile.flag2].flag1 = tile.flag1;
		strcpy(m_subject[tile.flag2].college,tile.college);
		strcpy(m_subject[tile.flag2].building,tile.building);
		strcpy(m_subject[tile.flag2].subject,tile.subject);
		return true;
	} 
	else {
		return false;
	}
}


float gSubjectContainer::gradeExpectOne (int weightCount, int nRound)
{
	
	float grade;
	if (weightCount == 0)	{	//F
		return 0.0f;
	}	else if (0 < weightCount && weightCount <= 3)	{	// D-
		return 0.7f;
	}	else if (3 < weightCount && weightCount <= 6)	{	// D0
		return 1.0f;
	}	else if (6 < weightCount && weightCount <= 10)	{	// D+
		return 1.3f;
	}	else if (10 < weightCount && weightCount <= 13)	{	// C-
		return 1.6f;
	}	else if (13 < weightCount && weightCount <= 16)	{	// C0
		return 2.0f;
	}	else if (16 < weightCount && weightCount <= 20)	{	// C+
		return 2.3f;
	}	else if (20 < weightCount && weightCount <= 23)	{	// B-
		return 2.6f;
	}	else if (23 < weightCount && weightCount <= 26)	{	// B0
		return 3.0f;
	}	else if (26 < weightCount && weightCount <= 30)	{	// B+
		return 3.3f;
	}	else if (30 < weightCount && weightCount <= 33)	{	// A-
		return 3.6f;
	}	else if (33 < weightCount && weightCount <= 36)	{	// A0
		return 4.0f;
	}	else if (36 < weightCount)	{	// A+
		return 4.3f;
	}
	return -1.0f;
}


float gSubjectContainer::gradeAverage (int* weightCount, int nRound, int numberOfSubject)
{
	float average = 0.0;
	for (int i = 0 ; i < numberOfSubject ; i++ ) {
		average += gradeExpectOne(weightCount[i],nRound);
	}
	average = average / numberOfSubject ;
	return average;
}

