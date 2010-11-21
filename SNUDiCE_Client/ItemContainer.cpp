#include "ItemContainer.h"
#include <stdio.h>

#define ITEMSCRIPT			".\\Data\\itemdata.dat"

static gItemContainer s_ItemContainer;

gItemContainer *gItemContainer::GetIF()
{
	return &s_ItemContainer;
}

gItemContainer::gItemContainer(void)
{
}

gItemContainer::~gItemContainer(void)
{
}


bool gItemContainer::SetUp()
{
	FILE		*fp;

	fp = fopen(ITEMSCRIPT, "rt");
	if(!fp)
		return false;

	int			i, k;
	int			nIndex = 0;		// 몇번째 아이템 입력중이냐
	int			nCount;			// 뭐입력중이나.
	char		szBuf[256];
	char		szTemp[256];

	while( fgets(szBuf, 256, fp) != NULL)
	{
		if(szBuf[0] == '/' && szBuf[1] == '/')
			continue;								// 주석 건너뛰기

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
				case 0:	// itemtype
					{
						ITEMTYPE	type;
						if( strcmp(szTemp, "ITEM_STAT") == 0 )
							type = ITEM_STAT;
						else if( strcmp(szTemp, "ITEM_STAMINA") == 0 )
							type = ITEM_STAMINA;
//						else if( strcmp(szTemp, "ITEM_GRADE" ) == 0 )
//							type = ITEM_GRADE;
						else if( strcmp(szTemp, "ITEM_MOVESELECT") == 0)
							type = ITEM_MOVESELECT;
						else if( strcmp(szTemp, "ITEM_MOVEPLACE") == 0)
							type = ITEM_MOVEPLACE;
						else if( strcmp(szTemp, "ITEM_NOCLASS") == 0)
							type = ITEM_NOCLASS;
						else if( strcmp(szTemp, "ITEM_TOGETHERCLASS") == 0)
							type = ITEM_TOGETHERCLASS;
						else if( strcmp(szTemp, "ITEM_DASH") == 0)
							type = ITEM_DASH;
						else if( strcmp(szTemp, "ITEM_POWERDASH") == 0)
							type = ITEM_POWERDASH;
						else if( strcmp(szTemp, "ITEM_LOVE") == 0)
							type = ITEM_LOVE;
						else
							return false;

						m_ItemList[nIndex].type = type;
					}
					break;
				case 1:	// target
					{
						ITEMTARGET	target;
						if(strcmp(szTemp, "TARGET_ME") == 0)
							target = TARGET_ME;
						else if(strcmp(szTemp, "TARGET_ALL") == 0)
							target = TARGET_ALL;
						else if(strcmp(szTemp, "TARGET_ALLEXCEPTME") == 0)
							target = TARGET_ALLEXCEPTME;
						else if(strcmp(szTemp, "TARGET_OTHER") == 0)
							target = TARGET_OTHER;
						else if(strcmp(szTemp, "TARGET_MEOTHER") == 0)
							target = TARGET_MEOTHER;
						else if(strcmp(szTemp, "TARGET_OTHERSEX") == 0)
							target = TARGET_OTHERSEX;
						else if(strcmp(szTemp, "TARGET_MYCOUPLE") == 0)
							target = TARGET_MYCOUPLE;
						else if(strcmp(szTemp, "TARGET_OTHERCOUPLE") == 0)
							target = TARGET_OTHERCOUPLE;
						else if(strcmp(szTemp, "TARGET_ALLCOUPLE") == 0)
							target = TARGET_ALLCOUPLE;
						else if(strcmp(szTemp, "TARGET_ALLSINGLE") == 0)
							target = TARGET_ALLSINGLE;
						else
							return false;

						m_ItemList[nIndex].target = target;
					}
					break;
				case 2: // lang
					m_ItemList[nIndex].nLang = atoi(szTemp);
					break;
				case 3: // math
					m_ItemList[nIndex].nMath = atoi(szTemp);
					break;
				case 4: // art
					m_ItemList[nIndex].nArt = atoi(szTemp);
					break;
				case 5: // move
					m_ItemList[nIndex].nMove = atoi(szTemp);
					break;
				case 6: // stamina
					m_ItemList[nIndex].nStamina = atoi(szTemp);
					break;
				case 7: // multi
					m_ItemList[nIndex].nMulti = atoi(szTemp);
					break;
				case 8: // exist turn
					m_ItemList[nIndex].nExistTurn = atoi(szTemp);
					break;
				case 9: // pos
					m_ItemList[nIndex].nPos = atoi(szTemp);
					break;
				case 10: // love
					m_ItemList[nIndex].nLove = atoi(szTemp);
					break;
				case 11: // img
					if(!m_ItemImg[nIndex].Load(szTemp))
						return false;
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

void gItemContainer::Release()
{
	int			i;

	for(i = 0; i < ITEMNUM; i++)
		m_ItemImg[i].Release();

}

bool gItemContainer::Restore()
{
	int			i;

	for(i = 0; i < ITEMNUM; i++)
		if(!m_ItemImg[i].Restore())
			return false;

	return true;
}
