#include "BattleNetCore.h"

static gBattleNetCore	s_BattleNetCore;

gBattleNetCore *gBattleNetCore::GetIF()
{
	return &s_BattleNetCore;
}

gBattleNetCore::gBattleNetCore()
{

}

gBattleNetCore::~gBattleNetCore()
{

}

bool gBattleNetCore::SetUp()
{
	if(!m_ImgBack.Load(BNET_FILE_BACK))
		return false;

	return true;
}

void gBattleNetCore::MainLoop()
{
	Draw();
}

void gBattleNetCore::Draw()
{
	m_ImgBack.Draw();
}

void gBattleNetCore::Release()
{
	m_ImgBack.Release();

}

void gBattleNetCore::OnLButtonDown()
{

}

void gBattleNetCore::OnLButtonUp()
{

}

void gBattleNetCore::OnMouseMove()
{

}

void gBattleNetCore::OnRButtonDown()
{

}

bool gBattleNetCore::PreTransMsg(MSG &msg)
{
	return false;
}