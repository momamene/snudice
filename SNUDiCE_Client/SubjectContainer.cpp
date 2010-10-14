#include "SubjectContainer.h"
#include "Map.h"
#define SCRIPT_FILE "Subject_Script.txt" //��ũ��Ʈ ���� �ִ� ���ε�, �˾Ƽ� �ٱ��ֽʼ� ��
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
	//�ݵ�� ��ũ��Ʈ�� 
	//�����̸�
	//������
	//�����̸�
	//������
	//�̷������� ���ֽʽÿ� �ƴϸ� �䵵�˴ϴ�.
	//�׸��� ������ ���̴� �ظ��ϸ� 25�� ���ܷ�...
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