#include "TopUI.h"
#include "Util.h"
#include "MainWin.h"
#include "PlayerContainer.h"
#include "RoomCore.h"
#include "Server.h"
#include "Chat.h"
#include "PlaySoundCore.h"

#define TOP_FILE_BACK			".\\Data\\Interface\\top_back.img"
#define TOP_POS_BACK_X			0
#define TOP_POS_BACK_Y			0
#define TOP_POS_BACK_W			640
#define TOP_POS_BACK_H			60

#define TOP_BTN_BACK_FILE		".\\Data\\Interface\\top_btn_back.img"
#define TOP_BTN_SIZEW			30
#define TOP_BTN_SIZEH			30
#define TOP_BTN_POS_X			595
#define TOP_BTN_POS_Y			20
#define TOP_BTN_TERM_X			40

#define TOP_BTN_OPTION_FILE		".\\Data\\Interface\\top_btn_option.img"

#define OPTION_BACK				".\\Data\\Interface\\option.img"
#define OPTION_SIZE_W			242
#define OPTION_SIZE_H			301
#define OPTION_POS_X			(WNDSIZEW - OPTION_SIZE_W) / 2
#define OPTION_POS_Y			(WNDSIZEH - OPTION_SIZE_H) / 2

#define OPTION_BTN_OK_FILE		".\\Data\\Interface\\option_ok.img"
#define OPTION_BTN_CANCEL_FILE	".\\Data\\Interface\\option_cancel.img"
#define OPTION_BTN_OK_SIZEW		80
#define OPTION_BTN_OK_SIZEH		30
#define OPTION_BTN_OK_POSX		(OPTION_POS_X + 30)
#define OPTION_BTN_OK_POSY		(OPTION_POS_Y + 250)
#define OPTION_BTN_CANCEL_POSX	(OPTION_POS_X + OPTION_SIZE_W - OPTION_BTN_OK_SIZEW - 30)
#define OPTION_BTN_CANCEL_POSY	OPTION_BTN_OK_POSY

#define OPTION_BAR_FILE			".\\Data\\Interface\\option_bar.img"
#define OPTION_BAR_SIZEW		12
#define OPTION_BAR_SIZEH		26
#define OPTION_GAUGE_W			165
#define OPTION_GAUGE_H			9
#define OPTION_BGM_POS_X		(OPTION_POS_X + 39)
#define OPTION_BGM_POS_Y		(OPTION_POS_Y + 104)
#define OPTION_EFFECT_POS_X		OPTION_BGM_POS_X
#define OPTION_EFFECT_POS_Y		(OPTION_POS_Y + 164)

static gTopUI s_TopUI;

gTopUI *gTopUI::GetIF()
{
	return &s_TopUI;
}

gTopUI::gTopUI(void)
{
}

gTopUI::~gTopUI(void)
{
}


