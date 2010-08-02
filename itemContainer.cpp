#include "itemContainer.h"
#include "const.h"
#include <stdio.h>
#include <stdlib.h>	// 이게 분명 gCharManager에서는 필요하지 않았을 텐데..
#include "gPlayerManager.h"

static itemContainer s_itemContainer; // 2

itemContainer *itemContainer::GetIF() // 3
{
	return &s_itemContainer;
}

bool itemContainer::SetUp()		// gCharManager 의 SetUp을 모방한 것이 자명하다.
{
	m_itemN = MAXCARD;

	m_item	= new ITEM[m_itemN];
	
	// read dat file
	FILE	*fp;
	
	fp = fopen(CARDDATAFILE, "rt");
	if(!fp)	return false;
	
	char		szBuf[512];
	char		szTemp[512];
	int			i, k;
	int			nSlot = 0;
	int			nCount;			// 뭐 입력하는중이냐 0 단대 1 이름 ...
	ITEM		itemTemp;
	
	// 
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
				case 0:	// index
					itemTemp.m_index = atoi(szTemp);
					break;
				case 1: // effect
					itemTemp.m_effect = atoi(szTemp);
					break;
				case 2: // flagHigh
					itemTemp.m_flagHigh = atoi(szTemp);
					break;
				case 3: // flagLow
					itemTemp.m_flagLow = atoi(szTemp);
					break;
				case 4: // activeType
					itemTemp.m_activeType = atoi(szTemp);
					break;
				case 5: // turn
					itemTemp.m_turn = atoi(szTemp);
					break;
				}
				k = 0;
			}
			else
				szTemp[k++] = szBuf[i];
			i++;
		}
		m_item[nSlot++] = itemTemp; 
	}
	fclose(fp);
	// end read data file
}

