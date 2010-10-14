#include "SubjectContainer.h"
#include "Map.h"
#define SCRIPT_FILE "Subject_Script.txt" //스크립트 파일 있는 곳인데, 알아서 바까주십쇼 ㅠ
#include <stdio.h>

SUBJECT::SUBJECT()
{
	conPosIndex = -1;
	flag = -1;
	memset(college,0,sizeof(char)*MAXSUBJECTINFOLENGTH);
	memset(building,0,sizeof(char)*MAXSUBJECTINFOLENGTH);
	memset(subject,0,sizeof(char)*MAXSUBJECTINFOLENGTH);
}


void SUBJECT::putScript(int n)
{
	char szTemp[MAXSCRIPTLENGTH+1];
	//반드시 스크립트는 
	//교수이름
	//강의평가
	//교수이름
	//강의평가
	//이런식으로 써주십시오 아니면 요도됩니다.
	//그리고 강의평가 길이는 왠만하면 25자 내외로...
	FILE *fp=fopen(SCRIPT_FILE, "rt");
	for(int i = 0 ; i <= n ; i++) {
		if(i==n) {
			fgets(szTemp, 10, fp);
			if(szTemp[strlen(szTemp)-1]=='\n') szTemp[strlen(szTemp)-1]=0;
			strcpy(professor, szTemp);
			fgets(szTemp, MAXSCRIPTLENGTH, fp);
			if(szTemp[strlen(szTemp)-1]=='\n') szTemp[strlen(szTemp)-1]=0;
			strcpy(script, szTemp);
		}
		else {
			fgets(szTemp, 10, fp);
			fgets(szTemp, MAXSCRIPTLENGTH, fp);
		}
	}
	fclose(fp);
}


static gSubjectContainer s_subjectContainer; // 2

gSubjectContainer *gSubjectContainer::GetIF() // 3
{
	return &s_subjectContainer;
}

bool gSubjectContainer::putSubject(gTile tile, int conPosIndex)
{
	if(tile.flag2 < CLASSNUM && m_subject[tile.flag2].conPosIndex == -1)
	{
		m_subject[tile.flag2].conPosIndex = conPosIndex;
		m_subject[tile.flag2].flag = tile.flag1;
		strcpy(m_subject[tile.flag2].college,tile.college);
		strcpy(m_subject[tile.flag2].building,tile.building);
		strcpy(m_subject[tile.flag2].subject,tile.subject);
		m_subject[tile.flag2].putScript(tile.flag2);
		return true;
	} 
	else
	{
		return false;
	}
}