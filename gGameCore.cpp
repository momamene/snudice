#include "gGameCore.h"

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
	tileContainer::GetIF()->Setup();
	tileContainer::GetIF()->Load();
	//MainLoop();
	return true;
}

void gGameCore::MainLoop()
{
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