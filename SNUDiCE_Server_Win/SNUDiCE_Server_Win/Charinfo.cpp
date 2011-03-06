#include "Charinfo.h"
#include "const.h"
#include <stdio.h>

static gCharinfo s_Charinfo;

gCharinfo *gCharinfo::GetIF()
{
	return &s_Charinfo;
}

bool gCharinfo::SetUp()
{
	FILE  *fp;
	fp = fopen(CHARDATAFILE, "rt");
	if(!fp)
		return false;
	int   i, k;
	int   nIndex = 0;  // ���° ĳ���� �Է����̳�
	int   nCount;   // ���Է����̳�. 0 ; �̸�, 1; �ܴ� .. .
	char  szBuf[256];
	char  szTemp[256];
	while( fgets(szBuf, 256, fp) != NULL)
	{
		if(szBuf[0] == '/' && szBuf[1] == '/')
			continue;        // �ּ� �ǳʶٱ�
		i = 0;
		k = 0;
		nCount = 0;
		while(szBuf[i] != '\n')
		{
			if(szBuf[i] == ',')
			{
				szTemp[k] = NULL;
				switch(nCount++)
				{
				case 0: // �̸�
					strcpy(m_CharInfo[nIndex].szName, szTemp);
					break;
				case 1: // �ܰ�����
					strcpy(m_CharInfo[nIndex].szCollege, szTemp);
					break;
				case 2: // ����
					if( strcmp(szTemp, "��") == 0 ) // && nIndex != 12)	//�ɿ�������
						m_CharInfo[nIndex].bMale = true;
					else
						m_CharInfo[nIndex].bMale = false;
					break;
				case 3: // ���
					m_CharInfo[nIndex].nLang = atoi(szTemp);
					break;
				case 4: // ����
					m_CharInfo[nIndex].nMath = atoi(szTemp);
					break;
				case 5: // ����
					m_CharInfo[nIndex].nArt = atoi(szTemp);
					break;
				case 6: // ü��
					m_CharInfo[nIndex].nStamina = atoi(szTemp);
					break;
				case 7: // 4��ü
					m_CharInfo[nIndex].nDice4 = atoi(szTemp);
					break;
				case 8: // 6��ü
					m_CharInfo[nIndex].nDice6 = atoi(szTemp);
					break;
				}
				k = 0;
			}
			else if(szBuf[i] != '\t')
				szTemp[k++] = szBuf[i];
			i++;
		}
		nIndex++;
	}
	fclose(fp);

	return true;
}

void gCharinfo::Release()
{

}

CHARINFO gCharinfo::getCharinfo(int index)
{
	return m_CharInfo[index];
}

bool gCharinfo::getMale(int index)
{
	return m_CharInfo[index].bMale;
}