bool gTopUI::SetUp()
{
	if(!m_ImgBack.Load(TOP_FILE_BACK))
		return false;

	SetRect(&m_rcPos,
			TOP_POS_BACK_X,
			TOP_POS_BACK_Y,
			TOP_POS_BACK_X + TOP_POS_BACK_W,
			TOP_POS_BACK_Y + TOP_POS_BACK_H);

	RECT	rcDest, rcSour, rcTemp;
	SetRect(&rcSour, 0, 0, TOP_BTN_SIZEW, TOP_BTN_SIZEH);
	SetRect(&rcDest,
		TOP_BTN_POS_X,
		TOP_BTN_POS_Y,
		TOP_BTN_POS_X + TOP_BTN_SIZEW,
		TOP_BTN_POS_Y + TOP_BTN_SIZEH );

	rcTemp = rcDest;
	OffsetRect(&rcTemp, - ((TOP_END - 1) * TOP_BTN_TERM_X), 0);
	if(!m_Btn[TOP_OPTION].SetUp(TOP_BTN_OPTION_FILE, false, rcTemp))
		return false;
	OffsetRect(&rcTemp, TOP_BTN_TERM_X, 0);
	if(!m_Btn[TOP_BACK].SetUp(TOP_BTN_BACK_FILE, false, rcTemp))
		return false;

	m_uimode = RC_END;

	if(!m_Img[IMG_OPTION].Load(OPTION_BACK))
		return false;
	SetRect(&m_rc[RC_OPTION], OPTION_POS_X, OPTION_POS_Y,
		OPTION_POS_X + OPTION_SIZE_W, OPTION_POS_Y + OPTION_SIZE_H);

	if(!m_Img[IMG_BAR].Load(OPTION_BAR_FILE))
		return false;

	// option btn
	SetRect(&rcTemp,
		OPTION_BTN_OK_POSX, OPTION_BTN_OK_POSY,
		OPTION_BTN_OK_POSX + OPTION_BTN_OK_SIZEW,
		OPTION_BTN_OK_POSY + OPTION_BTN_OK_SIZEH );
	if(!m_OptBtn[OPT_OK].SetUp(OPTION_BTN_OK_FILE, false, rcTemp))
		return false;

	SetRect(&rcTemp,
		OPTION_BTN_CANCEL_POSX, OPTION_BTN_CANCEL_POSY,
		OPTION_BTN_CANCEL_POSX + OPTION_BTN_OK_SIZEW,
		OPTION_BTN_CANCEL_POSY + OPTION_BTN_OK_SIZEH );
	if(!m_OptBtn[OPT_CANCEL].SetUp(OPTION_BTN_CANCEL_FILE, false, rcTemp))
		return false;
	
	return true;
}

void gTopUI::Draw()
{
	Draw_Back();

	Draw_Option();
}

void gTopUI::Draw_Back()
{
	m_ImgBack.Draw(m_rcPos.left, m_rcPos.top);


	int		i;

	for(i = 0; i < TOP_END; i++)
		m_Btn[i].Draw();
}

void gTopUI::Draw_Option()
{
	if(m_uimode == RC_OPTION)
	{
		m_Img[IMG_OPTION].Draw(m_rc[RC_OPTION].left, m_rc[RC_OPTION].top);

		int		i;
		for(i = 0; i < OPT_END; i++)
			m_OptBtn[i].Draw();

		float	fRateX;
		int		nX, nY;
		// bgm
		fRateX = (float)gPlaySoundCore::GetIF()->m_nBGM / VOLUME_MAX;
		nX = int(OPTION_BGM_POS_X + (OPTION_GAUGE_W * fRateX) - (OPTION_BAR_SIZEW/2));
		nY = OPTION_BGM_POS_Y - 7;
		m_Img[IMG_BAR].Draw(nX, nY);

		// effect
		fRateX = (float)gPlaySoundCore::GetIF()->m_nEffect / VOLUME_MAX;
		nX = int(OPTION_EFFECT_POS_X + (OPTION_GAUGE_W * fRateX) - (OPTION_BAR_SIZEW/2));
		nY = OPTION_EFFECT_POS_Y - 7;
		m_Img[IMG_BAR].Draw(nX, nY);
	}
}


void gTopUI::Release()
{
	m_ImgBack.Release();

	int		i;
	
	for(i = 0; i < TOP_END; i++)
		m_Btn[i].Release();

	for(i = 0; i < IMG_END; i++)
		m_Img[i].Release();

	for(i = 0; i < OPT_END; i++)
		m_OptBtn[i].Release();
}

bool gTopUI::Restore()
{
	if(!m_ImgBack.Restore())
		return false;

	int		i;

	for(i = 0; i < TOP_END; i++)
		if(!m_Btn[i].Restore())
			return false;

	for(i = 0; i < IMG_END; i++)
		if(!m_Img[i].Restore())
			return false;

	for(i = 0; i < OPT_END; i++)
		if(!m_OptBtn[i].Restore())
			return false;

	return true;
}

