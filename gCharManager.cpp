#include "gCharManager.h"
#include "const.h"
#include <stdio.h>

//------------------------------------------------------------------------------------
//	Constructor	/	Destructor
//------------------------------------------------------------------------------------
static gCharManager s_charmanager;

gCharManager *gCharManager::GetIF()
{
	return &s_charmanager;
}

gCharManager::gCharManager()
{

}

gCharManager::~gCharManager()
{

}

void gCharManager::Release()
{
	int		i;

	for(i = 0; i < CHARNUM; i++)
		m_Chars[i].Release();
		
	SAFE_DELETE_ARRAY(m_Chars);
}

bool gCharManager::SetUp()
{
	// alloc chars
	m_Chars	= new gChar[CHARNUM];

	// read dat file
	FILE	*fp;

	fp = fopen(CHARDATAFILE, "rt");
	if(!fp)	return false;

	char		szBuf[512];
	char		szTemp[512];
	char		szIllu[128];
	int			i, k;
	int			nSlot = 0;
	int			nCount;			// �� �Է��ϴ����̳� 0 �ܴ� 1 �̸� ...
	CHARDATA	chardata;

	// �ܰ�����, �̸�, ����(��1��0), ���, ����, ����, ü��, �̵�, ��Ÿ����, �̹���
	while(fgets(szBuf, 512, fp) != NULL)
	{
		if(szBuf[0] == '/' && szBuf[1] == '/')	continue;		// �ּ��� ���
		i = 0;
		k = 0;
		nCount	= 0;
		while(szBuf[i] != '\n')
		{
			if(szBuf[i] == ',')
			{
				szTemp[k] = NULL;
				switch(nCount++)
				{
				case 0:	// �ܰ�����
					strcpy(chardata.szColleage, szTemp);
					break;
				case 1: // �̸�
					strcpy(chardata.szName, szTemp);
					break;
				case 2: // ����
					if(strcmp(szTemp, "��") == 0)
						chardata.eSex = ESEX_MALE;
					else
						chardata.eSex = ESEX_FEMALE;
					break;
				case 3: // ���
					chardata.nLang = atoi(szTemp);
					break;
				case 4: // ����
					chardata.nMath = atoi(szTemp);
					break;
				case 5: // ����
					chardata.nArt = atoi(szTemp);
					break;
				case 6: // ü��
					chardata.nStamina = atoi(szTemp);
					break;
				case 7: // �̵�
					chardata.nMove = atoi(szTemp);
					break;
				case 8: // ����
					strcpy(chardata.szComment, szTemp);
					break;
				case 9: // illu img
					strcpy(szIllu, szTemp);
					break;
				}
				k = 0;
			}
			else
				szTemp[k++] = szBuf[i];
			i++;
		}
		m_Chars[nSlot++].SetUp(chardata, szIllu);
	}
	fclose(fp);
	// end read data file
}