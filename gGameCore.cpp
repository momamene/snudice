#include "gGameCore.h"
#include "gMouse.h"
#include "const.h"


//------------------------------------------------------------------------------------
//	Constructor	/	Destructor
//------------------------------------------------------------------------------------

static gGameCore s_GameCore;

gGameCore *gGameCore::GetIF()
{
	return &s_GameCore;
}

gGameCore::gGameCore()
{

}

gGameCore::~gGameCore()
{

}

bool gGameCore::SetUp()
{
	m_xPos=0;
	m_yPos=0;
	tileContainer::GetIF()->Setup();
	//tileContainer::GetIF()->Load();
	//MainLoop();
	return true;
}

void gGameCore::MainLoop()
{
	gMouse *mouse = gMouse::GetIF();
	
	if(mouse->m_nPosX < MINMOVE){
		if(m_xPos>0) m_xPos--;
	}
	else if(mouse->m_nPosY < MINMOVE) {
		if(m_yPos>0) m_yPos--;
	}
	if(mouse->m_nPosX > WNDSIZEW - MINMOVE) { // 미친 수작업.
		if(m_xPos<(LINEX/2+LINEX%2)*WIDEX-LEFTX-WNDSIZEW) m_xPos++;
	}
	if(mouse->m_nPosY > WNDSIZEH - MINMOVE){ // 미친 수작업. 수학 공식 그런거 없음.
		if(m_yPos<(LINEY+2)*FULLY-WNDSIZEW+10) m_yPos++;
	}
	Draw();
}

void gGameCore::Draw()
{
	tileContainer::GetIF()->Draw();
}

void gGameCore::OnLButtonDown()
{
	
}

void gGameCore::OnLButtonUp()
{
	
}

void gGameCore::OnMouseMove()
{
	
	
}

void gGameCore::OnRButtonDown()
{
	
}