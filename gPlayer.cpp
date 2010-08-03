 #include "gPlayer.h"
 #include "const.h"
#include "tileContainer.h"
#include "gImage.h"
#include "gGameCore.h"
#include "gTimer.h"
#include "itemContainer.h"
#include "gPopUp.h"

bool gPlayer::SetUp (gChar *gchar)
{
	tileContainer *tilecontainer = tileContainer::GetIF();
	int i;

	
	POINT bBefore,b;
	
	m_charInfo = gchar;
	for(i = 0 ; i < 4 ; i++){
		m_myItem[i] = 0;
	}
	m_xSpacePos = tilecontainer->m_xInitSpacePos;
	m_ySpacePos = tilecontainer->m_yInitSpacePos;
	m_Next_xSpacePos = m_xSpacePos;
	m_Next_ySpacePos = m_ySpacePos;
//	m_positionRare = m_position;
//	m_positionFinal = m_position;
	bBefore.x = m_xSpacePos;
	bBefore.y = m_ySpacePos;
	
	b = tilecontainer->conToAbs(bBefore);
	
	m_xDrawline = b.x; // a.x + frame*(b.x-a.x)/MAXFRAMECOUNT;
	m_yDrawline = b.y; // a.y + frame*(b.y-a.y)/MAXFRAMECOUNT;

	m_subjectGrader.init(); //m_subjectN = 0;

	m_isNokdu = false;

	m_moveFoot = 1;
	m_movePosition = 0;
	//memset(0,m_itemCooltime);
	for(i = 0 ; i < MAXCARD ; i++)
		m_itemCooltime[i] = 0;

	return true;
}

void gPlayer::Draw() 
{
	tileContainer *tilecontainer = tileContainer::GetIF();
	gGameCore *ggameCore = gGameCore::GetIF();
	
	RECT rc;

	rc.left = -ggameCore->m_xPos + m_xDrawline + 15;
	rc.top = -ggameCore->m_yPos + m_yDrawline - FULLY;
	rc.right = rc.left + DOT_WIDTH;
	rc.bottom = rc.top + DOT_HEIGHT;

// 	if(m_movePosition==-1)
// 		//m_charInfo->DrawIllu(rc);
// 		m_charInfo->DrawDot(rc,m_moveFoot,m_movePosition);
// 	else
		m_charInfo->DrawDot(rc,m_moveFoot,m_movePosition);
	
}

void gPlayer::posSpacor() 
{	// 다음 칸으로 움직이라는 신호.
	gGameCore *gameCore = gGameCore::GetIF();
	tileContainer * tilecontainer = tileContainer::GetIF();

	if(tilecontainer->m_xInitSpacePos == m_xSpacePos && tilecontainer->m_yInitSpacePos == m_ySpacePos && m_isNokdu)
	{
		m_Next_xSpacePos = tilecontainer->tileMap[m_xSpacePos*LINEY+m_ySpacePos].flag1; // gplayerManager->m_player[gameCore->m_turnPlayer]->m_charInfo;
		m_Next_ySpacePos = tilecontainer->tileMap[m_xSpacePos*LINEY+m_ySpacePos].flag2; // gplayerManager->m_player[gameCore->m_turnPlayer];
	}
	else
	{
		m_Next_xSpacePos = tilecontainer->tileMap[m_xSpacePos*LINEY+m_ySpacePos].nextTile.x;	// 기본 방침은, Next와 Now가 괴리가 있는 상황은 움직이는 상황인 것이다.
		m_Next_ySpacePos = tilecontainer->tileMap[m_xSpacePos*LINEY+m_ySpacePos].nextTile.y;
	}
	if(m_xSpacePos < m_Next_xSpacePos) m_movePosition = 3;
	else if(m_xSpacePos > m_Next_xSpacePos) m_movePosition = 1;
	else if(m_ySpacePos < m_Next_ySpacePos) m_movePosition = 0;
	else if(m_ySpacePos > m_Next_ySpacePos) m_movePosition = 2;
//	else m_movePosition = -1;

}