void gTopUI::OnLButtonDown(int x, int y)
{
	gPlaySoundCore	*sound = gPlaySoundCore::GetIF();
	int		i;

	if(m_Btn[TOP_BACK].PointInButton(x, y))
	{
		OnLButtonDown_Back();
		return;
	}
	else if(m_Btn[TOP_OPTION].PointInButton(x, y))
	{
		m_uimode = RC_OPTION;
		sound->m_nTempBGM		= sound->m_nBGM;
		sound->m_nTempEffect	= sound->m_nEffect;
		sound->m_bTempFull		= sound->m_bFull;
	}

	if(m_uimode == RC_OPTION)
	{
		// volume control
		RECT	rcBGM = {OPTION_BGM_POS_X, OPTION_BGM_POS_Y,
			OPTION_BGM_POS_X + OPTION_GAUGE_W,
			OPTION_BGM_POS_Y + OPTION_GAUGE_H };
		RECT	rcEffect = {OPTION_EFFECT_POS_X, OPTION_EFFECT_POS_Y,
			OPTION_EFFECT_POS_X + OPTION_GAUGE_W,
			OPTION_EFFECT_POS_Y + OPTION_GAUGE_H };

		if(gUtil::PointInRect(x, y, rcBGM))
		{
			float	fRateX;
			int		nX, newVol;
			nX = x - OPTION_BGM_POS_X;
			fRateX = (float)nX / OPTION_GAUGE_W;
			newVol = int(VOLUME_MAX * fRateX);
			if(newVol < 0)
				newVol = 0;
			if(newVol > VOLUME_MAX)
				newVol = VOLUME_MAX;
			sound->m_nBGM = newVol;
			sound->setBGMVolume(sound->m_nBGM);
			return;
		}
		if(gUtil::PointInRect(x, y, rcEffect))
		{
			float	fRateX;
			int		nX, newVol;
			nX = x - OPTION_EFFECT_POS_X;
			fRateX = (float)nX / OPTION_GAUGE_W;
			newVol = int(VOLUME_MAX * fRateX);
			if(newVol < 0)
				newVol = 0;
			if(newVol > VOLUME_MAX)
				newVol = VOLUME_MAX;
			sound->m_nEffect = newVol;
			sound->setEffectSoundVolume(sound->m_nEffect);
			return;
		}
		// end volume
		if(m_OptBtn[OPT_OK].PointInButton(x, y))
		{
			m_uimode = RC_END;
			for(i = 0; i < OPT_END; i++)
				m_OptBtn[i].m_eBtnMode = EBM_NONE;
			return;
		}
		if(m_OptBtn[OPT_CANCEL].PointInButton(x, y))
		{
			sound->m_nBGM		= sound->m_nTempBGM;
			sound->m_nEffect	= sound->m_nTempEffect;
			sound->m_bFull		= sound->m_bTempFull;
			m_uimode = RC_END;
			for(i = 0; i < OPT_END; i++)
				m_OptBtn[i].m_eBtnMode = EBM_NONE;
			sound->setBGMVolume(sound->m_nBGM);
			sound->setEffectSoundVolume(sound->m_nEffect);
			return;
		}
	}
}

