#include "itemContainer.h"
#include "const.h"
#include <stdio.h>
#include <stdlib.h>	// �̰� �и� gCharManager������ �ʿ����� �ʾ��� �ٵ�..
#include "gPlayerManager.h"

static itemContainer s_itemContainer; // 2

itemContainer *itemContainer::GetIF() // 3
{
	return &s_itemContainer;
}

bool itemContainer::SetUp()		// gCharManager �� SetUp�� ����� ���� �ڸ��ϴ�.
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
	int			nCount;			// �� �Է��ϴ����̳� 0 �ܴ� 1 �̸� ...
	ITEM		itemTemp;
	
	// 
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
			// m_flagHigh�� ���뼺 ����
			//switch(m_item[cardIndex-1].m_flagHigh){
			//case 1:
			// �̰��� �Ƹ� ���� ���̳� ���¹̳� ���� ��ȹ�� �ȵ� �־� ����
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
			// �ʱ� space ������ �߻�
			// ��� case �̿ܿ��� ��� ������ ������� �ʾҴ�.
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
				switch(m_item[cardIndex-1].m_activeType){ // ����� ������� �ϵ� �ڵ��� ���� ������ȹ 

				case 0: // ��
					gplayerManager->m_player[player].m_xSpacePos = 2;
					gplayerManager->m_player[player].m_ySpacePos = 17;
					gplayerManager->m_player[player].m_Next_xSpacePos = 2;
					gplayerManager->m_player[player].m_Next_xSpacePos = 17;
					gplayerManager->m_player[player].m_isNokdu = case5NokduSelect;
					break;
						
				case 1: // ��
					gplayerManager->m_player[activeTarget].m_xSpacePos = 2;
					gplayerManager->m_player[activeTarget].m_ySpacePos = 17;
					gplayerManager->m_player[activeTarget].m_Next_xSpacePos = 2;
					gplayerManager->m_player[activeTarget].m_Next_xSpacePos = 17;
					gplayerManager->m_player[activeTarget].m_isNokdu = case5NokduSelect;
					break;			

				case 2: // ����
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

				case 3: // �� ����
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
				case 4: // ���
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
			// ������ ���� ��������
			break;
		}	
	}
	else {
		if(case5NokduSelect != -1){
			switch(m_item[cardIndex-1].m_activeType){ // ����� ������� �ϵ� �ڵ��� ���� ������ȹ 
				
			case 0: // ��
				gplayerManager->m_player[player].m_itemCooltime[cardIndex-1] = m_item[cardIndex-1].m_turn;
				break;
				
			case 1: // ��
				gplayerManager->m_player[activeTarget].m_itemCooltime[cardIndex-1] = m_item[cardIndex-1].m_turn;
			
				break;			
				
			case 2: // ����
				gplayerManager->m_player[player].m_itemCooltime[cardIndex-1] = m_item[cardIndex-1].m_turn;
				gplayerManager->m_player[activeTarget].m_itemCooltime[cardIndex-1] = m_item[cardIndex-1].m_turn;
				break;
				
			case 3: // �� ����
				for(i = 0 ; i < MAXPLAYER ; i++) {
					if(i == player) continue;
					if(gplayerManager->m_player[i].m_nNP==-1) continue;
					gplayerManager->m_player[i].m_itemCooltime[cardIndex-1] = m_item[cardIndex-1].m_turn;
				}
				break;
			case 4: // ���
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