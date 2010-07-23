#include "gGameCore.h"
#include "gMouse.h"
#include "const.h"
#include "gMainWin.h" // ��� ���� Ű������ �д´�.
#include "gInterface.h"
#include "gCharManager.h"
#include "gPlayerManager.h"
#include "time.h"


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

	m_turnN = 1;
	m_turnPlayer = 0;
	srand(time(NULL));

	m_gMode = EGM_SUBMIT;

	return true;
}

void gGameCore::MainLoopMouse1(){
	gMouse *mouse = gMouse::GetIF();
	
	if(mouse->m_nPosX < MINMOVE){
		if(m_xPos>0) m_xPos--;
	}
	if(mouse->m_nPosY < MINMOVE) {
		if(m_yPos>0) m_yPos--;
	}
	if(mouse->m_nPosX > WNDSIZEW - MINMOVE) { 
		if(m_xPos<2228-WNDSIZEW+20) m_xPos++;
	}
	if(mouse->m_nPosY > WNDSIZEH - MINMOVE){ // ������ ����
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
			m_spacor=rand()%6;
			m_frameCount=1;
			tilecontainer->posSpacor();
			gplayerManager->m_player[m_turnPlayer].posSpacor();
		}
	}
	if(!(mainWin->m_Keys[VK_SPACE])){

	}
}
void gGameCore::MainLoopMouse2(){
	tileContainer *tilecontainer = tileContainer::GetIF();
	gPlayerManager *gplayerManager = gPlayerManager::GetIF();
	

	switch(m_gMode){
	case EGM_SUBMIT:

		break;
	case EGM_GAME:

	if(m_spacor>0){
		if(m_frameCount < MAXFRAMECOUNT){ // Ȱ��ȭ ����
			tilecontainer->posMover(m_frameCount);
			gplayerManager->m_player[m_turnPlayer].posMover(m_frameCount);
			
			m_frameCount++;
		}
		else{	// ���� ����
			tilecontainer->posStoper();
			gplayerManager->m_player[m_turnPlayer].posStoper();
			m_spacor--;
			if(m_spacor>0){
				m_frameCount=1;
				tilecontainer->posSpacor();
				gplayerManager->m_player[m_turnPlayer].posSpacor();
			}
			else{
				if(m_turnPlayer>=MAXPLAYER-1){
					m_turnPlayer=0;
					tilecontainer->m_xSpacePos=gplayerManager->m_player[m_turnPlayer].m_xSpacePos;
					tilecontainer->m_ySpacePos=gplayerManager->m_player[m_turnPlayer].m_ySpacePos;
					m_turnN++;
					while(gplayerManager->m_playerState[m_turnPlayer] == EPS_NONE) m_turnPlayer++;
				}
				else{
					do m_turnPlayer++; 
					while(gplayerManager->m_playerState[m_turnPlayer] == EPS_NONE);
					tilecontainer->m_xSpacePos=gplayerManager->m_player[m_turnPlayer].m_xSpacePos;
					tilecontainer->m_ySpacePos=gplayerManager->m_player[m_turnPlayer].m_ySpacePos;
				}
				
			}
			
		}
	}
	break;
	}
}

void gGameCore::MainLoop() // MainLoop ���θ� �Լ���� �ٽ� ����ϰ� ���� �ʿ䰡 �ſ�ſ� ����
{
//	gMainWin *mainWin = gMainWin::GetIF(); // mainWin�̶�� ���� Ű������ �д´�.
	
	switch(m_gMode){
	case EGM_SUBMIT:
	break;

	case EGM_GAME:	
	MainLoopKeyboard();
	MainLoopMouse1();	
	break;
	}
	MainLoopMouse2();
	Draw();
}

void gGameCore::Draw()
{
	tileContainer::GetIF()->Draw();
	switch(m_gMode){
	case EGM_SUBMIT:
		break;
	case EGM_GAME:
		gPlayerManager::GetIF()->Draw();
		gInterface::GetIF()->Draw();
		break;
	}
	
	//temp
	//a.Draw();
	// temp end
}


void gGameCore::OnLButtonDown()
{
	gMouse *mouse = gMouse::GetIF();
	tileContainer *tilecontainer = tileContainer::GetIF();
	gPlayerManager * gplayerManager = gPlayerManager::GetIF();

	int i;
	switch(m_gMode){
	case EGM_SUBMIT:
		for(i = 0 ; i < tilecontainer->m_subjectN ; i++){
			if(mouse->m_nPosX < 100 && mouse->m_nPosY > i*20 && mouse->m_nPosY < (i+1)*20){
				m_selectSubject = tilecontainer->m_subject[i];	// �Է� �����ε�. �� �̷� �ڵ�� ���������� ���� �ʾƿ�. �츮 ��ü�����ؾ���.
				gplayerManager->m_player[m_turnPlayer].m_subjectGrader.m_subject[m_turnN-1] = m_selectSubject;
				gplayerManager->m_player[m_turnPlayer].m_subjectGrader.m_subjectN++;
				if(m_turnPlayer>=MAXPLAYER-1){
					if(m_turnN<=6){
						m_turnN++;
						m_turnPlayer=0;
					}
					else{
						m_gMode=EGM_GAME;
						m_turnN=1;
						m_turnPlayer=0;
					}
				}
				else{
					m_turnPlayer++;
				}
				break;
			}
		}
		
		

		

	break;
	case EGM_GAME:
		gInterface::GetIF()->OnLButtonDown();
	}
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