void gTopUI::OnLButtonDown_Back()
{
	gPlayerContainer	*pc = gPlayerContainer::GetIF();
	gChat				*chat = gChat::GetIF();

	switch(gMainWin::GetIF()->m_eCoreMode)
	{
	case ECM_BATTLENET:
		{
			PK_GOLOGIN_ASK		ask;

			strcpy(ask.szID, pc->m_MyPlayer.szID);
			gServer::GetIF()->Send(PL_GOLOGIN_ASK, sizeof(ask), &ask);

			chat->MsgStackClear();
			gMainWin::GetIF()->m_eCoreMode = ECM_LOGIN;
		}
		break;
	case ECM_ROOMMAKE:
		{
			gRoomCore::GetIF()->Cancel_Make();
		}
		break;
	case ECM_ROOMJOIN:
		{
			gRoomCore::GetIF()->m_bEnteringPass = false;
			gRoomCore::GetIF()->m_nSelected = -1;
			gRoomCore::GetIF()->m_EditPassEnter.Clear();
			SetFocus(gMainWin::GetIF()->m_hWnd);
		}
	case ECM_ROOM:
		{
			PK_CHANNELCHANGE_ASK	ask;

			ask.nChannel = pc->m_MyChannel.nChannelNum;
			strcpy(ask.szID, pc->m_MyPlayer.szID);

			gServer::GetIF()->Send(PL_CHANNELCHANGE_ASK, sizeof(ask), &ask);
			chat->MsgStackClear();
			gMainWin::GetIF()->m_eCoreMode = ECM_BATTLENET;
		}
		break;
	}
	return;
}

void gTopUI::OnMouseMove(int x, int y)
{
	int		i;

	for(i = 0; i < TOP_END; i++)
	{
		if(m_Btn[i].PointInButton(x, y))
			m_Btn[i].m_eBtnMode = EBM_HOVER;
		else
			m_Btn[i].m_eBtnMode = EBM_NONE;
	}

	if(m_uimode == RC_OPTION)
	{
		gPlaySoundCore	*sound = gPlaySoundCore::GetIF();

		for(i = 0; i < OPT_END; i++)
		{
			if(m_OptBtn[i].PointInButton(x, y))
				m_OptBtn[i].m_eBtnMode = EBM_HOVER;
			else
				m_OptBtn[i].m_eBtnMode = EBM_NONE;
		}
		if(GetKeyState(VK_LBUTTON) < 0)
		{
			RECT	rcBGM = {OPTION_BGM_POS_X, OPTION_BGM_POS_Y,
				OPTION_BGM_POS_X + OPTION_GAUGE_W,
				OPTION_BGM_POS_Y + OPTION_GAUGE_H };
			RECT	rcEffect = {OPTION_EFFECT_POS_X, OPTION_EFFECT_POS_Y,
				OPTION_EFFECT_POS_X + OPTION_GAUGE_W,
				OPTION_EFFECT_POS_Y + OPTION_GAUGE_H };
		
			if(gUtil::PointInRect(x, y, rcBGM))
			{
				float	fRateX;
				int		nX, newVol;
				nX = x - OPTION_BGM_POS_X;
				fRateX = (float)nX / OPTION_GAUGE_W;
				newVol = int(VOLUME_MAX * fRateX);
				if(newVol < 0)
					newVol = 0;
				if(newVol > VOLUME_MAX)
					newVol = VOLUME_MAX;
				sound->m_nBGM = newVol;
				sound->setBGMVolume(sound->m_nBGM);
				return;
			}
			if(gUtil::PointInRect(x, y, rcEffect))
			{
				float	fRateX;
				int		nX, newVol;
				nX = x - OPTION_EFFECT_POS_X;
				fRateX = (float)nX / OPTION_GAUGE_W;
				newVol = int(VOLUME_MAX * fRateX);
				if(newVol < 0)
					newVol = 0;
				if(newVol > VOLUME_MAX)
					newVol = VOLUME_MAX;
				sound->m_nEffect = newVol;
				sound->setEffectSoundVolume(sound->m_nEffect);
				return;
			}
		}
	}
}

void gTopUI::OnRButtonDown(int x, int y)
{
	if(m_uimode == RC_OPTION)
		m_uimode = RC_END;
}

bool gTopUI::PointInUI(int x, int y)
{
	if(gUtil::PointInRect(x, y, m_rcPos))
		return true;

	if(m_uimode == RC_OPTION)
	{
		if(gUtil::PointInRect(x, y, m_rc[RC_OPTION]))
			return true;
	}

	return false;
}