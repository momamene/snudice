#include "gGameCore.h"
#include "gMouse.h"
#include "const.h"
#include "gMainWin.h" // 라고 쓰고 키보드라고 읽는다.
#include "gInterface.h"
#include "gCharManager.h"
#include "gPlayerManager.h"
#include "gUtil.h"
#include "time.h"

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
	if(FAILED(SetUp_CharSelect()))
		return false;

	gCharManager *gcharManager = gCharManager::GetIF();
	m_xPos=0;
	m_yPos=0;
	m_minimapOn=0;
	m_spacor=0;
	m_frameCount = 0;
	tileContainer::GetIF()->Setup();

	m_turnN = 1;
	m_turnPlayer = 0;
	srand(time(NULL));

	m_gMode = EGM_CHARSEL;

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
		if(m_xPos<2228-WNDSIZEW+20) m_xPos++;
	}
	if(mouse->m_nPosY > WNDSIZEH - MINMOVE){ // 수학적 공식
		if(m_yPos<1520-WNDSIZEH+20) m_yPos++;
	}

}

void gGameCore::MainLoopKeyboard(){
	
	gMainWin *mainWin = gMainWin::GetIF(); // mainWin이라고 쓰고 키보드라고 읽는다.
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
void gGameCore::MainLoopMove(){
	tileContainer *tilecontainer = tileContainer::GetIF();
	gPlayerManager *gplayerManager = gPlayerManager::GetIF();
	

	switch(m_gMode){
	case EGM_SUBMIT:

		break;
	case EGM_GAME:

	if(m_spacor>0){
		if(m_frameCount < MAXFRAMECOUNT){ // 활성화 조건
			tilecontainer->posMover(m_frameCount);
			gplayerManager->m_player[m_turnPlayer].posMover(m_frameCount);
			
			m_frameCount++;
		}
		else{	// 종료 조건
			tilecontainer->posStoper();
			gplayerManager->m_player[m_turnPlayer].posStoper();
			m_spacor--;
			if(m_spacor>0){
				m_frameCount=1;
				tilecontainer->posSpacor();
				gplayerManager->m_player[m_turnPlayer].posSpacor();
			}
			else{	// 실제 종료 조건
				gplayerManager->m_player[m_turnPlayer].m_subjectGrader.meet(gplayerManager->m_player[m_turnPlayer].m_xSpacePos*100+gplayerManager->m_player[m_turnPlayer].m_ySpacePos);

				if(m_turnPlayer>=MAXPLAYER-1){
					m_turnPlayer=0;
					tilecontainer->m_xSpacePos=gplayerManager->m_player[m_turnPlayer].m_xSpacePos;
					tilecontainer->m_ySpacePos=gplayerManager->m_player[m_turnPlayer].m_ySpacePos;
					m_turnN++;
					while(gplayerManager->m_player[m_turnPlayer].m_nNP == -1) m_turnPlayer++;
				}
				else{
					do m_turnPlayer++; 
					while(gplayerManager->m_player[m_turnPlayer].m_nNP == -1);
					tilecontainer->m_xSpacePos = gplayerManager->m_player[m_turnPlayer].m_xSpacePos;
					tilecontainer->m_ySpacePos = gplayerManager->m_player[m_turnPlayer].m_ySpacePos;
				}
				
			}
			
		}
	}
	break;
	}
}

void gGameCore::MainLoop() // MainLoop 내부를 함수들로 다시 깔끔하게 만들 필요가 매우매우 있음
{
//	gMainWin *mainWin = gMainWin::GetIF(); // mainWin이라고 쓰고 키보드라고 읽는다.
	
	switch(m_gMode)
	{
	case EGM_CHARSEL:
		break;
	case EGM_SUBMIT:
		break;
	case EGM_GAME:	
		MainLoopKeyboard();
		MainLoopMouse();	
		MainLoopMove();
		break;
	}
	Draw();
}

void gGameCore::Draw()
{
	switch(m_gMode){
	case EGM_CHARSEL:
		Draw_CharSelect();
		break;
	case EGM_SUBMIT:
//		gInterface::GetIF()->Draw();
		break;
	case EGM_GAME:
		tileContainer::GetIF()->Draw();
		gPlayerManager::GetIF()->Draw();
		gInterface::GetIF()->Draw();
		break;
	}
	
	//temp
	//
	// temp end
}

void gGameCore::OnLButtonDownSubmit(){
	gMouse *mouse = gMouse::GetIF();
	tileContainer *tilecontainer = tileContainer::GetIF();
	gPlayerManager * gplayerManager = gPlayerManager::GetIF();

	for(int i = 0 ; i < tilecontainer->m_subjectN ; i++){
		if(mouse->m_nPosX < 100 && mouse->m_nPosY > i*20 && mouse->m_nPosY < (i+1)*20){
			m_selectSubject = tilecontainer->m_subject[i];	// 입력 구문인데. 아 이런 코드는 전반적으로 좋지 않아요. 우리 객체지향해야지.
			gplayerManager->m_player[m_turnPlayer].m_subjectGrader.m_subject[m_turnN-1] = m_selectSubject;
			gplayerManager->m_player[m_turnPlayer].m_subjectGrader.m_subjectN++;
			if(m_turnPlayer>=MAXPLAYER-1){
				if(m_turnN < 6){
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

}


void gGameCore::OnLButtonDown()
{
	switch(m_gMode)
	{
		case EGM_CHARSEL:
			OnLButtonDown_CharSel();
			break;
		case EGM_SUBMIT:
			OnLButtonDownSubmit();	
			break;
		case EGM_GAME:
			gInterface::GetIF()->OnLButtonDown();
			break;
	}
}

void gGameCore::OnLButtonUp()
{
	switch(m_gMode)
	{
		case EGM_CHARSEL:
			break;
		case EGM_GAME:
			gInterface::GetIF()->OnLButtonUp();
			break;
	}
}

void gGameCore::OnMouseMove()
{
	switch(m_gMode)
	{
	case EGM_CHARSEL:
		OnMouseMove_CharSel();
		break;
	case EGM_GAME:
		gInterface::GetIF()->OnMouseMove();
		break;
	}
}

void gGameCore::OnRButtonDown()
{
	gInterface::GetIF()->OnRButtonDown();	
}

void gGameCore::PutScreenPos(int x,int y){
	m_xPos = x;
	m_yPos = y;
}

void gGameCore::Draw_CharSelect()
{
	m_ImgSelBack.Draw();

	int		i;
	RECT	rcDest;
	RECT	rcSour;

	m_BtnStart.Draw();

	for(i = 0; i < CHARNUM; i++)
		m_ImgID[i].Draw();

	for(i = 0; i < CHARNUM; i++)
	{
		if(m_nSelected[i] < 0) continue;
		rcDest = m_ImgID[i].m_rcPos;
		rcDest.left		-= CSEL_POS_OUTLINEX;
		rcDest.top		-= CSEL_POS_OUTLINEY;
		rcDest.right	= rcDest.left + CSEL_POS_OUTLINEW;
		rcDest.bottom	= rcDest.top + CSEL_POS_OUTLINEH;
		SetRect(&rcSour, 0, 0, CSEL_POS_OUTLINEW, CSEL_POS_OUTLINEH);

		switch(m_nSelected[i])
		{
			case 0:
				OffsetRect(&rcSour, CSEL_POS_OUTLINEW * 0, 0);
				break;
			case 1:
				OffsetRect(&rcSour, CSEL_POS_OUTLINEW * 1, 0);
				break;
			case 2:
				OffsetRect(&rcSour, CSEL_POS_OUTLINEW * 2, 0);
				break;
			case 3:
				OffsetRect(&rcSour, CSEL_POS_OUTLINEW * 3, 0);
				break;
		}
		m_ImgOutline.Draw(rcDest, rcSour);
	}


	// 누가 고를 차례냐
	SetRect(&rcDest,	CSEL_POS_PLAYERX,
						CSEL_POS_PLAYERY,
						CSEL_POS_PLAYERX + CSEL_POS_PLAYERW,
						CSEL_POS_PLAYERY + CSEL_POS_PLAYERH );
	SetRect(&rcSour, 0, 0, CSEL_POS_PLAYERW, CSEL_POS_PLAYERH );

	OffsetRect(&rcSour, 0, CSEL_POS_PLAYERH * m_nPlayer);
	m_ImgWho.Draw(rcDest, rcSour, false);

	// 캐릭터 일러 그리기
	SetRect(&rcDest,	CSEL_POS_ILLUX,
						CSEL_POS_ILLUY,
						CSEL_POS_ILLUX + CSEL_POS_ILLUW,
						CSEL_POS_ILLUY + CSEL_POS_ILLUH );

	gChar	*charac = &gCharManager::GetIF()->m_Chars[m_nSel];
	charac->DrawIllu(rcDest);
	
	// 캐릭터 정보 출력
	HDC			hdc;
	char		szBuf[128];
	
	gUtil::BeginText();
	wsprintf(szBuf, "이름 : %s", charac->m_Data.szName);
	gUtil::Text(CSEL_POS_CHARINFOX, CSEL_POS_CHARINFOY, szBuf);
	
	if(charac->m_Data.eSex == ESEX_MALE)
		wsprintf(szBuf, "성별 : ♂");
	else
		wsprintf(szBuf, "성별 : ♀");
	gUtil::Text(CSEL_POS_CHARINFOX + 150, CSEL_POS_CHARINFOY, szBuf);
	
	wsprintf(szBuf, "소속 : %s", charac->m_Data.szColleage);
	gUtil::Text(CSEL_POS_CHARINFOX, CSEL_POS_CHARINFOY + 20, szBuf);
	wsprintf(szBuf, "언어 : %d", charac->m_Data.nLang);
	gUtil::Text(CSEL_POS_CHARINFOX, CSEL_POS_CHARINFOY + 40, szBuf);
	wsprintf(szBuf, "수리 : %d", charac->m_Data.nMath);
	gUtil::Text(CSEL_POS_CHARINFOX, CSEL_POS_CHARINFOY + 60, szBuf);
	wsprintf(szBuf, "예능 : %d", charac->m_Data.nArt);
	gUtil::Text(CSEL_POS_CHARINFOX, CSEL_POS_CHARINFOY + 80, szBuf);
	wsprintf(szBuf, "체력 : %d", charac->m_Data.nStamina);
	gUtil::Text(CSEL_POS_CHARINFOX, CSEL_POS_CHARINFOY + 100, szBuf);
	wsprintf(szBuf, "이동 : %d", charac->m_Data.nMove);
	gUtil::Text(CSEL_POS_CHARINFOX, CSEL_POS_CHARINFOY + 120, szBuf);
	
	gUtil::Text(CSEL_POS_CHARINFOX, CSEL_POS_CHARINFOY + 140, charac->m_Data.szComment);
	
	gUtil::EndText();

}

bool gGameCore::SetUp_CharSelect()
{
	if(FAILED(m_ImgSelBack.Load(CSEL_IMG_BACK)))
		return false;

	// player n
	if(FAILED(m_ImgWho.Load(CSEL_IMG_PLAYER)))
		return false;

	// outline
	if(FAILED(m_ImgOutline.Load(CSEL_IMG_OUTLINE)))
		return false;

	memset(m_nSelected, -1, sizeof(int) * CHARNUM);

	m_nSel			= 0;
	m_nPlayer		= 0;

	RECT		rcBtn;
	// 시작버튼
	SetRect(&rcBtn, CSEL_POS_STARTX, CSEL_POS_STARTY,
		CSEL_POS_STARTX + CSEL_POS_STARTW, CSEL_POS_STARTY + CSEL_POS_STARTH);
	m_BtnStart.SetUp(CSEL_IMG_START, false, rcBtn);

	// 언어계열 7넘
	//	인문대
	SetRect(&rcBtn, CSEL_POS_IDCARDX1, CSEL_POS_IDCARDY1,
		CSEL_POS_IDCARDX1 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY1 + CSEL_POS_IDCARDH);
	m_ImgID[0].SetUp(CSEL_IMG_IDIMG1, true, rcBtn);
	//	사회대
	SetRect(&rcBtn, CSEL_POS_IDCARDX2, CSEL_POS_IDCARDY2,
		CSEL_POS_IDCARDX2 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY2 + CSEL_POS_IDCARDH);
	m_ImgID[1].SetUp(CSEL_IMG_IDIMG2, true, rcBtn);
	//	경영대
	SetRect(&rcBtn, CSEL_POS_IDCARDX3, CSEL_POS_IDCARDY3,
		CSEL_POS_IDCARDX3 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY3 + CSEL_POS_IDCARDH);
	m_ImgID[2].SetUp(CSEL_IMG_IDIMG3, true, rcBtn);
	//	법대
	SetRect(&rcBtn, CSEL_POS_IDCARDX4, CSEL_POS_IDCARDY4,
		CSEL_POS_IDCARDX4 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY4 + CSEL_POS_IDCARDH);
	m_ImgID[3].SetUp(CSEL_IMG_IDIMG4, true, rcBtn);
	//	생활과학대
	SetRect(&rcBtn, CSEL_POS_IDCARDX5, CSEL_POS_IDCARDY5,
		CSEL_POS_IDCARDX5 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY5 + CSEL_POS_IDCARDH);
	m_ImgID[4].SetUp(CSEL_IMG_IDIMG5, true, rcBtn);
	//	사범대
	SetRect(&rcBtn, CSEL_POS_IDCARDX6, CSEL_POS_IDCARDY6,
		CSEL_POS_IDCARDX6 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY6 + CSEL_POS_IDCARDH);
	m_ImgID[5].SetUp(CSEL_IMG_IDIMG6, true, rcBtn);
	//	자유전공
	SetRect(&rcBtn, CSEL_POS_IDCARDX7, CSEL_POS_IDCARDY7,
		CSEL_POS_IDCARDX7 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY7 + CSEL_POS_IDCARDH);
	m_ImgID[6].SetUp(CSEL_IMG_IDIMG7, true, rcBtn);

	// 수리계열 7넘
	//	공대
	SetRect(&rcBtn, CSEL_POS_IDCARDX8, CSEL_POS_IDCARDY8,
		CSEL_POS_IDCARDX8 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY8 + CSEL_POS_IDCARDH);
	m_ImgID[7].SetUp(CSEL_IMG_IDIMG8, true, rcBtn);
	//	자연대
	SetRect(&rcBtn, CSEL_POS_IDCARDX9, CSEL_POS_IDCARDY9,
		CSEL_POS_IDCARDX9 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY9 + CSEL_POS_IDCARDH);
	m_ImgID[8].SetUp(CSEL_IMG_IDIMG9, true, rcBtn);
	//	의대
	SetRect(&rcBtn, CSEL_POS_IDCARDX10, CSEL_POS_IDCARDY10,
		CSEL_POS_IDCARDX10 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY10 + CSEL_POS_IDCARDH);
	m_ImgID[9].SetUp(CSEL_IMG_IDIMG10, true, rcBtn);
	//	수의대
	SetRect(&rcBtn, CSEL_POS_IDCARDX11, CSEL_POS_IDCARDY11,
		CSEL_POS_IDCARDX11 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY11 + CSEL_POS_IDCARDH);
	m_ImgID[10].SetUp(CSEL_IMG_IDIMG11, true, rcBtn);
	//	약대
	SetRect(&rcBtn, CSEL_POS_IDCARDX12, CSEL_POS_IDCARDY12,
		CSEL_POS_IDCARDX12 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY12 + CSEL_POS_IDCARDH);
	m_ImgID[11].SetUp(CSEL_IMG_IDIMG12, true, rcBtn);
	//	간호대
	SetRect(&rcBtn, CSEL_POS_IDCARDX13, CSEL_POS_IDCARDY13,
		CSEL_POS_IDCARDX13 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY13 + CSEL_POS_IDCARDH);
	m_ImgID[12].SetUp(CSEL_IMG_IDIMG13, true, rcBtn);
	//	농대
	SetRect(&rcBtn, CSEL_POS_IDCARDX14, CSEL_POS_IDCARDY14,
		CSEL_POS_IDCARDX14 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY14 + CSEL_POS_IDCARDH);
	m_ImgID[13].SetUp(CSEL_IMG_IDIMG14, true, rcBtn);

	// 예술계열 2넘
	//	음대
	SetRect(&rcBtn, CSEL_POS_IDCARDX15, CSEL_POS_IDCARDY15,
		CSEL_POS_IDCARDX15 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY15 + CSEL_POS_IDCARDH);
	m_ImgID[14].SetUp(CSEL_IMG_IDIMG15, true, rcBtn);
	//	미대
	SetRect(&rcBtn, CSEL_POS_IDCARDX16, CSEL_POS_IDCARDY16,
		CSEL_POS_IDCARDX16 + CSEL_POS_IDCARDW, CSEL_POS_IDCARDY16 + CSEL_POS_IDCARDH);
	m_ImgID[15].SetUp(CSEL_IMG_IDIMG16, true, rcBtn);

	return true;
}

void gGameCore::OnLButtonDown_CharSel()
{
	gMouse			*mouse	= gMouse::GetIF();
	gCharManager	*cm		= gCharManager::GetIF();

	int		i;

	for(i = 0; i < CHARNUM; i++)
	{
		if(m_ImgID[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			//Btn 상태가 Click 이면 누가 고른거로 처리
			if(m_ImgID[i].m_eBtnMode == EBM_CLICK)
				return;

			if(m_nPlayer >= MAXPLAYER)
				return;

			gPlayerManager::GetIF()->m_player[m_nPlayer].SetUp(&cm->m_Chars[i]);
			m_ImgID[i].m_eBtnMode = EBM_CLICK;
			m_nSelected[i] = m_nPlayer;
			m_nPlayer++;
			SetPlayerIndex(m_nPlayer);

			return;
		}
	}
	if(m_BtnStart.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		if(m_nPlayer >= MAXPLAYER)
			m_gMode = EGM_GAME;
	}
}

void gGameCore::OnMouseMove_CharSel()
{
	gMouse	*mouse = gMouse::GetIF();

	int		i;
	
	for(i = 0; i < CHARNUM; i++)
	{
		if(m_ImgID[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			m_nSel = i;
			if(m_ImgID[i].m_eBtnMode == EBM_CLICK) continue; // 선택된 캐릭터
			m_ImgID[i].m_eBtnMode = EBM_HOVER;
			
		}
		else
		{
			if(m_ImgID[i].m_eBtnMode == EBM_CLICK) continue; // 선택된 캐릭터
			m_ImgID[i].m_eBtnMode = EBM_NONE;
		}
	}
	if(m_BtnStart.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		m_BtnStart.m_eBtnMode = EBM_HOVER;
	else
		m_BtnStart.m_eBtnMode = EBM_NONE;

}

void gGameCore::SetPlayerIndex(int np)
{
	int		i;

	for(i = np; i < MAXPLAYER; i++)
	{
		if(gPlayerManager::GetIF()->m_player[i].m_nNP == -1)
			m_nPlayer++;
		else
			break;
	}
}

void gGameCore::Release()
{
	int		i;

	m_ImgSelBack.Release();
	m_ImgWho.Release();
	m_ImgOutline.Release();
	m_BtnStart.Release();

	for(i = 0; i < CHARNUM; i++)
		m_ImgID[i].Release();
}