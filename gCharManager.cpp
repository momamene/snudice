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
	int			nCount;			// 뭐 입력하는중이냐 0 단대 1 이름 ...
	CHARDATA	chardata;

	// 단과대학, 이름, 성별(남1여0), 언어, 수리, 예능, 체력, 이동, 기타설명, 이미지
	while(fgets(szBuf, 512, fp) != NULL)
	{
		if(szBuf[0] == '/' && szBuf[1] == '/')	continue;		// 주석일 경우
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
				case 0:	// 단과대학
					strcpy(chardata.szColleage, szTemp);
					break;
				case 1: // 이름
					strcpy(chardata.szName, szTemp);
					break;
				case 2: // 성별
					if(strcmp(szTemp, "남") == 0)
						chardata.eSex = ESEX_MALE;
					else
						chardata.eSex = ESEX_FEMALE;
					break;
				case 3: // 언어
					chardata.nLang = atoi(szTemp);
					break;
				case 4: // 수리
					chardata.nMath = atoi(szTemp);
					break;
				case 5: // 예능
					chardata.nArt = atoi(szTemp);
					break;
				case 6: // 체력
					chardata.nStamina = atoi(szTemp);
					break;
				case 7: // 이동
					chardata.nMove = atoi(szTemp);
					break;
				case 8: // 설명
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