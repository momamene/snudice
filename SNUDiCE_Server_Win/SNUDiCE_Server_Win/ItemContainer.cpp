#include "ItemContainer.h"
#include <stdio.h>

#define ITEMSCRIPT			".\\Data\\itemdata.dat"

static gItemContainer s_ItemContainer;

gItemContainer *gItemContainer::GetIF()
{
	return &s_ItemContainer;
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

}
