#include "SubjectContainer.h"

SUBJECT::SUBJECT()
{
	conPosIndex = -1;
	flag = -1;
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
	if(tile.flag2 < MAXSUBJECT_N && m_subject[tile.flag2].conPosIndex == -1) {
		m_subject[tile.flag2].conPosIndex = conPosIndex;
		m_subject[tile.flag2].flag = tile.flag1;
		strcpy(m_subject[tile.flag2].college,tile.college);
		strcpy(m_subject[tile.flag2].building,tile.building);
		strcpy(m_subject[tile.flag2].subject,tile.subject);
		return true;
	} 
	else {
		return false;
	}
}