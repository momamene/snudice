#include "GameCore.h"
#include "PopUp.h"
#include "Util.h"
#include "stringconst.h"
#include "MainWin.h"
#include "Map.h"
#include "Mouse.h"

#define MINMOVE			20
#define WORLDX			2228
#define WORLDY			1520

static gGameCore s_GameCore;

gGameCore *gGameCore::GetIF()
{
	return &s_GameCore;
}

gGameCore::gGameCore(void)
{
}

gGameCore::~gGameCore(void)
{
}

bool gGameCore::SetUp()
{
	return true;
}

void gGameCore::MainLoop()
{
	MainLoopMouse();		// 마우스 스크롤
	Draw();

	// popup 창 처리
	if(gPopUp::GetIF()->isPopUp())
	{
		gPopUp::GetIF()->MainLoop();
		return;
	}

	if(gPopUp::GetIF()->m_bReturn)
	{
		switch(gPopUp::GetIF()->m_ePop)
		{
			case EPOP_DISCONNECT:
				switch(gPopUp::GetIF()->m_eBtnClk)
				{
					case ECLK_OK:
						gMainWin::GetIF()->Exit();
						break;
				}
				break;
		}
		gPopUp::GetIF()->m_bReturn = false;
	}
}

void gGameCore::MainLoopMouse()
{
	gMouse	*mouse = gMouse::GetIF();
	gMap	*map = gMap::GetIF();

	if(mouse->m_nPosX < MINMOVE)
	{
		if(map->m_nAbsDrawlineX > 0)
			map->m_nAbsDrawlineX -= 2;
	}
	if(mouse->m_nPosY < MINMOVE)
	{
		if(map->m_nAbsDrawlineY > 0)
			map->m_nAbsDrawlineY -= 2;
	}
	if(mouse->m_nPosX > WNDSIZEW - MINMOVE)
	{ 
		if(map->m_nAbsDrawlineX < WORLDX - WNDSIZEW + MINMOVE)
			map->m_nAbsDrawlineX += 2;
	}
	if(mouse->m_nPosY > WNDSIZEH - MINMOVE)
	{ // 수학적 공식
		if(map->m_nAbsDrawlineY < WORLDY + FULLY * 2 - WNDSIZEH + MINMOVE)
			map->m_nAbsDrawlineY += 2;
	}
}



void gGameCore::Draw()
{
	gMap::GetIF()->Draw();
}

void gGameCore::Release()
{

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

bool gGameCore::PreTransMsg(MSG &msg)
{
	return false;
}