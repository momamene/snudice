 #include "gPlayer.h"
// #include "const.h"
#include "tileContainer.h"
#include "gImage.h"
#include "gGameCore.h"

bool gPlayer::SetUp (gChar *gchar)
{
	tileContainer *tilecontainer = tileContainer::GetIF();

	
	POINT bBefore,b;
	
	m_charInfo = gchar;
	for(int i = 0 ; i < 4 ; i++){
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

	return true;
}

void gPlayer::Draw() 
{
	tileContainer *tilecontainer = tileContainer::GetIF();
	gGameCore *ggameCore = gGameCore::GetIF();
	
	//POINT ij1,ij2;
	RECT rc;
/*	
	ij1.x = m_xSpacePos;//m_position.x;
	ij1.y = m_ySpacePos; //m_position.y;
	ij2 = tilecontainer->conToAbs(ij1);
	rc.left = -ggameCore->m_xPos + ij2.x;
	rc.top = -ggameCore->m_yPos + ij2.y - FULLY;
	rc.right = rc.left + FULLX;
	rc.bottom = rc.top + FULLY * 2;
*/
	// 캐릭터 드로우.
	rc.left = -ggameCore->m_xPos + m_xDrawline;
	rc.top = -ggameCore->m_yPos + m_yDrawline - FULLY;
	rc.right = rc.left + FULLX;
	rc.bottom = rc.top + FULLY * 2;
	
	m_charInfo->DrawIllu(rc);
	
}

void gPlayer::posSpacor() 
{	// 다음 칸으로 움직이라는 신호.
	gGameCore *gameCore = gGameCore::GetIF();
	tileContainer * tilecontainer = tileContainer::GetIF();
	
	m_Next_xSpacePos = tilecontainer->tileMap[m_xSpacePos*LINEY+m_ySpacePos].nextTile.x;	// 기본 방침은, Next와 Now가 괴리가 있는 상황은 움직이는 상황인 것이다.
	m_Next_ySpacePos = tilecontainer->tileMap[m_xSpacePos*LINEY+m_ySpacePos].nextTile.y;
}

void gPlayer::posMover(int frame)
{
	gGameCore *ggameCore = gGameCore::GetIF();
	tileContainer * tilecontainer = tileContainer::GetIF();

	POINT b, a;
	b.x = m_Next_xSpacePos;
	b.y = m_Next_ySpacePos;
	a.x = m_xSpacePos;
	a.y = m_ySpacePos;
	b = tilecontainer->conToAbs(b);
	a = tilecontainer->conToAbs(a);

	m_xDrawline = a.x + frame*(b.x-a.x)/MAXFRAMECOUNT;
	m_yDrawline = a.y + frame*(b.y-a.y)/MAXFRAMECOUNT;

	b.x = b.x - WNDSIZEW/2 + HALFX;
	b.y = b.y - WNDSIZEH/2 + HALFY;
	a.x = a.x - WNDSIZEW/2 + HALFX;
	a.y = a.y - WNDSIZEH/2 + HALFY;


	//ggameCore->PutScreenPos(a.x + frame*(b.x-a.x)/MAXFRAMECOUNT,a.y + frame*(b.y-a.y)/MAXFRAMECOUNT);
	//ggameCore->PutScreenPos(b.x,b.y);
	
}
void gPlayer::posStoper()
{
	m_xSpacePos = m_Next_xSpacePos;	// 기본 방침은 Next와 Now가 같은 상황은 멈춘 상황이라는 것이다.
	m_ySpacePos = m_Next_ySpacePos; // 기본 방침은 Pos는 Con 값이라는 것이다.
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
