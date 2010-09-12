//------------------------------------------------------------------------------------
//	gChannelUI Class
//
//	2010. 08. 22	CoderK
//
//	배틀넷 화면에서 보이는 채널, 클랜, 친구관련 
//------------------------------------------------------------------------------------
#pragma once
#include "MainWin.h"
#include <windows.h>
#include "Image.h"
#include "ImgButton.h"
#include "networkconst.h"

#define CH_FILE_BACK			".\\Data\\Interface\\channel_back.img"
#define CH_SIZE_W				160
#define CH_SIZE_H				420
#define CH_POS_X				480
#define CH_POS_Y				60

#define CH_SIZE_MODEBTNW		50
#define CH_SIZE_MODEBTNH		20
#define CH_BTN_FILE_CHANNEL		".\\Data\\Interface\\channel_btn_ch.img"
#define CH_BTN_CHANNEL_POS_X	10		// 채널 UI 내에서의 위치
#define CH_BTN_CHANNEL_POS_Y	10
#define CH_BTN_FILE_FRIEND		".\\Data\\Interface\\channel_btn_friend.img"
#define CH_BTN_FRIEND_POS_X		10		// 채널 UI 내에서의 위치
#define CH_BTN_FRIEND_POS_Y		40
#define CH_BTN_FILE_CLAN		".\\Data\\Interface\\channel_btn_clan.img"
#define CH_BTN_CLAN_POS_X		10		// 채널 UI 내에서의 위치
#define CH_BTN_CLAN_POS_Y		70

// channel mode
#define CH_FILE_CHNAME			".\\Data\\Interface\\channel_name.img"
#define CH_SIZE_CHNAMEW			50
#define CH_SIZE_CHNAMEH			17
#define CH_POS_CHNAMEX			47
#define CH_POS_CHNAMEY			12

#define CH_POS_PLAYERNAMEX		20
#define CH_POS_PLAYERNAMEY		60
#define CH_POS_PLAYERNAMETERM	20

#define CH_FILE_CHCHANGE		".\\Data\\Interface\\channel_btn_chchange.img"
//#define CH_FILE_CHCHANGECANCEL	".\\Data\\Interface\\channel_btn_chcancel.img"
#define CH_BTN_SIZE_CHCHANGEW	50
#define CH_BTN_SIZE_CHCHANGEH	20
#define CH_BTN_POS_CHCHANGEX	105
#define CH_BTN_POS_CHCHANGEY	12

#define CH_BTN_FILE_CH1			".\\Data\\Interface\\channel_btn_ch1.img"
#define CH_BTN_FILE_CH2			".\\Data\\Interface\\channel_btn_ch2.img"
#define CH_BTN_FILE_CH3			".\\Data\\Interface\\channel_btn_ch3.img"
#define CH_BTN_FILE_CH4			".\\Data\\Interface\\channel_btn_ch4.img"
#define CH_BTN_FILE_CH5			".\\Data\\Interface\\channel_btn_ch5.img"
#define CH_BTN_FILE_CH6			".\\Data\\Interface\\channel_btn_ch6.img"

#define CH_BTN_SIZE_CHNAMEW		125
#define CH_BTN_SIZE_CHNAMEH		30
#define CH_BTN_POS_CHNAMEX		10
#define CH_BTN_POS_CHNAMEY		50
//#define CH_BTN_CHNAME_XTERM		10
#define CH_BTN_CHNAME_YTERM		30

enum CHANNELMODE
{
	CM_CHANNEL,
	CM_FRIEND,
	CM_CLAN,
	CM_END,

	CM_CHANNELCHANGE,
};

enum CH_CHANGE_BTN
{
	CCB_CHANGE,
	CCB_CANCEL,
	CCB_CH1,
	CCB_CH2,
	CCB_CH3,
	CCB_CH4,
	CCB_CH5,
	CCB_CH6,
	CCB_END,
};

class gChannelUI
{
public:
	gChannelUI(void);
	~gChannelUI(void);

public:
	gImage			m_ImgBack;	// 채널 UI 이미지
	RECT			m_rcPos;

	CHANNELMODE		m_eChannel;
	gImgButton		m_BtnMode[CM_END];

	gImage			m_ImgChName;
	gImgButton		m_BtnChChange[CCB_END];

public:
	bool			SetUp();
	void			Draw();
	void			Release();

	bool			isPointInUI(int x, int y);

	void			OnLButtonDown(int x, int y);
	void			OnLButtonUp(int x, int y);
	void			OnMouseMove(int x, int y);
	void			OnRButtonDown(int x, int y);

	void			DrawChannel();
	void			DrawChannelChange();
};
