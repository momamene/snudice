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

float gSubjectContainer::gradification (float grade)
{
	float gradeLeft = grade;
	if(grade<0.7 ) return 0.0;
	else if(grade >= 4.3) return 4.3;
	else{
		while(gradeLeft>1) gradeLeft -= 1.0;
		if(gradeLeft < 0.3) return grade - gradeLeft;
		else if(gradeLeft < 0.7) return grade - gradeLeft + 0.3;
		else return grade - gradeLeft + 0.7;
	}
}


float gSubjectContainer::gradeExpectOne (int weightCount, int nRound)
{
	float grade;
	grade = (double)weightCount / (nRound+29);
	return gradification(grade);
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

