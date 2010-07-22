#include "gGameCore.h"
#include "gMouse.h"
#include "const.h"
#include "gMainWin.h" // ��� ���� Ű������ �д´�.
#include "gInterface.h"
#include "gCharManager.h"
#include "gPlayerManager.h"


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
	gCharManager *gcharManager = gCharManager::GetIF();
	m_xPos=0;
	m_yPos=0;
	m_minimapOn=0;
	m_spacor=0;
	m_frameCount = 0;
	tileContainer::GetIF()->Setup();
	gPlayerManager::GetIF()->SetUp();
	
	
	// temp
	//a.SetUp(gcharManager->m_Chars[10]);
	// temp end

	return true;
}

void gGameCore::MainLoopMouse(){
	gMouse *mouse = gMouse::GetIF();
	
	if(mouse->m_nPosX < MINMOVE){
		if(m_xPos>0) m_xPos--;
	}
	if(mouse->m_nPosY < MINMOVE) {
		if(m_yPos>0) m_yPos--;
	}
	if(mouse->m_nPosX > WNDSIZEW - MINMOVE) { 
		//if(m_xPos<(LINEX/2+LINEX%2)*WIDEX-MIDDLEX-WNDSIZEW+20) m_xPos++;
		if(m_xPos<2228-WNDSIZEW+20) m_xPos++;
	}
	if(mouse->m_nPosY > WNDSIZEH - MINMOVE){ // ������ ����
		//if(m_yPos<(LINEY)*FULLY-WNDSIZEH+20) m_yPos++;
		if(m_yPos<1520-WNDSIZEH+20) m_yPos++;
	}

}

void gGameCore::MainLoopKeyboard(){
	
	gMainWin *mainWin = gMainWin::GetIF(); // mainWin�̶�� ���� Ű������ �д´�.
	tileContainer *tilecontainer = tileContainer::GetIF();
	gPlayerManager *gplayerManager = gPlayerManager::GetIF();
	if(mainWin->m_Keys['M']){
		if(m_minimapOn==0) m_minimapOn=1;
		if(m_minimapOn==2) m_minimapOn=3;
	}
	if(!(mainWin->m_Keys['M'])){
		if(m_minimapOn==1) m_minimapOn=2;
		if(m_minimapOn==3) m_minimapOn=0;
	}
	
	if(mainWin->m_Keys[VK_SPACE]){
		if(m_spacor==0) {
			m_spacor=1;
			m_frameCount=1;
			tilecontainer->posSpacor();
			gplayerManager->m_player[0].posSpacor();
		}
	}
	if(!(mainWin->m_Keys[VK_SPACE])){

	}
}

void gGameCore::MainLoop() // MainLoop ���θ� �Լ���� �ٽ� ����ϰ� ���� �ʿ䰡 �ſ�ſ� ����
{
//	gMainWin *mainWin = gMainWin::GetIF(); // mainWin�̶�� ���� Ű������ �д´�.
	tileContainer *tilecontainer = tileContainer::GetIF();
	gPlayerManager *gplayerManager = gPlayerManager::GetIF();

	MainLoopMouse();
	MainLoopKeyboard();
	if(m_spacor==1){
		if(m_frameCount < MAXFRAMECOUNT){
			tilecontainer->posMover(m_frameCount);
			gplayerManager->m_player[0].posMover(m_frameCount);
			
			m_frameCount++;
		}
		else{
			tilecontainer->posStoper();
			gplayerManager->m_player[0].posStoper();
			m_spacor=0;
		}
	}
	Draw();
}

void gGameCore::Draw()
{
	tileContainer::GetIF()->Draw();
	gInterface::GetIF()->Draw();
	gPlayerManager::GetIF()->Draw();
	
	//temp
	//a.Draw();
	// temp end
}

void gGameCore::OnLButtonDown()
{
	gInterface::GetIF()->OnLButtonDown();
}

void gGameCore::OnLButtonUp()
{
	gInterface::GetIF()->OnLButtonUp();
}

void gGameCore::OnMouseMove()
{
	gInterface::GetIF()->OnMouseMove();
}

void gGameCore::OnRButtonDown()
{
	gInterface::GetIF()->OnRButtonDown();	
}

void gGameCore::PutScreenPos(int x,int y){
	m_xPos = x;
	m_yPos = y;
}