void gPlayer::posMover(int frame)
{
	gGameCore *ggameCore = gGameCore::GetIF();
	tileContainer * tilecontainer = tileContainer::GetIF();
	gTimer *gtimer = gTimer::GetIF();

	int frameMax = gtimer->m_frame;

	POINT b, a;
	b.x = m_Next_xSpacePos;
	b.y = m_Next_ySpacePos;
	a.x = m_xSpacePos;
	a.y = m_ySpacePos;
	b = tilecontainer->conToAbs(b);
	a = tilecontainer->conToAbs(a);

	m_xDrawline = a.x + frame*(b.x-a.x)/(gtimer->m_frame);
	m_yDrawline = a.y + frame*(b.y-a.y)/(gtimer->m_frame);

	if(frame<frameMax/4) m_moveFoot = 1;
	else if(frame<frameMax/2) m_moveFoot = 0;
	else if(frame<(frameMax*3)/4) m_moveFoot = 1;
	else m_moveFoot = 2;

	b.x = b.x - WNDSIZEW/2 + HALFX;
	b.y = b.y - WNDSIZEH/2 + HALFY;
	a.x = a.x - WNDSIZEW/2 + HALFX;
	a.y = a.y - WNDSIZEH/2 + HALFY;

	
}

void gPlayer::posStoper()
{
	tileContainer *tilecontainer = tileContainer::GetIF();
	m_xSpacePos = m_Next_xSpacePos;	// 기본 방침은 Next와 Now가 같은 상황은 멈춘 상황이라는 것이다.
	m_ySpacePos = m_Next_ySpacePos; // 기본 방침은 Pos는 Con 값이라는 것이다.
	/*
	if(m_xSpacePos==tilecontainer->m_xInitSpacePos&&m_ySpacePos==tilecontainer->m_yInitSpacePos){
		if(m_isNokdu) m_isNokdu = false;
		else m_isNokdu = true;
	}
	*/ 
//	m_movePosition = -1;
	m_moveFoot = 1;
}

void gPlayer::Release()
{

}

bool gPlayer::isMySubject(int flag)
{
	for(int i = 0 ; i < m_subjectGrader.m_subjectN ; i++ )
		if(m_subjectGrader.m_subject[i]==flag) return true;
	return false;
}

int gPlayer::meetItemCalculator(int classType,int originalVal) {
	itemContainer* itemcontainer = itemContainer::GetIF();

	int i;
	int convertedVal = originalVal;

	for (i = 0 ; i < MAXCARD ; i++){

  		if(m_itemCooltime[i]==0) continue;


		if(itemcontainer->m_item[i].m_effect==0 || itemcontainer->m_item[i].m_effect==classType+1 ){

			if(itemcontainer->m_item[i].m_flagHigh==0) convertedVal += itemcontainer->m_item[i].m_flagLow;
			else if (itemcontainer->m_item[i].m_flagHigh==1){
       				convertedVal -= itemcontainer->m_item[i].m_flagLow;
			}
		}
	}
	for (i = 0 ; i < MAXCARD ; i++){
		if(m_itemCooltime[i]==0) continue;
		if(itemcontainer->m_item[i].m_effect==0 || itemcontainer->m_item[i].m_effect==classType+1 ){
			if(itemcontainer->m_item[i].m_flagHigh==2) convertedVal *= itemcontainer->m_item[i].m_flagLow;
		}
	}

	if(convertedVal < 0 ) convertedVal = 0;

	return convertedVal*20;
}

void gPlayer::meet()
{
	tileContainer *tilecontainer = tileContainer::GetIF();
	gGameCore *gameCore = gGameCore::GetIF();
	int tile = m_xSpacePos*LINEY+m_ySpacePos;
	bool boolo = (tilecontainer->tileMap[tile].tileType==TY_CLASS);
	int flag2 = tilecontainer->tileMap[tile].flag2;                  
	//m_player[m_turnPlayer].m_subjectGrader.meet(flag2);
			
	

	//int tile = tilecontainer->flagToFirstTile(subjectIndex);
	for(int i = 0 ; i < m_subjectGrader.m_subjectN ; i++ ){
		if(boolo && m_subjectGrader.m_subject[i]==flag2){
			m_subjectGrader.m_meetCount[i]++;
			
			// 수업이름
			// n의 성취도 획득!!  <- 이렇게 띄워지게 바꿔라

			gPopUp::GetIF()->SetImgPopUp(ECLK_OK, &m_charInfo->m_ImgPopup, "수업 이름", "n의 성취도 획득!!");
			
			if(tilecontainer->tileMap[tile].flag3==0)
				m_subjectGrader.m_weightCount[i] += meetItemCalculator(0,m_charInfo->m_Data.nLang);
			else if (tilecontainer->tileMap[tile].flag3==1)
				m_subjectGrader.m_weightCount[i] += meetItemCalculator(1,m_charInfo->m_Data.nMath);
			else if (tilecontainer->tileMap[tile].flag3==2)
				m_subjectGrader.m_weightCount[i] += meetItemCalculator(2,m_charInfo->m_Data.nArt);
				
		}
	}
}