void itemContainer::itemUse(int player,int cardIndex,int activeTarget) {
	gPlayerManager* gplayerManager = gPlayerManager::GetIF();
	
	int i;
	int case5NokduSelect;
	//int case5ActiveType;
	if (m_item[cardIndex-1].m_turn==0){
		switch(m_item[cardIndex-1].m_effect){
		
		
		case 4:
			// m_flagHigh의 범용성 차단
			//switch(m_item[cardIndex-1].m_flagHigh){
			//case 1:
			// 이것은 아마 옳을 것이나 스태미너 관련 기획이 안되 있어 보류
			/*
				if(gplayerManager->m_player[activeTarget].m_nNP==-1) {
					return;
				}
				else{
					if(m_item[cardIndex-1].m_flagLow < gplayerManager->m_player[activeTarget].m_charInfo->m_Data.nStamina)
						gplayerManager->m_player[activeTarget].m_charInfo->m_Data.nStamina -= m_item[cardIndex].m_flagLow;
					else
						gplayerManager->m_player[activeTarget].m_charInfo->m_Data.nStamina = 0;	
					return;
				}
			*/
			//	break;				
			//}
			break;
		case 5:
			// 초기 space 문제가 발생
			// 모두 case 이외에는 모든 변수를 고려하지 않았다.
			//c5NS = m_item[cardIndex].m_
			//if(c5NS == 0 || c5NS == 1 || c5NS == 2)
			switch(m_item[cardIndex-1].m_flagHigh){
			case 0 :
				case5NokduSelect = 1;
				break;
			case 1:
				case5NokduSelect = 0;
				break;
			case 2:
				case5NokduSelect = -1;
				break;
			}
			if(case5NokduSelect != -1){
				switch(m_item[cardIndex-1].m_activeType){ // 상우의 대대적인 하드 코딩과 사후 복구계획 

				case 0: // 나
					gplayerManager->m_player[player].m_xSpacePos = 2;
					gplayerManager->m_player[player].m_ySpacePos = 17;
					gplayerManager->m_player[player].m_Next_xSpacePos = 2;
					gplayerManager->m_player[player].m_Next_xSpacePos = 17;
					gplayerManager->m_player[player].m_isNokdu = case5NokduSelect;
					break;
						
				case 1: // 너
					gplayerManager->m_player[activeTarget].m_xSpacePos = 2;
					gplayerManager->m_player[activeTarget].m_ySpacePos = 17;
					gplayerManager->m_player[activeTarget].m_Next_xSpacePos = 2;
					gplayerManager->m_player[activeTarget].m_Next_xSpacePos = 17;
					gplayerManager->m_player[activeTarget].m_isNokdu = case5NokduSelect;
					break;			

				case 2: // 나너
					gplayerManager->m_player[player].m_xSpacePos = 2;
					gplayerManager->m_player[player].m_ySpacePos = 17;
					gplayerManager->m_player[player].m_Next_xSpacePos = 2;
					gplayerManager->m_player[player].m_Next_xSpacePos = 17;
					gplayerManager->m_player[player].m_isNokdu = case5NokduSelect;
					gplayerManager->m_player[activeTarget].m_xSpacePos = 2;
					gplayerManager->m_player[activeTarget].m_ySpacePos = 17;
					gplayerManager->m_player[activeTarget].m_Next_xSpacePos = 2;
					gplayerManager->m_player[activeTarget].m_Next_xSpacePos = 17;
					gplayerManager->m_player[activeTarget].m_isNokdu = case5NokduSelect;
					break;

				case 3: // 나 제외
					for(i = 0 ; i < MAXPLAYER ; i++) {
						if(i == player) continue;
						if(gplayerManager->m_player[i].m_nNP==-1) continue;
						gplayerManager->m_player[i].m_xSpacePos = 2;
						gplayerManager->m_player[i].m_ySpacePos = 17;
						gplayerManager->m_player[i].m_Next_xSpacePos = 2;
						gplayerManager->m_player[i].m_Next_xSpacePos = 17;
						gplayerManager->m_player[i].m_isNokdu = case5NokduSelect;
					}
					break;
				case 4: // 모두
					for(i = 0 ; i < MAXPLAYER ; i++) {
					//	if(i == player) continue;
						if(gplayerManager->m_player[i].m_nNP==-1) continue;
						gplayerManager->m_player[i].m_xSpacePos = 2;
						gplayerManager->m_player[i].m_ySpacePos = 17;
						gplayerManager->m_player[i].m_Next_xSpacePos = 2;
						gplayerManager->m_player[i].m_Next_xSpacePos = 17;
						gplayerManager->m_player[i].m_xDrawline = 2;
						gplayerManager->m_player[i].m_yDrawline = 17;
						gplayerManager->m_player[i].m_isNokdu = case5NokduSelect;
					}
					break;
				}
			}
			break;
		case 6:
			// 대출이 제일 어려웠어요
			break;
		}	
	}
	else {
		if(case5NokduSelect != -1){
			switch(m_item[cardIndex-1].m_activeType){ // 상우의 대대적인 하드 코딩과 사후 복구계획 
				
			case 0: // 나
				gplayerManager->m_player[player].m_itemCooltime[cardIndex-1] = m_item[cardIndex-1].m_turn;
				break;
				
			case 1: // 너
				gplayerManager->m_player[activeTarget].m_itemCooltime[cardIndex-1] = m_item[cardIndex-1].m_turn;
			
				break;			
				
			case 2: // 나너
				gplayerManager->m_player[player].m_itemCooltime[cardIndex-1] = m_item[cardIndex-1].m_turn;
				gplayerManager->m_player[activeTarget].m_itemCooltime[cardIndex-1] = m_item[cardIndex-1].m_turn;
				break;
				
			case 3: // 나 제외
				for(i = 0 ; i < MAXPLAYER ; i++) {
					if(i == player) continue;
					if(gplayerManager->m_player[i].m_nNP==-1) continue;
					gplayerManager->m_player[i].m_itemCooltime[cardIndex-1] = m_item[cardIndex-1].m_turn;
				}
				break;
			case 4: // 모두
				for(i = 0 ; i < MAXPLAYER ; i++) {
					//	if(i == player) continue;
					if(gplayerManager->m_player[i].m_nNP==-1) continue;
					gplayerManager->m_player[i].m_itemCooltime[cardIndex-1] = m_item[cardIndex-1].m_turn;
				}
				break;
			}
		}
		//gplayerManager->m_player[player]
	}
}