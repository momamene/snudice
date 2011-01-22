#include <stdio.h>
#include "UIGame.h"
#include "Util.h"
#include "PlayerContainer.h"
#include "GameCore.h"
#include "Mouse.h"
#include "MainWin.h"
#include "SubjectContainer.h"
#include "Chat.h"
#include "ItemContainer.h"
#include "Server.h"
#include "PopUp.h"
#include "stringconst.h"
#include "Map.h"
#include "Mouse.h"
#include "PlaySoundCore.h"
#include "SubmitCore.h"
#include "RoomCore.h"

#define	UI_FILE_MAININFO					".\\Data\\Interface\\game_maininfo.img"
#define UI_SIZE_MAININFO_W					220
#define UI_SIZE_MAININFO_H					110
#define UI_POS_MAININFO_X					0
#define UI_POS_MAININFO_Y					0

#define MAININFO_ID_POS_X					102
#define MAININFO_ID_POS_Y					16
#define MAININFO_LANG_POS_X					102
#define MAININFO_LANG_POS_Y					32
#define MAININFO_MATH_POS_X					102
#define MAININFO_MATH_POS_Y					47
#define MAININFO_ART_POS_X					102
#define MAININFO_ART_POS_Y					62
#define MAININFO_DICE6_POS_X				180
#define MAININFO_DICE6_POS_Y				33
#define MAININFO_DICE4_POS_X				180
#define MAININFO_DICE4_POS_Y				53
#define MAININFO_NAME_POS_X					15
#define MAININFO_NAME_POS_Y					74
#define MAININFO_PIC_POS_X					15
#define MAININFO_PIC_POS_Y					10

#define MAININFO_FILE_BARLINE				".\\Data\\Interface\\game_bar_outline.img"
#define MAININFO_BARLINE_SIZE_W				150
#define MAININFO_BARLINE_SIZE_H				10
#define MAININFO_BARLINE_POS_X				13
#define MAININFO_BARLINE_POS_Y				91
#define MAININFO_FILE_BARGUAGE				".\\Data\\Interface\\game_bar_guage.img"
#define MAININFO_BARGUAGE_SIZE_W			148
#define MAININFO_BARGUAGE_SIZE_H			8
#define MAININFO_BARGUAGE_POS_X				14
#define MAININFO_BARGUAGE_POS_Y				92

#define SUBINFO_FILE_BACK					".\\Data\\Interface\\game_subinfo.img"
#define SUBINFO_SIZE_W						120
#define SUBINFO_SIZE_H						40
#define SUBINFO_POS_X						220
#define SUBINFO_POS_Y						0
#define SUBINFO_ITEM_FILE					".\\Data\\Interface\\game_sub_item.img"
#define SUBINFO_ITEM_SIZE_W					50
#define SUBINFO_ITEM_SIZE_H					30
#define SUBINFO_ITEM_POS_X					227
#define SUBINFO_ITEM_POS_Y					5
#define SUBINFO_SUBJECT_FILE				".\\Data\\Interface\\game_sub_subject.img"
#define SUBINFO_SUBJECT_SIZE_W				50
#define SUBINFO_SUBJECT_SIZE_H				30
#define SUBINFO_SUBJECT_POS_X				283
#define SUBINFO_SUBJECT_POS_Y				5

#define SUBINFO_SUBWND_FILE					".\\Data\\Interface\\game_sub_subwnd.img"
#define SUBINFO_SUBWND_SIZE_W				270
#define SUBINFO_SUBWND_SIZE_H				230
#define SUBINFO_SUBWND_POS_X				((WNDSIZEW - SUBINFO_SUBWND_SIZE_W) / 2)
#define SUBINFO_SUBWND_POS_Y				((WNDSIZEH - SUBINFO_SUBWND_SIZE_H) / 2)
#define SUBINFO_ID_POS_X					212
#define SUBINFO_ID_POS_Y					155
#define SUBINFO_BUILDING_POS_X				215
#define SUBINFO_SUBNAME_POS_X				270
#define SUBINFO_GRADE_POS_X					400
#define SUBINFO_SUBNAME_POS_Y				181
#define SUBINFO_SUBNAME_TERM_Y				18
#define SUBINFO_AVGRADE_FONTSIZE			22
#define SUBINFO_AVGRADE_POS_X				355
#define SUBINFO_AVGRADE_POS_Y				305
#define SUBINFO_BTN_FILE_PREV				".\\Data\\Interface\\game_btn_prev.img"
#define SUBINFO_BTN_FILE_NEXT				".\\Data\\Interface\\game_btn_next.img"
#define SUBINFO_BTN_PREV_SIZE_W				12
#define SUBINFO_BTN_PREV_SIZE_H				21
#define SUBINFO_BTN_PREV_POS_X				190
#define SUBINFO_BTN_PREV_POS_Y				220
#define SUBINFO_BTN_NEXT_POS_X				438
#define SUBINFO_BTN_NEXT_POS_Y				220

#define DICEBTN_FILE						".\\Data\\Interface\\game_btn_dice.img"
#define DICEBTN_SIZE_W						100
#define DICEBTN_SIZE_H						101
#define DICEBTN_POS_X						515
#define DICEBTN_POS_Y						247

#define MENUBTN_FILE						".\\Data\\Interface\\game_btn_menu.img"
#define MENUBTN_SIZE_W						80
#define MENUBTN_SIZE_H						30
#define MENUBTN_POS_X						(WNDSIZEW - MENUBTN_SIZE_W)
#define MENUBTN_POS_Y						0

#define MINIMAP_BACK_FILE					".\\Data\\Interface\\game_minimap.img"
#define MINIMAP_BACK_POS_X					480
#define MINIMAP_BACK_POS_Y					360
#define MINIMAP_BACK_SIZE_W					200
#define MINIMAP_BACK_SIZE_H					120
#define MINIMAP_START_X						(MINIMAP_BACK_POS_X + 10)
#define MINIMAP_START_Y						(MINIMAP_BACK_POS_Y + 10)
#define MINIMAP_SOLUTION					16
#define MINIMAP_CURSOR_FILE					".\\Data\\Interface\\game_minimapcursor.img"
#define MINIMAP_CURSOR_SIZE_W				41
#define MINIMAP_CURSOR_SIZE_H				31
#define MINIMAP_SIZE_W						144
#define MINIMAP_SIZE_H						107

#define UI_NUMBER_FILE						".\\Data\\Interface\\game_number.img"
#define UI_NUMBER_SIZE_W					16
#define UI_NUMBER_SIZE_H					16
#define UI_NUMBER_TERM_X					0
#define UI_NUMBER_TERM_Y					0

#define ITEMCARD_POS_X						22
#define ITEMCARD_POS_Y						120
#define ITEMCARD_SIZE_W						140
#define ITEMCARD_SIZE_H						196
#define ITEMCARD_TERM_X						10

#define TARGET_OUTLINE_FILE					".\\Data\\Interface\\game_face_outline.img"
#define TARGET_OUTLINE_SIZE_W				52
#define TARGET_OUTLINE_SIZE_H				62
#define TARGET_TERM_X						10
#define TARGET_TERM_Y						10
#define TARGET_POS_CENTER_X					320
#define TARGET_POS_CENTER_Y					200

#define USEINFO_CARD_POS_X					320
#define USEINFO_CARD_POS_Y					ITEMCARD_POS_Y
#define USEINFO_USER_POS_X					USEINFO_CARD_POS_X - 200													// 중점
#define USEINFO_USER_POS_Y					(ITEMCARD_POS_Y + (ITEMCARD_SIZE_H - TARGET_OUTLINE_SIZE_H) / 2)			// 중점
#define USEINFO_TARGET_POS_X				USEINFO_CARD_POS_X + 200													// 중점
#define USEINFO_TARGET_POS_Y				(USEINFO_USER_POS_Y + TARGET_OUTLINE_SIZE_H / 2)							// 중점
#define USEINFO_TARGET_TERM_X				10
#define USEINFO_TARGET_TERM_Y				10

#define USEINFO_TICK						2000	// 3초 보여줌
#define INFOCHANGE_TICK						2000

#define INFOCHANGE_POS_X					320
#define	INFOCHANGE_POS_Y					150
#define INFOCHANGE_TERM_X					10		
#define INFOCHANGE_TERM_Y					10
#define INFOCHANGE_INFOSIZE_W				50
#define INFOCHANGE_INFOSIZE_H				12		// info 하나당 높이
#define INFOCHANGE_INFOTERM_Y				10		// info끼리 텀

// turn, rank 같이 표시
#define TURN_START_X						530
#define TURN_START_Y						80
#define TURN_TERM_Y							20

#define TURN_CROWN_FILE						".\\Data\\Interface\\game_crown.img"
#define TURN_CROWN_SIZE_W					14
#define TURN_CROWN_SIZE_H					12
#define TURN_CROWN_TERM_X					-22
#define TURN_CROWN_TERM_Y					-1
#define TURN_OUTLINE_FILE					".\\Data\\Interface\\game_turn.img"
#define TURN_OUTLINE_TERM_X					-25
#define TURN_OUTLINE_TERM_Y					-5


#define MAPTOOLTIP_FILE						".\\Data\\Interface\\game_maptooltip.img"
#define MAPTOOLTIP_SIZE_W					120
#define MAPTOOLTIP_SIZE_H					80
#define MAPTOOLTIP_TERM_MOUSE				15			// 마우스좌표에 더해지는 좌표. 부터출력
#define MAPTOOLTIP_TEXT_X					7
#define MAPTOOLTIP_TEXT_Y					7
#define MAPTOOLTIP_TEXT_TERM_Y				20
#define MAPTOOLTIP_TEXT_TERM_X				75
#define MAPTOOLTIP_IMG_SIZE_W				30
#define MAPTOOLTIP_IMG_SIZE_H				35
#define MAPTOOLTIP_IMG_POS_X				10
#define MAPTOOLTIP_IMG_POS_Y				42
#define MAPTOOLTIP_IMG_TERM_X				7

#define COUPLE_OUTLINE_FILE					".\\Data\\Interface\\game_coupleoutline.img"
#define COUPLE_OUTLINE_POS_X				12
#define COUPLE_OUTLINE_POS_Y				117
#define COUPLE_FACE_SIZE_W					35
#define COUPLE_FACE_SIZE_H					42
#define COUPLE_FACE_POS_X					(COUPLE_OUTLINE_POS_X + 2)			
#define COUPLE_FACE_POS_Y					(COUPLE_OUTLINE_POS_Y + 13)
#define COUPLE_LOVE_FILE					".\\Data\\Interface\\game_love.img"
#define COUPLE_LOVE_SIZE_W					24
#define COUPLE_LOVE_SIZE_H					20
#define COUPLE_LOVE_POS_X					(COUPLE_FACE_POS_X + 45)
#define COUPLE_LOVE_POS_Y					(COUPLE_FACE_POS_Y + 13)
#define COUPLE_LOVE_TERM_X					3

#define BECOUPLE_MALE_X						(320 - TARGET_OUTLINE_SIZE_W - 30)
#define BECOUPLE_MALE_Y						(220 - TARGET_OUTLINE_SIZE_H/2)
#define BECOUPLE_FEMALE_X					(320 + 30)
#define BECOUPLE_FEMALE_Y					BECOUPLE_MALE_Y
#define BECOUPLE_HEART_X					(320 - COUPLE_LOVE_SIZE_W/2)
#define BECOUPLE_HEART_Y					(220 - COUPLE_LOVE_SIZE_H/2)
#define BECOUPLE_TICK						2000

#define TEXT_NUM_FILE						".\\Data\\Interface\\number.img"
#define TEXT_ICON_FILE						".\\Data\\Interface\\icon.img"
#define ITEM_USER_BOX_FILE					".\\Data\\Interface\\game_carduse.img"

#define TIMER_SHOWTIME						1500
#define	TIMER_YOURTURN_FILE					".\\Data\\Interface\\yourturn.img"
#define TIMER_YOURTURN_SIZE_W				255
#define TIMER_YOURTURN_SIZE_H				36
#define TIMER_YOURTURN_POS_X				((WNDSIZEW - TIMER_YOURTURN_SIZE_W) / 2)
#define TIMER_YOURTURN_POS_Y				((WNDSIZEH - TIMER_YOURTURN_SIZE_H) / 2 - 30)
#define TIMER_NUMBER_FILE					".\\Data\\Interface\\timer.img"
#define TIMER_NUMBER_SIZE_W					50
#define	TIMER_NUMBER_SIZE_H					50
#define TIMER_NUMBER_POS_X					((WNDSIZEW - TIMER_NUMBER_SIZE_W) / 2)
#define TIMER_NUMBER_POS_Y					((WNDSIZEH - TIMER_NUMBER_SIZE_H) / 2 - 30)

#define RESULT_FILE							".\\Data\\Interface\\result.img"
#define RESULT_SIZE_W						250
#define RESULT_SIZE_H						200
#define RESULT_POS_X						((WNDSIZEW - RESULT_SIZE_W) / 2)
#define RESULT_POS_Y						((WNDSIZEH - RESULT_SIZE_H) / 2 - 30)
#define RESULT_POS_START_Y					(RESULT_POS_Y + 50)
#define RESULT_POS_START_X					(RESULT_POS_X + 30)
#define RESULT_TERM_X						70
#define RESULT_TERM_Y						22
#define RESULT_SHOWTIME						10000

#define MAP_BTN_MAP_FILE					".\\Data\\Interface\\game_btn_map.img"
#define MAP_BTN_MAP_SIZE_W					30
#define MAP_BTN_MAP_SIZE_H					30
#define MAP_BTN_MAP_POS_X					340
#define MAP_BTN_MAP_POS_Y					0

#define MAP_BACK_FILE						".\\Data\\Interface\\game_mapback.img"
#define MAP_BACK_SIZE_W						622
#define MAP_BACK_SIZE_H						360
#define MAP_BACK_POS_X						((WNDSIZEW - MAP_BACK_SIZE_W) / 2)
#define MAP_BACK_POS_Y						((WNDSIZEH - MAP_BACK_SIZE_H) / 2)

#define MAP_BG_FILE							".\\Data\\Interface\\game_mapbg.img"
#define MAP_BG_SIZE_W						375
#define MAP_BG_SIZE_H						272
#define MAP_BG_POS_X						235
#define MAP_BG_POS_Y						(MAP_BACK_POS_Y + (MAP_BACK_SIZE_H - MAP_BG_SIZE_H) / 2)

#define MAP_PLAYER_FILE						".\\Data\\Interface\\game_map_player.img"
#define MAP_PLAYER_SIZE_W					190
#define MAP_PLAYER_SIZE_H					45
#define MAP_PLAYER_POS_X					(MAP_BACK_POS_X + 20)
#define MAP_PLAYER_POS_Y					(MAP_BACK_POS_Y + 30)
#define MAP_PLAYER_TERM_Y					6

#define MAP_PLAYEROUT_FILE					".\\Data\\Interface\\game_map_playeroutline.img"
#define MAP_PLAYEROUT_SIZE_W				196
#define MAP_PLAYEROUT_SIZE_H				51

#define MAP_PLAYERBAR_FILE					".\\Data\\Interface\\game_map_playerbar.img"
#define MAP_PLAYERBAR_SIZE_W				94
#define MAP_PLAYERBAR_SIZE_H				2
#define MAP_PLAYERBAR_POS_X					40
#define MAP_PLAYERBAR_POS_Y					38

#define MAP_PLAYERLOVE_FILE					".\\Data\\Interface\\game_map_love.img"
#define MAP_PLAYERLOVE_SIZE_W				12
#define MAP_PLAYERLOVE_SIZE_H				10
#define MAP_PLAYERLOVE_POS_X				(MAP_PLAYER_POS_X + 176)
#define MAP_PLAYERLOVE_POS_Y				6
#define MAP_PLAYERLOVE_TERM_Y				3

// 전체맵 보기에서, 과목 점수(평점) 띄워줄 좌표.. 하드코딩 우왕 ㅋ
static POINT s_ptPosGrade[CLASSNUM] = 
{
	// 언어
	{ 331, 272	},		// 사회과학대학			16동	심리학개론
	{ 343, 248	},		// 법과대학				17동	법의학
	{ 370, 223	},		// 인문대학				1동		대학국어
	{ 409, 184	},		// 사범대학				11동	교육과정
	{ 383, 177	},		// 인문대학				7동		미학과 예술론
	{ 320, 231	},		// 생활과학대학			222동	생활과학의 이해
	{ 301, 268	},		// 경영대학				58동	국제경영
	// 수리
	{ 417, 247	},		// 자연과학대학			11동	미적분학
	{ 462, 262 	},		// 자연과학대학			500동	화학실험
	{ 487, 248	},		// 농업생명과학대학		200동	농업과환경
	{ 512, 218	},		// 공과대학				37동	건축이론
	{ 501, 171	},		// 공과대학				302동	논리설계실험
	{ 446, 192	},		// 약학대학				29동	약물치료학
	{ 294, 211	},		// 수의과대학			85동	수의외과학
	// 예술
	{ 345, 198	},		// 음악대학				54동	음악학개론
	{ 341, 221	},		// 미술대학				49동	색채학
	{ 273, 242	},		// 사범대학				71동	댄스스포츠
	{ 284, 289	},		// 미술대학				151동	미술관탐방
};

static gUIGame s_UIGame;

gUIGame *gUIGame::GetIF()
{
	return &s_UIGame;
}

gUIGame::gUIGame(void)
{
}

gUIGame::~gUIGame(void)
{
}

bool gUIGame::SetUp()
{
	RECT		rcDest;

	// Maininfo
	if(!m_ImgUI[UIIMG_MAININFO].Load(UI_FILE_MAININFO))
		return false;
	SetRect(&m_rcPos[UIT_MAININFO],
			UI_POS_MAININFO_X,
			UI_POS_MAININFO_Y,
			UI_POS_MAININFO_X + UI_SIZE_MAININFO_W,
			UI_POS_MAININFO_Y + UI_SIZE_MAININFO_H );

	if(!m_ImgUI[UIIMG_BAROUTLINE].Load(MAININFO_FILE_BARLINE))
		return false;
	if(!m_ImgUI[UIIMG_BARGUAGE].Load(MAININFO_FILE_BARGUAGE))
		return false;

	SetRect(&m_rcBarDest,
			MAININFO_BARGUAGE_POS_X,
			MAININFO_BARGUAGE_POS_Y,
			MAININFO_BARGUAGE_POS_X + MAININFO_BARGUAGE_SIZE_W,
			MAININFO_BARGUAGE_POS_Y + MAININFO_BARGUAGE_SIZE_H);
	SetRect(&m_rcBarSour,
			0, 0, MAININFO_BARGUAGE_SIZE_W, MAININFO_BARGUAGE_SIZE_H);

	// SubInfo
	if(!m_ImgUI[UIIMG_SUBINFO].Load(SUBINFO_FILE_BACK))
		return false;

	SetRect(&m_rcPos[UIT_SUBINFO],
			SUBINFO_POS_X,
			SUBINFO_POS_Y,
			SUBINFO_POS_X + SUBINFO_SIZE_W,
			SUBINFO_POS_Y + SUBINFO_SIZE_H);


	SetRect(&rcDest,
			SUBINFO_ITEM_POS_X,
			SUBINFO_ITEM_POS_Y,
			SUBINFO_ITEM_POS_X + SUBINFO_ITEM_SIZE_W,
			SUBINFO_ITEM_POS_Y + SUBINFO_ITEM_SIZE_H );
	if(!m_BtnUI[UIBTN_ITEMCARD].SetUp(SUBINFO_ITEM_FILE, false, rcDest))
		return false;
	SetRect(&rcDest,
		SUBINFO_SUBJECT_POS_X,
		SUBINFO_SUBJECT_POS_Y,
		SUBINFO_SUBJECT_POS_X + SUBINFO_SUBJECT_SIZE_W,
		SUBINFO_SUBJECT_POS_Y + SUBINFO_SUBJECT_SIZE_H );
	if(!m_BtnUI[UIBTN_SUBJECT].SetUp(SUBINFO_SUBJECT_FILE, false, rcDest))
		return false;

	// sub - subject window
	if(!m_ImgUI[UIIMG_SUBWND].Load(SUBINFO_SUBWND_FILE))
		return false;
	SetRect(&m_rcPos[UIT_SUBWND],
		SUBINFO_SUBWND_POS_X,
		SUBINFO_SUBWND_POS_Y,
		SUBINFO_SUBWND_POS_X + SUBINFO_SUBWND_SIZE_W,
		SUBINFO_SUBWND_POS_Y + SUBINFO_SUBWND_SIZE_H );

	SetRect(&rcDest,
		SUBINFO_BTN_PREV_POS_X,
		SUBINFO_BTN_PREV_POS_Y,
		SUBINFO_BTN_PREV_POS_X + SUBINFO_BTN_PREV_SIZE_W,
		SUBINFO_BTN_PREV_POS_Y + SUBINFO_BTN_PREV_SIZE_H );
	if(!m_BtnUI[UIBTN_SUBPREV].SetUp(SUBINFO_BTN_FILE_PREV, false, rcDest))
		return false;

	SetRect(&rcDest,
		SUBINFO_BTN_NEXT_POS_X,
		SUBINFO_BTN_NEXT_POS_Y,
		SUBINFO_BTN_NEXT_POS_X + SUBINFO_BTN_PREV_SIZE_W,
		SUBINFO_BTN_NEXT_POS_Y + SUBINFO_BTN_PREV_SIZE_H );
	if(!m_BtnUI[UIBTN_SUBNEXT].SetUp(SUBINFO_BTN_FILE_NEXT, false, rcDest))
		return false;

	// menu
	SetRect(&m_rcPos[UIT_MENU],
		MENUBTN_POS_X,
		MENUBTN_POS_Y,
		MENUBTN_POS_X + MENUBTN_SIZE_W,
		MENUBTN_POS_Y + MENUBTN_SIZE_H);
	if(!m_BtnUI[UIBTN_MENU].SetUp(MENUBTN_FILE, false, m_rcPos[UIT_MENU]))
		return false;

	// minimap
	if(!m_ImgUI[UIIMG_MINIMAP].Load(MINIMAP_BACK_FILE))
		return false;
	SetRect(&m_rcPos[UIT_MINIMAPBACK],
			MINIMAP_BACK_POS_X,
			MINIMAP_BACK_POS_Y,
			MINIMAP_BACK_POS_X + MINIMAP_BACK_SIZE_W,
			MINIMAP_BACK_POS_Y + MINIMAP_BACK_SIZE_H);
	if(!m_ImgUI[UIIMG_MINIMAPCURSOR].Load(MINIMAP_CURSOR_FILE))
		return false;
	SetRect(&m_rcPos[UIT_MINIMAP],
			MINIMAP_START_X,
			MINIMAP_START_Y,
			MINIMAP_START_X + MINIMAP_SIZE_W,
			MINIMAP_START_Y + MINIMAP_SIZE_H );

	// dice btn
	SetRect(&m_rcPos[UIT_DICE],
			DICEBTN_POS_X,
			DICEBTN_POS_Y,
			DICEBTN_POS_X + DICEBTN_SIZE_W,
			DICEBTN_POS_Y + DICEBTN_SIZE_H );
	if(!m_BtnUI[UIBTN_DICE].SetUp(DICEBTN_FILE, false, m_rcPos[UIT_DICE]))
		return false;

	// item 사용, 타겟 charface img
	if(!m_ImgUI[UIIMG_FACEOUTLINE].Load(TARGET_OUTLINE_FILE))
		return false;

	if(!m_ImgUI[UIIMG_MAPTOOLTIP].Load(MAPTOOLTIP_FILE))
		return false;

	// couple 액자
	if(!m_ImgUI[UIIMG_COUPLEOUTLINE].Load(COUPLE_OUTLINE_FILE))
		return false;
	if(!m_ImgUI[UIIMG_LOVE].Load(COUPLE_LOVE_FILE))
		return false;

	// turn, ranking
	if(!m_ImgUI[UIIMG_TURNOUTLINE].Load(TURN_OUTLINE_FILE))
		return false;
	if(!m_ImgUI[UIIMG_CROWN].Load(TURN_CROWN_FILE))
		return false;

	if(!m_ImgUI[UIIMG_NUMBER].Load(TEXT_NUM_FILE))
		return false;
	if(!m_ImgUI[UIIMG_ICON].Load(TEXT_ICON_FILE))
		return false;
	if(!m_ImgUI[UIIMG_USERBOX].Load(ITEM_USER_BOX_FILE))
		return false;

	if(!m_ImgUI[UIIMG_YOURTURN].Load(TIMER_YOURTURN_FILE))
		return false;
	if(!m_ImgUI[UIIMG_TIMER].Load(TIMER_NUMBER_FILE))
		return false;

	if(!m_ImgUI[UIIMG_RESULT].Load(RESULT_FILE))
		return false;

	// map
	//	map btn
	SetRect(&rcDest,
		MAP_BTN_MAP_POS_X,
		MAP_BTN_MAP_POS_Y,
		MAP_BTN_MAP_POS_X + MAP_BTN_MAP_SIZE_W,
		MAP_BTN_MAP_POS_Y + MAP_BTN_MAP_SIZE_H );
	if(!m_BtnUI[UIBTN_MAPBTN].SetUp(MAP_BTN_MAP_FILE, false, rcDest))
		return false;
	memcpy(&m_rcPos[UIT_MAPBTN], &rcDest, sizeof(RECT));

	//	mapback
	if(!m_ImgUI[UIIMG_MAPBACK].Load(MAP_BACK_FILE))
		return false;
	SetRect(&m_rcPos[UIT_MAP],
		MAP_BACK_POS_X,
		MAP_BACK_POS_Y,
		MAP_BACK_POS_X + MAP_BACK_SIZE_W,
		MAP_BACK_POS_Y + MAP_BACK_SIZE_H);

	//	mapbg
	if(!m_ImgUI[UIIMG_MAPBG].Load(MAP_BG_FILE))
		return false;

	//	map player, outline
	if(!m_ImgUI[UIIMG_MAPPLAYER].Load(MAP_PLAYER_FILE))
		return false;
	if(!m_ImgUI[UIIMG_MAPPLAYEROUT].Load(MAP_PLAYEROUT_FILE))
		return false;
	if(!m_ImgUI[UIIMG_MAPPLAYERBAR].Load(MAP_PLAYERBAR_FILE))
		return false;
	if(!m_ImgUI[UIIMG_MAPLOVE].Load(MAP_PLAYERLOVE_FILE))
		return false;

	m_uimode = UIM_NONE;
	m_bTargetByMove = false;
	m_timer.SetUp();
	m_bItemUsed = false;

	return true;
}

void gUIGame::MainLoop()
{

}

void gUIGame::Draw()
{
	gPlayerContainer	*gPC	= gPlayerContainer::GetIF();
	gGameCore			*gc		= gGameCore::GetIF();
	gSubjectContainer	*sc		= gSubjectContainer::GetIF();
	gMap				*map	= gMap::GetIF();

	char	szBuf[128];
	int		i;

	// maptooltip
	if(m_uimode != UIM_MAP)
	{
		POINT	ptMouse;
		ptMouse.x = gMouse::GetIF()->m_nPosX;
		ptMouse.y = gMouse::GetIF()->m_nPosY;
		if(!IsUIRange(ptMouse.x, ptMouse.y))
		{
			if(!gChat::GetIF()->PointInUI(ptMouse.x, ptMouse.y))
			{
				int		nToolTipPos = map->viewabsToCon(ptMouse);
				if(nToolTipPos < LINEX*LINEY)
				{
					gTile	*tile = &map->tileMap[nToolTipPos];
					if(tile->tileType != TY_NONE)
					{
						ptMouse.x += MAPTOOLTIP_TERM_MOUSE;
						ptMouse.y += MAPTOOLTIP_TERM_MOUSE;
						if(ptMouse.x + MAPTOOLTIP_SIZE_W > WNDSIZEW)
							ptMouse.x = WNDSIZEW - MAPTOOLTIP_SIZE_W;
						if(ptMouse.y + MAPTOOLTIP_SIZE_H > CHAT_POS_Y)
							ptMouse.y = CHAT_POS_Y - MAPTOOLTIP_SIZE_H;

						m_ImgUI[UIIMG_MAPTOOLTIP].Draw(ptMouse.x, ptMouse.y);

						int		textPosX = ptMouse.x + MAPTOOLTIP_TEXT_X;
						int		textPosY = ptMouse.y + MAPTOOLTIP_TEXT_Y;
						gUtil::BeginText();
						if(tile->subject)
						{
							gUtil::Text(textPosX, textPosY, tile->subject);
							textPosY += MAPTOOLTIP_TEXT_TERM_Y;
						}
						if(tile->college)
						{
							gUtil::Text(textPosX, textPosY, tile->college);
							//textPosY += MAPTOOLTIP_TEXT_TERM_Y;
						}
						if(tile->building)
						{
							gUtil::Text(textPosX + MAPTOOLTIP_TEXT_TERM_X, textPosY, tile->building);
						}
						gUtil::EndText();

						if(tile->tileType == TY_CLASS)
						{
							gSubmitCore	*submit = gSubmitCore::GetIF();

							RECT	rcDest, rcSour;

							SetRect(&rcDest,
								ptMouse.x + MAPTOOLTIP_IMG_POS_X,
								ptMouse.y + MAPTOOLTIP_IMG_POS_Y,
								ptMouse.x + MAPTOOLTIP_IMG_POS_X + MAPTOOLTIP_IMG_SIZE_W,
								ptMouse.y + MAPTOOLTIP_IMG_POS_Y + MAPTOOLTIP_IMG_SIZE_H);

							for(i = 0; i < CLASSSEAT; i++)
							{
								BYTE	subject = submit->m_subject[tile->flag2][i];
								if(subject != NOSEAT && subject != AVAILSEAT)
								{
									gImage	*img = &gPC->m_ImgInfo[ gPC->m_GPlayerList[ subject ].ctype ].ImgPic;
									SetRect(&rcSour,
											0, 0, img->m_nWidth, img->m_nHeight);

									img->Draw(rcDest, rcSour);
									OffsetRect(&rcDest, (MAPTOOLTIP_IMG_SIZE_W + MAPTOOLTIP_IMG_TERM_X), 0);
								}
							}
						}
					}
				}
			}
		}
	}

	gChat::GetIF()->Draw();

	// image
	// show always
		// MainInfo
		gPC->m_ImgInfo[gPC->m_MyGamePlayer.ctype].ImgPic.Draw(MAININFO_PIC_POS_X, MAININFO_PIC_POS_Y);
		m_ImgUI[UIIMG_MAININFO].Draw(UI_POS_MAININFO_X, UI_POS_MAININFO_Y);

		m_rcBarDest.right = m_rcBarDest.left + gPC->m_MyGamePlayer.nStamina * MAININFO_BARGUAGE_SIZE_W / 10;
		m_ImgUI[UIIMG_BARGUAGE].Draw(m_rcBarDest, m_rcBarSour);
		m_ImgUI[UIIMG_BAROUTLINE].Draw(MAININFO_BARLINE_POS_X, MAININFO_BARLINE_POS_Y);

		// minimap
		m_ImgUI[UIIMG_MINIMAP].Draw(MINIMAP_BACK_POS_X, MINIMAP_BACK_POS_Y);
		map->DrawMinimap(MINIMAP_START_X, MINIMAP_START_Y, MINIMAP_SOLUTION);
		int		nMiniPosX, nMiniPosY;
		nMiniPosX = MINIMAP_START_X + int(MINIMAP_SIZE_W * map->GetPosRateX());
		nMiniPosY = MINIMAP_START_Y + int(MINIMAP_SIZE_H * map->GetPosRateY());
		m_ImgUI[UIIMG_MINIMAPCURSOR].Draw(nMiniPosX, nMiniPosY);
	
		// menu
		m_BtnUI[UIBTN_MENU].Draw();

		// dice btn
		if(!gPC->isTurn(gc->m_nTurn))
			m_BtnUI[UIBTN_DICE].m_eBtnMode = EBM_CLICK;

		m_BtnUI[UIBTN_DICE].Draw();

		m_ImgUI[UIIMG_SUBINFO].Draw(SUBINFO_POS_X, SUBINFO_POS_Y);
		m_BtnUI[UIBTN_ITEMCARD].Draw();
		m_BtnUI[UIBTN_SUBJECT].Draw();
		m_BtnUI[UIBTN_MAPBTN].Draw();

		// 연애
		//if(strlen(gPC->m_MyGamePlayer.szCouple) != 0)
		if(m_bCouple)
		{
			int			coupleIdx = gPC->GetGPIndex(gPC->m_MyGamePlayer.szCouple);
			gImage*		img = &gPC->m_ImgInfo[gPC->m_GPlayerList[coupleIdx].ctype].ImgPic;

			RECT		rcDest, rcSour;

			// 사진
			SetRect(&rcDest,
				COUPLE_FACE_POS_X,	COUPLE_FACE_POS_Y,
				COUPLE_FACE_POS_X + COUPLE_FACE_SIZE_W, COUPLE_FACE_POS_Y + COUPLE_FACE_SIZE_H);
			SetRect(&rcSour,
				0, 0, img->m_nWidth, img->m_nHeight);

			img->Draw(rcDest, rcSour);

			// 액자
			m_ImgUI[UIIMG_COUPLEOUTLINE].Draw(COUPLE_OUTLINE_POS_X, COUPLE_OUTLINE_POS_Y);

			// 하트 게이지
			for(i = 0; i < gPC->m_MyGamePlayer.nLove; i++)
			{
				SetRect(&rcDest,
					COUPLE_LOVE_POS_X, COUPLE_LOVE_POS_Y,
					COUPLE_LOVE_POS_X + COUPLE_LOVE_SIZE_W, COUPLE_LOVE_POS_Y + COUPLE_LOVE_SIZE_H);
				OffsetRect(&rcDest,
					(COUPLE_LOVE_SIZE_W + COUPLE_LOVE_TERM_X) * i, 0);
				SetRect(&rcSour,
					0, 0, COUPLE_LOVE_SIZE_W, COUPLE_LOVE_SIZE_H);
				m_ImgUI[UIIMG_LOVE].Draw(rcDest, rcSour, false);
			}
			for(; i < 3; i++)
			{
				SetRect(&rcDest,
					COUPLE_LOVE_POS_X, COUPLE_LOVE_POS_Y,
					COUPLE_LOVE_POS_X + COUPLE_LOVE_SIZE_W, COUPLE_LOVE_POS_Y + COUPLE_LOVE_SIZE_H);
				OffsetRect(&rcDest,
					(COUPLE_LOVE_SIZE_W + COUPLE_LOVE_TERM_X) * i, 0);
				SetRect(&rcSour,
					0, 0, COUPLE_LOVE_SIZE_W, COUPLE_LOVE_SIZE_H);
				OffsetRect(&rcSour, COUPLE_LOVE_SIZE_W, 0);
				m_ImgUI[UIIMG_LOVE].Draw(rcDest, rcSour, false);
			}
		}

		// turn, rank
		int		nTurnCount = 0;
		for(i = 0; i < ROOMMAXPLAYER; i++)
		{
			if(strlen(gPC->m_GPlayerList[i].szID) == 0)
				continue;

			if(gGameCore::GetIF()->m_nTurn == i)
			{
				m_ImgUI[UIIMG_TURNOUTLINE].Draw(TURN_START_X + TURN_OUTLINE_TERM_X,
												TURN_START_Y + (TURN_TERM_Y * nTurnCount) + TURN_OUTLINE_TERM_Y);
			}
			if(gPC->m_GPlayerList[i].nRank == 1)
			{
				m_ImgUI[UIIMG_CROWN].Draw(TURN_START_X + TURN_CROWN_TERM_X,
										TURN_START_Y + (TURN_TERM_Y * nTurnCount) + TURN_CROWN_TERM_Y);
			}
			nTurnCount++;
		}

	// show always end

	switch(m_uimode)
	{
		case UIM_SUGANG:
			{
				m_ImgUI[UIIMG_SUBWND].Draw(SUBINFO_SUBWND_POS_X, SUBINFO_SUBWND_POS_Y);
				m_BtnUI[UIBTN_SUBPREV].Draw();
				m_BtnUI[UIBTN_SUBNEXT].Draw();
			}
			break;
		case UIM_ITEM:
			{
				gItemContainer	*ic = gItemContainer::GetIF();
				int		j = 0;
				for(i = 0; i < MAXITEMNUM; i++)
				{
					if(gPC->m_MyGamePlayer.nItem[i] == -1)
						continue;

					ic->m_ItemImg[ gPC->m_MyGamePlayer.nItem[i] ].Draw(ITEMCARD_POS_X + (ITEMCARD_TERM_X + ITEMCARDIMG_W) * j, ITEMCARD_POS_Y);
					j++;
				}
			}
			break;
		case UIM_TARGETSELECT_MULTI:
			{
				DrawTargetButton();
			}
			break;
		case UIM_ITEMUSEINFO:
			{
				int nFrame = m_timer.frame();

				//m_ImgUI[UIIMG_USERBOX].Draw(USEINFO_USER_POS_X - USEINFO_TARGET_TERM_X/2, USEINFO_CARD_POS_Y - 1);



				if(nFrame >= 1)
				{
					m_timer.frameEnd();
					PK_ITEMUSESTART_ASK		ask;

					strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
					gServer::GetIF()->Send(PL_ITEMUSESTART_ASK, sizeof(ask), &ask);
					m_uimode = UIM_NONE;
				}
				gItemContainer	*ic = gItemContainer::GetIF();
				gImage			*cardimg = &ic->m_ItemImg[m_nCardIdx];	
				DrawTargetButton();

				m_itemuser.img->Draw(m_itemuser.rcPos.left + 1, m_itemuser.rcPos.top + 1);
				m_ImgUI[UIIMG_FACEOUTLINE].Draw(m_itemuser.rcPos.left, m_itemuser.rcPos.top);

				cardimg->Draw(USEINFO_CARD_POS_X - ITEMCARD_SIZE_W/2, USEINFO_CARD_POS_Y);
			}
			break;
		case UIM_INFOCHANGE:
			{
				int nFrame = m_timer.frame();

				if(nFrame >= 1)
				{
					m_timer.frameEnd();
					PK_INFOCHANGEEND_ASK		ask;

					strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
					gServer::GetIF()->Send(PL_INFOCHANGEEND_ASK, sizeof(ask), &ask);
					m_uimode = UIM_NONE;
				}
				Draw_InfoChange();
			}
			break;
		case UIM_BECOUPLE:
			{
				int	nFrame = m_timer.frame();

				if(nFrame >= 1)
				{
					m_timer.frameEnd();
					PK_BECOUPLEEND_ASK		ask;

					strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
					gServer::GetIF()->Send(PL_BECOUPLEEND_ASK, sizeof(ask), &ask);
					m_uimode = UIM_NONE;
				}
				DrawTargetButton();

				RECT	rcDest, rcSour;
				SetRect(&rcDest, 
					BECOUPLE_HEART_X, BECOUPLE_HEART_Y,
					BECOUPLE_HEART_X + COUPLE_LOVE_SIZE_W, BECOUPLE_HEART_Y + COUPLE_LOVE_SIZE_H);
				SetRect(&rcSour,
					0, 0, COUPLE_LOVE_SIZE_W, COUPLE_LOVE_SIZE_H);

				if(!m_bCouple)
					OffsetRect(&rcSour, COUPLE_LOVE_SIZE_W * 2, 0);

				m_ImgUI[UIIMG_LOVE].Draw(rcDest, rcSour);
			}
			break;
		case UIM_RESULT:
			{
				m_ImgUI[UIIMG_RESULT].Draw(RESULT_POS_X, RESULT_POS_Y);
			}
			break;
	}
	

	// text
	gUtil::BeginText();

	// MainInfo
		gUtil::Text(MAININFO_ID_POS_X, MAININFO_ID_POS_Y, gPC->m_MyGamePlayer.szID);
		wsprintf(szBuf, "%d", gPC->m_MyGamePlayer.nLang);
		gUtil::Text(MAININFO_LANG_POS_X, MAININFO_LANG_POS_Y, szBuf);
		wsprintf(szBuf, "%d", gPC->m_MyGamePlayer.nMath);
		gUtil::Text(MAININFO_MATH_POS_X, MAININFO_MATH_POS_Y, szBuf);
		wsprintf(szBuf, "%d", gPC->m_MyGamePlayer.nArt);
		gUtil::Text(MAININFO_ART_POS_X, MAININFO_ART_POS_Y, szBuf);

		wsprintf(szBuf, "%d", gPC->m_MyGamePlayer.nDice6);
		gUtil::Text(MAININFO_DICE6_POS_X, MAININFO_DICE6_POS_Y, szBuf);
		wsprintf(szBuf, "%d", gPC->m_MyGamePlayer.nDice4);
		gUtil::Text(MAININFO_DICE4_POS_X, MAININFO_DICE4_POS_Y, szBuf);

		if(strlen(gPC->m_CharInfo[gPC->m_MyGamePlayer.ctype].szName) < 7)
			gUtil::Text(MAININFO_NAME_POS_X + 8, MAININFO_NAME_POS_Y, gPC->m_CharInfo[gPC->m_MyGamePlayer.ctype].szName);
		else
			gUtil::Text(MAININFO_NAME_POS_X, MAININFO_NAME_POS_Y, gPC->m_CharInfo[gPC->m_MyGamePlayer.ctype].szName);


	// rank, turn

		nTurnCount = 0;
		for(i = 0; i < ROOMMAXPLAYER; i++)
		{
			if(strlen(gPC->m_GPlayerList[i].szID) == 0)
				continue;

			gUtil::TextOutLine(TURN_START_X + 2, TURN_START_Y + (TURN_TERM_Y * nTurnCount), gPC->m_GPlayerList[i].szID);
			nTurnCount++;
		}
/*
	// pinfo
		gUtil::Text(PINFO_INFO_POS_X + PINFO_ID_TERM_X, PINFO_INFO_POS_Y + PINFO_ID_TERM_Y,
					gPC->m_GPlayerList[ m_rankIdx[m_nCurPInfo] ].szID);
		if(m_rankIdx[ m_nCurPInfo + 1 ] != -1)
			gUtil::Text(PINFO_INFO_POS_X + PINFO_ID_TERM_X, PINFO_INFO_POS_Y + PINFO_ID_TERM_Y + PINFO_INFO_TERM_Y,
				gPC->m_GPlayerList[ m_rankIdx[m_nCurPInfo + 1] ].szID);
*/


	// sub - subwnd
		if(m_uimode == UIM_SUGANG)
		{
			GAMEPLAYER	*gp = &gPC->m_GPlayerList[m_nSubSel];

			gUtil::Text(SUBINFO_ID_POS_X, SUBINFO_ID_POS_Y, gp->szID);
			for(i = 0; i < MAXSUBJECT; i++)
			{	
				gUtil::Text(SUBINFO_BUILDING_POS_X, SUBINFO_SUBNAME_POS_Y + (SUBINFO_SUBNAME_TERM_Y * i),
						sc->m_subject[ gp->bySubIdx[i] ].building);

				gUtil::Text(SUBINFO_SUBNAME_POS_X, SUBINFO_SUBNAME_POS_Y + (SUBINFO_SUBNAME_TERM_Y * i),
						sc->m_subject[ gp->bySubIdx[i] ].subject);

				sprintf_s(szBuf, "%.1f", gp->fGrade[i]);
				gUtil::Text(SUBINFO_GRADE_POS_X, SUBINFO_SUBNAME_POS_Y + (SUBINFO_SUBNAME_TERM_Y * i),
					szBuf);
			}
			sprintf_s(szBuf, "%.1f", gp->fAvGrade);
		}
		//sprintf_s(szBuf, ".1f", )

	// result
		if(m_uimode == UIM_RESULT)
		{
			int			nLineCount = 0;
			for(i = 0; i < ROOMMAXPLAYER; i++)
			{
				if(m_rankIdx[i] == -1)
					continue;

				if(strlen(gPC->m_GPlayerList[ m_rankIdx[i] ].szID) == 0)
					continue;

				gUtil::TextOutLine(RESULT_POS_START_X, RESULT_POS_START_Y + nLineCount * RESULT_TERM_Y,
								gPC->m_GPlayerList[ m_rankIdx[i] ].szID);

				sprintf_s(szBuf, "%.1f", gPC->m_GPlayerList[ m_rankIdx[i] ].fAvGrade);
				gUtil::TextOutLine(RESULT_POS_START_X + RESULT_TERM_X, RESULT_POS_START_Y + nLineCount * RESULT_TERM_Y, szBuf);

				wsprintf(szBuf, "%d", gPC->m_GPlayerList[ m_rankIdx[i] ].nRank);
				gUtil::TextOutLine(RESULT_POS_START_X + RESULT_TERM_X * 2, RESULT_POS_START_Y + nLineCount * RESULT_TERM_Y, szBuf);

				nLineCount++;
			}

			int		nFrame = m_timer.frame();
			if(nFrame >= 1)
			{
				m_timer.frameEnd();
				gRoomCore::GetIF()->SendRoomBack();	//방나가고돌아오기수정
			}
		}

	gUtil::EndText();

	if(m_uimode == UIM_SUGANG)
	{
		gUtil::SetSize(SUBINFO_AVGRADE_FONTSIZE);
		gUtil::BeginText();
			gUtil::Text(SUBINFO_AVGRADE_POS_X, SUBINFO_AVGRADE_POS_Y, szBuf);
		gUtil::EndText();
		gUtil::SetDefaultFont();
	}

	// map
	if(m_uimode == UIM_MAP)
	{
		m_ImgUI[UIIMG_MAPBACK].Draw(MAP_BACK_POS_X, MAP_BACK_POS_Y);
		m_ImgUI[UIIMG_MAPBG].Draw(MAP_BG_POS_X, MAP_BG_POS_Y);
		map->DrawMap();

		// player info
		int		nPlayerCount = 0;
		for(i = 0; i < ROOMMAXPLAYER; i++)
		{
			if(strlen(gPC->m_GPlayerList[i].szID) == 0)
				continue;

			int		nYPos = MAP_PLAYER_POS_Y + (MAP_PLAYER_SIZE_H + MAP_PLAYER_TERM_Y) * nPlayerCount;
			m_ImgUI[UIIMG_MAPPLAYER].Draw(MAP_PLAYER_POS_X, nYPos);
			gImage*	pic = &gPC->m_ImgInfo[ gPC->m_GPlayerList[i].ctype ].ImgPic;
			RECT		rcDest = {	MAP_PLAYER_POS_X + 6,
									nYPos + 7,
									MAP_PLAYER_POS_X + 6 + 28,
									nYPos + 7 + 32 };
			RECT		rcSour = {0, 0, pic->m_nWidth, pic->m_nHeight};
			pic->Draw(rcDest, rcSour);

			int		couple = gPC->GetCoupleIndex(i);
			if(couple != -1)
			{
				OffsetRect(&rcDest, 138, 0);
				pic = &gPC->m_ImgInfo[ gPC->m_GPlayerList[couple].ctype ].ImgPic;
				pic->Draw(rcDest, rcSour);

				SetRect(&rcDest,
						MAP_PLAYERLOVE_POS_X,
						nYPos + MAP_PLAYERLOVE_POS_Y,
						MAP_PLAYERLOVE_POS_X + MAP_PLAYERLOVE_SIZE_W,
						nYPos + MAP_PLAYERLOVE_POS_Y + MAP_PLAYERLOVE_SIZE_H );
				SetRect(&rcSour, 0, 0, MAP_PLAYERLOVE_SIZE_W, MAP_PLAYERLOVE_SIZE_H);
				int nLoveCount;
				for(nLoveCount = 0; nLoveCount < gPC->m_GPlayerList[i].nLove; nLoveCount++)
				{
					m_ImgUI[UIIMG_MAPLOVE].Draw(rcDest, rcSour);
					OffsetRect(&rcDest, 0, MAP_PLAYERLOVE_TERM_Y + MAP_PLAYERLOVE_SIZE_H);
				}
				OffsetRect(&rcSour, MAP_PLAYERLOVE_SIZE_W, 0);
				for(; nLoveCount < 3; nLoveCount++)
				{
					m_ImgUI[UIIMG_MAPLOVE].Draw(rcDest, rcSour);
					OffsetRect(&rcDest, 0, MAP_PLAYERLOVE_TERM_Y + MAP_PLAYERLOVE_SIZE_H);
				}
			}

			if(i == m_nCharSelected)
				m_ImgUI[UIIMG_MAPPLAYEROUT].Draw(MAP_PLAYER_POS_X - 3, nYPos - 3);

			rcSour.left		= 0;
			rcSour.top		= 0;
			rcSour.right	= MAP_PLAYERBAR_SIZE_W * gPC->m_GPlayerList[i].nStamina / 10;
			rcSour.bottom	= rcSour.top + MAP_PLAYERBAR_SIZE_H;

			rcDest = rcSour;
			OffsetRect(&rcDest, MAP_PLAYER_POS_X + MAP_PLAYERBAR_POS_X, nYPos + MAP_PLAYERBAR_POS_Y);
			m_ImgUI[UIIMG_MAPPLAYERBAR].Draw(rcDest, rcSour);

			nPlayerCount++;
		}


		gUtil::BeginText();
		// grade
		GAMEPLAYER	*gp = &gPC->m_GPlayerList[m_nCharSelected];
		for(i = 0; i < MAXSUBJECT; i++)
		{	
			sprintf_s(szBuf, "%.1f", gp->fGrade[i]);
			gUtil::TextOutLine(s_ptPosGrade[ gp->bySubIdx[i] ].x, s_ptPosGrade[ gp->bySubIdx[i] ].y, szBuf);
		}
		nPlayerCount = 0;
		for(i = 0; i < ROOMMAXPLAYER; i++)
		{
			if(strlen(gPC->m_GPlayerList[i].szID) == 0)
				continue;

			int		nYPos = MAP_PLAYER_POS_Y + (MAP_PLAYER_SIZE_H + MAP_PLAYER_TERM_Y) * nPlayerCount;

			gUtil::Text(MAP_PLAYER_POS_X + 43, nYPos + 5, gPC->m_GPlayerList[i].szID);
			
			sprintf(szBuf, "%d", gPC->m_GPlayerList[i].nLang);
			gUtil::Text(MAP_PLAYER_POS_X + 59, nYPos + 20, szBuf);
			sprintf(szBuf, "%d", gPC->m_GPlayerList[i].nMath);
			gUtil::Text(MAP_PLAYER_POS_X + 90, nYPos + 20, szBuf);
			sprintf(szBuf, "%d", gPC->m_GPlayerList[i].nArt);
			gUtil::Text(MAP_PLAYER_POS_X + 122, nYPos + 20, szBuf);
			nPlayerCount++;
		}

		// stat
		gUtil::EndText();

		// maptooltip
		POINT	ptMouse, ptDraw;
		ptMouse.x = gMouse::GetIF()->m_nPosX;
		ptMouse.y = gMouse::GetIF()->m_nPosY;
		ptDraw = ptMouse;

		if(gUtil::PointInRect(ptMouse.x, ptMouse.y, m_rcPos[UIT_MAP]))
		{
			RECT		rcMap = {	MAP_BG_POS_X,
									MAP_BG_POS_Y,
									MAP_BG_POS_X + MAP_BG_SIZE_W,
									MAP_BG_POS_Y + MAP_BG_SIZE_H };

			if(gUtil::PointInRect(ptMouse.x, ptMouse.y, rcMap))
			{
				ptMouse.x -= MAP_BG_POS_X;
				ptMouse.y -= MAP_BG_POS_Y;
				ptMouse.x *= 6;
				ptMouse.y *= 6;

				POINT	ptCon = map->absToCon(ptMouse);
				int		nToolTipPos = ptCon.x * LINEY + ptCon.y;
				gTile	*tile = &map->tileMap[nToolTipPos];
				if(tile->tileType != TY_NONE)
				{
					ptDraw.x += MAPTOOLTIP_TERM_MOUSE;
					ptDraw.y += MAPTOOLTIP_TERM_MOUSE;
					if(ptDraw.x + MAPTOOLTIP_SIZE_W > WNDSIZEW)
						ptDraw.x = WNDSIZEW - MAPTOOLTIP_SIZE_W;
					if(ptDraw.y + MAPTOOLTIP_SIZE_H > CHAT_POS_Y)
						ptDraw.y = CHAT_POS_Y - MAPTOOLTIP_SIZE_H;

					m_ImgUI[UIIMG_MAPTOOLTIP].Draw(ptDraw.x, ptDraw.y);

					int		textPosX = ptDraw.x + MAPTOOLTIP_TEXT_X;
					int		textPosY = ptDraw.y + MAPTOOLTIP_TEXT_Y;
					gUtil::BeginText();
					if(tile->subject)
					{
						gUtil::Text(textPosX, textPosY, tile->subject);
						textPosY += MAPTOOLTIP_TEXT_TERM_Y;
					}
					if(tile->college)
					{
						gUtil::Text(textPosX, textPosY, tile->college);
						//textPosY += MAPTOOLTIP_TEXT_TERM_Y;
					}
					if(tile->building)
					{
						gUtil::Text(textPosX + MAPTOOLTIP_TEXT_TERM_X, textPosY, tile->building);
					}
					gUtil::EndText();

					if(tile->tileType == TY_CLASS)
					{
						gSubmitCore	*submit = gSubmitCore::GetIF();

						RECT	rcDest, rcSour;

						SetRect(&rcDest,
							ptDraw.x + MAPTOOLTIP_IMG_POS_X,
							ptDraw.y + MAPTOOLTIP_IMG_POS_Y,
							ptDraw.x + MAPTOOLTIP_IMG_POS_X + MAPTOOLTIP_IMG_SIZE_W,
							ptDraw.y + MAPTOOLTIP_IMG_POS_Y + MAPTOOLTIP_IMG_SIZE_H);

						for(i = 0; i < CLASSSEAT; i++)
						{
							BYTE	subject = submit->m_subject[tile->flag2][i];
							if(subject != NOSEAT && subject != AVAILSEAT)
							{
								gImage	*img = &gPC->m_ImgInfo[ gPC->m_GPlayerList[ subject ].ctype ].ImgPic;
								SetRect(&rcSour,
									0, 0, img->m_nWidth, img->m_nHeight);

								img->Draw(rcDest, rcSour);
								OffsetRect(&rcDest, (MAPTOOLTIP_IMG_SIZE_W + MAPTOOLTIP_IMG_TERM_X), 0);
							}
						}
					}
				}
			}
		}
	}

	// your turn
	if(m_bShowYourTurn)
	{
		if(GetTickCount() - m_nYourTurnTimer > TIMER_SHOWTIME)
			m_bShowYourTurn = false;
		else
		{
			m_ImgUI[UIIMG_YOURTURN].Draw(TIMER_YOURTURN_POS_X, TIMER_YOURTURN_POS_Y);
		}
	}
	// time count
	if(m_bShowTimeCount)
	{
		int		termX;
		if((termX = GetTickCount() - gc->m_turnTime) > SLEEPTIMEMAX - 5000)
		{
			if(!m_bDrawedTimeCount)
			{
				gPlaySoundCore::GetIF()->PlayEffectSound(EFFECT_FILE_10, true);
				m_bDrawedTimeCount = true;
			}

			termX = SLEEPTIMEMAX - termX;
			termX /= 1000;
			if(termX >= 0 && termX <= 4)
			{
				RECT	rcDest, rcSour;
				SetRect(&rcDest,
					TIMER_NUMBER_POS_X,
					TIMER_NUMBER_POS_Y,
					TIMER_NUMBER_POS_X + TIMER_NUMBER_SIZE_W,
					TIMER_NUMBER_POS_Y + TIMER_NUMBER_SIZE_H);
				SetRect(&rcSour,
					0, 0, TIMER_NUMBER_SIZE_W, TIMER_NUMBER_SIZE_H);

				OffsetRect(&rcSour, (termX * TIMER_NUMBER_SIZE_W), 0);
				m_ImgUI[UIIMG_TIMER].Draw(rcDest, rcSour);
			}
		}
	}
}


void gUIGame::Release()
{
	int			i;

	for(i = 0; i < UIIMG_END; i++)
		m_ImgUI[i].Release();

	for(i = 0; i < UIBTN_END; i++)
		m_BtnUI[i].Release();

}

bool gUIGame::OnLButtonDown()
{
	gPlayerContainer	*gPC	= gPlayerContainer::GetIF();
	gMouse				*mouse	= gMouse::GetIF();
	gGameCore			*gc		= gGameCore::GetIF();
	gItemContainer		*ic		= gItemContainer::GetIF();
	gMap				*map	= gMap::GetIF();


	if(m_uimode == UIM_INFOCHANGE
		|| m_uimode == UIM_ITEMUSEINFO)
		return false;
	
	if(gUtil::PointInRect(mouse->m_nPosX, mouse->m_nPosY, m_rcPos[UIT_MINIMAPBACK]))
	{
		int		sx, sy;
		float	ratex, ratey;
		sx = mouse->m_nPosX - MINIMAP_START_X;
		sy = mouse->m_nPosY - MINIMAP_START_Y;
		ratex = float(sx) / MINIMAP_SIZE_W;
		ratey = float(sy) / MINIMAP_SIZE_H;
		map->SetPosByRateX(ratex);
		map->SetPosByRateY(ratey);
		return true;
	}
	if(m_BtnUI[UIBTN_DICE].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		if(gc->m_bMoving || gc->m_bBusing)
			return true;
		if(gPC->isTurn(gc->m_nTurn))
			gc->SendMoveAsk();

		return true;
	}
	if(m_BtnUI[UIBTN_SUBJECT].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		if(m_uimode != UIM_SUGANG)
		{
			m_nSubSel	= gPC->GetMyGPIndex();
			m_uimode	= UIM_SUGANG;
		}
		else
			m_uimode	= UIM_NONE;

		return true;
	}
	if(m_BtnUI[UIBTN_ITEMCARD].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		if(m_uimode != UIM_ITEM)
		{
			if(gPC->GetMyItemNum() > 0)
				m_uimode	= UIM_ITEM;
			else
				gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_20);
		}
		else
			m_uimode	= UIM_NONE;

		return true;
	}
	//2010. 12. 28.
	//MENU module 추가합시당....당....
	//PopUp으로 메뉴 고르는걸 띄울까요?
	//고르면 주사위 및 다른건 막히는건가? 아니면... 생각할 게 많네여...
	if(m_BtnUI[UIBTN_MENU].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		return true;
	}
	if(m_BtnUI[UIBTN_MAPBTN].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		if(m_uimode)
			m_uimode = UIM_NONE;
		else
		{
			m_uimode = UIM_MAP;
			m_nCharSelected = gPC->GetMyPIndex();
		}
		return true;
	}

	switch(m_uimode)
	{
		case UIM_ITEM:				// 아이템 모드
			{
				if(gPC->GetMyGPIndex() != gGameCore::GetIF()->m_nTurn)
					return true;
				if(gGameCore::GetIF()->m_bMoved)
					return true;
				if(m_bItemUsed)
					return true;

				m_bTargetByMove = false;

				int		i;
				for(i = 0; i < MAXITEMNUM; i++)
				{
					if(gPC->m_MyGamePlayer.nItem[i] == -1)
						continue;

					RECT	rcTemp;
					rcTemp.left		= ITEMCARD_POS_X + (ITEMCARD_POS_X + ITEMCARDIMG_W) * i;
					rcTemp.right	= rcTemp.left + ITEMCARDIMG_W;
					rcTemp.top		= ITEMCARD_POS_Y;
					rcTemp.bottom	= rcTemp.top + ITEMCARDIMG_H;

					if(gUtil::PointInRect(mouse->m_nPosX, mouse->m_nPosY, rcTemp))
					{
						int					ItemIdx = gPC->m_MyGamePlayer.nItem[i];
						ITEMCARD			*item = &ic->m_ItemList[ ItemIdx ];
						PK_ITEMUSE_ASK		ask;

						switch(item->type)
						{
							case ITEM_STAT: case ITEM_STAMINA: case ITEM_NOCLASS: case ITEM_TOGETHERCLASS:
								{
									if(item->target == TARGET_OTHER || item->target == TARGET_MEOTHER)
									{
										m_nItemID	= ItemIdx;
										m_uimode	= UIM_TARGETSELECT;
									}
									else
									{
										strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
										ask.nItemID = ItemIdx;

										gServer::GetIF()->Send(PL_ITEMUSE_ASK, sizeof ask, &ask);
										m_bItemUsed = true;
									}
								}
								break;
							case ITEM_MOVEPLACE:
								{
									if(item->target == TARGET_OTHER || item->target == TARGET_MEOTHER)
									{
										m_nItemID	= ItemIdx;
										m_uimode	= UIM_TARGETSELECT;
										m_bTargetByMove = true;
									}
									else
									{
										strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
										ask.nItemID = ItemIdx;

										gServer::GetIF()->Send(PL_ITEMUSE_ASK, sizeof ask, &ask);
										m_bItemUsed = true;
									}
								}
								break;
							case ITEM_MOVESELECT:
								{
									if(item->target == TARGET_OTHER || item->target == TARGET_MEOTHER)
									{
										m_nItemID	= ItemIdx;
										m_uimode	= UIM_TARGETSELECT;
										m_bTargetByMove = true;
									}
									else
									{
										m_nItemID	= ItemIdx;
										m_uimode	= UIM_PLACESELECT;
									}
								}
								break;
							// 연애요소 추가
							case ITEM_DASH: case ITEM_POWERDASH:
								{
									// 난 이미 커플
									//if(strlen(gPC->m_MyGamePlayer.szCouple) != 0)
									if(m_bCouple)
									{
										gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_24);
										return true;
									}
									m_nItemID	= ItemIdx;
									m_uimode	= UIM_TARGETSELECT;
								}
								break;
							case ITEM_LOVE:
								{
									if(item->target == TARGET_OTHERCOUPLE)
									{
										m_nItemID	= ItemIdx;
										m_uimode	= UIM_TARGETSELECT;
									}
									else
									{
										//if(strlen(gPC->m_MyGamePlayer.szCouple) == 0)
										if(!m_bCouple)
										{
											gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_25);
											return true;
										}
										strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
										ask.nItemID = ItemIdx;

										gServer::GetIF()->Send(PL_ITEMUSE_ASK, sizeof ask, &ask);
										m_bItemUsed = true;
									}
								}
								break;
						}
						return true;
					}
				}
			}
		break;
		case UIM_TARGETSELECT:
			{
				POINT		pt;
				pt.x = mouse->m_nPosX;
				pt.y = mouse->m_nPosY;

				int		nPos = map->viewabsToCon(pt);
				int		numchar = gPC->GetCharNumPos(nPos);

				if(gPC->m_MyGamePlayer.nPos == nPos)
					numchar--;

				if(numchar <= 0)
					break;
				else if(numchar == 1)
				{
					GAMEPLAYER	*target = gPC->GetPlayerByPos(nPos);

					if(m_bTargetByMove)
					{
						strcpy(m_szTarget, target->szID);
						m_uimode = UIM_PLACESELECT;
					}
					else
					{
						ITEMCARD	*item = &gItemContainer::GetIF()->m_ItemList[ m_nItemID ];
						switch(item->target)
						{
							case TARGET_OTHERSEX:
								{
									// 동성
									if(gPC->m_CharInfo[target->ctype].bMale == gPC->m_CharInfo[gPC->m_MyGamePlayer.ctype].bMale)
									{
										gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_22);
										return true;
									}
									if(item->type == ITEM_DASH || item->type == ITEM_POWERDASH)
									{
										// 이미 대상은 커플임
										if(strlen(target->szCouple) != 0)
										{
											gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_23);
											return true;
										}
									}
								}
								break;
							case TARGET_OTHERCOUPLE:
								{
									// 내 커플 선택
									if(m_bCouple && strcmp(target->szID, gPC->m_MyGamePlayer.szCouple) == 0)
									{
										gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_26);
										return true;
									}
									// 상대가 커플이 아님
									if(!m_bCouple || strlen(target->szCouple) == 0)
									{
										gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_27);
										return true;
									}
								}
								break;
						}

						PK_ITEMUSE_ASK		ask;
						ask.nItemID	= m_nItemID;
						strcpy(ask.szID, gPC->m_MyPlayer.szID);
						strcpy(ask.szTarget, target->szID);

						gServer::GetIF()->Send(PL_ITEMUSE_ASK, sizeof(ask), &ask);
						m_uimode = UIM_NONE;
						m_bItemUsed = true;
					}
				}
				else
				{
					m_uimode = UIM_TARGETSELECT_MULTI;
					SetTargetButton(nPos, numchar);
				}
			}
			break;
		case UIM_TARGETSELECT_MULTI:
			{
				int		i;

				for(i = 0; i < m_nTargetNum; i++)
				{
					if(gUtil::PointInRect(mouse->m_nPosX, mouse->m_nPosY, m_target[i].rcPos))
					{
						if(m_bTargetByMove)
						{
							strcpy(m_szTarget, gPC->m_GPlayerList[ m_target[i].idx ].szID);
							m_uimode = UIM_PLACESELECT;

							break;
						}
						else
						{
							ITEMCARD	*item = &gItemContainer::GetIF()->m_ItemList[ m_nItemID ];
							switch(item->target)
							{
								case TARGET_OTHERSEX:
									{
										// 동성
										if(gPC->m_CharInfo[ gPC->m_GPlayerList[ m_target[i].idx ].ctype ].bMale
												== gPC->m_CharInfo[ gPC->m_MyGamePlayer.ctype ].bMale)
										{
											gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_22);
											return true;
										}
										if(item->type == ITEM_DASH || item->type == ITEM_POWERDASH)
										{
											// 이미 대상은 커플임
											if(strlen(gPC->m_GPlayerList[m_target[i].idx].szCouple) != 0)
											{
												gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_23);
												return true;
											}
										}
									}
									break;
								case TARGET_OTHERCOUPLE:
									{
										// 내 커플 선택
										if(m_bCouple && strcmp(gPC->m_GPlayerList [m_target[i].idx ].szID, gPC->m_MyGamePlayer.szCouple) == 0)
										{
											gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_26);
											return true;
										}
										// 상대가 커플이 아님
										if(strlen(gPC->m_GPlayerList[m_target[i].idx].szCouple) == 0)
										{
											gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_27);
											return true;
										}
									}
									break;
							}

							PK_ITEMUSE_ASK		ask;

							strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
							strcpy(ask.szTarget, gPC->m_GPlayerList[ m_target[i].idx ].szID);
							ask.nItemID = m_nItemID;

							gServer::GetIF()->Send(PL_ITEMUSE_ASK, sizeof(ask), &ask);
							m_uimode = UIM_NONE;
							m_bItemUsed = true;
							break;
						}
					}
				}
			}
			break;
		case UIM_PLACESELECT:
			{
				PK_ITEMUSE_ASK		ask;

				POINT	pt;
				pt.x = mouse->m_nPosX;
				pt.y = mouse->m_nPosY;

				int		nPos = map->viewabsToCon(pt);
				if(map->tileMap[nPos].tileType != TY_NONE)
				{
					strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
					ask.nStartPos	= gPC->m_MyGamePlayer.nPos;
					ask.nDestPos	= nPos;
					if(m_bTargetByMove)
					{
						strcpy(ask.szTarget, m_szTarget);
						m_bTargetByMove = false;
					}
					ask.nItemID = m_nItemID;
					gServer::GetIF()->Send(PL_ITEMUSE_ASK, sizeof(ask), &ask);
					m_uimode = UIM_NONE;
					m_bItemUsed = true;
				}
			}
			break;
		case UIM_SUGANG:				// 수강현황 모드
			{
				if(m_BtnUI[UIBTN_SUBPREV].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				{
					while(true)
					{
						m_nSubSel--;
						if(m_nSubSel < 0)
							m_nSubSel = ROOMMAXPLAYER - 1;

						if(strlen(gPC->m_GPlayerList[m_nSubSel].szID) == 0)
							continue;

						break;
					}
					return true;
				}
				if(m_BtnUI[UIBTN_SUBNEXT].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				{
					while(true)
					{
						m_nSubSel++;
						if(m_nSubSel >= ROOMMAXPLAYER)
							m_nSubSel = 0;

						if(strlen(gPC->m_GPlayerList[m_nSubSel].szID) == 0)
							continue;

						break;
					}
					return true;
				}
			}
			break;
		case UIM_MAP:
			{
				// player info
				int		i;
				int		nPlayerCount = 0;
				for(i = 0; i < ROOMMAXPLAYER; i++)
				{
					if(strlen(gPC->m_GPlayerList[i].szID) == 0)
						continue;

					int		nYPos = MAP_PLAYER_POS_Y + (MAP_PLAYER_SIZE_H + MAP_PLAYER_TERM_Y) * nPlayerCount;

					RECT	rcPos = {	MAP_PLAYER_POS_X,
										nYPos,
										MAP_PLAYER_POS_X + MAP_PLAYER_SIZE_W,
										nYPos + MAP_PLAYER_SIZE_H};

					if(gUtil::PointInRect(mouse->m_nPosX, mouse->m_nPosY, rcPos))
					{
						m_nCharSelected = i;
						break;
					}
					nPlayerCount++;
				}
			}
			break;
	}

	return false;
}

void gUIGame::SetTargetButton(int nPos, int charmax)
{
	gPlayerContainer	*pc = gPlayerContainer::GetIF();

	m_nTargetNum = charmax;

	int			i;
	int			nCount = 0;

	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strlen(pc->m_GPlayerList[i].szID) != 0)
		{
			if(pc->m_GPlayerList[i].nPos == nPos)
			{
				if(strcmp(pc->m_GPlayerList[i].szID, pc->m_MyGamePlayer.szID) != 0)
				{
					m_target[nCount].img = &pc->m_ImgInfo[ pc->m_GPlayerList[i].ctype ].ImgPic;
					m_target[nCount].idx = i;
					nCount++;
				}
			}
		}
	}

	// pos set - 구찮다. 케이스별로 하드코딩하자
	int		startx, starty;
	switch(m_nTargetNum)
	{
		case 2:
			{
				// ㅁ ㅁ
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W - TARGET_TERM_X/2;
				starty = TARGET_POS_CENTER_Y - TARGET_OUTLINE_SIZE_H / 2;
				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
			}
			break;
		case 3:
			{
				// ㅁ ㅁ ㅁ 
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 3/2 - TARGET_TERM_X;
				starty = TARGET_POS_CENTER_Y - TARGET_OUTLINE_SIZE_H / 2;
				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
			}
			break;
		case 4:
			{
				// ㅁ ㅁ ㅁ ㅁ
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 2 - TARGET_TERM_X * 3/2;
				starty = TARGET_POS_CENTER_Y - TARGET_OUTLINE_SIZE_H / 2;
				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
			}
			break;
		case 5:
			{
				//  ㅁ ㅁ
				// ㅁ ㅁ ㅁ 
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W - TARGET_TERM_X/2;
				starty = TARGET_POS_CENTER_Y - TARGET_OUTLINE_SIZE_H - TARGET_TERM_Y/2;
				for(i = 0; i < 2; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 3/2 - TARGET_TERM_X;
				starty += (TARGET_TERM_Y + TARGET_OUTLINE_SIZE_H);
				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
			}
			break;
		case 6:
			{
				// ㅁ ㅁ ㅁ
				// ㅁ ㅁ ㅁ 
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 3/2 - TARGET_TERM_X;
				starty = TARGET_POS_CENTER_Y - TARGET_OUTLINE_SIZE_H - TARGET_TERM_Y/2;
				for(i = 0; i < 3; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 3/2 - TARGET_TERM_X;
				starty += (TARGET_TERM_Y + TARGET_OUTLINE_SIZE_H);
				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
			}
			break;
		case 7:
			{
				//  ㅁ ㅁ ㅁ
				// ㅁ ㅁ ㅁ ㅁ
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 3/2 - TARGET_TERM_X;
				starty = TARGET_POS_CENTER_Y - TARGET_OUTLINE_SIZE_H - TARGET_TERM_Y/2;
				for(i = 0; i < 3; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 2 - TARGET_TERM_X * 3/2;
				starty += (TARGET_TERM_Y + TARGET_OUTLINE_SIZE_H);
				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
			}
			break;
	}
}

void gUIGame::OnLButtonUp()
{
	gMouse				*mouse	= gMouse::GetIF();

//	m_Scroll.OnLbuttonUp(mouse->m_nPosX, mouse->m_nPosY);
}

void gUIGame::OnMouseMove()
{
	gMouse		*mouse = gMouse::GetIF();

	int			i;

	for(i = 0; i < UIBTN_END; i++)
	{
		if(!m_BtnUI[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_BtnUI[i].m_eBtnMode = EBM_NONE;
		else
			m_BtnUI[i].m_eBtnMode = EBM_HOVER;
	}

	if(GetKeyState(VK_LBUTTON) < 0)
	{
		if(gUtil::PointInRect(mouse->m_nPosX, mouse->m_nPosY, m_rcPos[UIT_MINIMAPBACK]))
		{
			gMap	*map = gMap::GetIF();
			int		sx, sy;
			float	ratex, ratey;
			sx = mouse->m_nPosX - MINIMAP_START_X;
			sy = mouse->m_nPosY - MINIMAP_START_Y;
			ratex = float(sx) / MINIMAP_SIZE_W;
			ratey = float(sy) / MINIMAP_SIZE_H;
			map->SetPosByRateX(ratex);
			map->SetPosByRateY(ratey);
		}
	}
}

void gUIGame::OnRButtonDown()
{
	if(m_uimode == UIM_INFOCHANGE)
		return;

	if(m_uimode == UIM_TARGETSELECT)
	{
		m_uimode = UIM_ITEM;
		return;
	}
	if(m_uimode == UIM_TARGETSELECT_MULTI)
	{
		m_uimode = UIM_TARGETSELECT;
		return;
	}
	if(m_uimode == UIM_PLACESELECT)
	{
		if(m_bTargetByMove)
			m_uimode = UIM_TARGETSELECT;
		else
			m_uimode = UIM_ITEM;
		return;
	}
	if(m_uimode != UIM_NONE && !m_bItemUsed)
		m_uimode = UIM_NONE;
}

bool gUIGame::IsUIRange(int x, int y)
{
	int			i;

	for(i = 0; i < UIT_END; i++)
	{
		if( i == UIT_SUBWND && m_uimode != UIM_SUGANG )
			continue;

		if(i == UIT_MAP && m_uimode != UIM_MAP)
			continue;

		if(gUtil::PointInRect(x, y, m_rcPos[i]))
			return true;
	}

	return false;
}


void gUIGame::SetRankList()
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	memset(m_rankIdx, -1, sizeof(int) * ROOMMAXPLAYER);

	int			nRank = 1;
	int			nCount = 0;
	int			i;
	int			nPlayerNum = gPC->GetGPNum();

	while(true)
	{
		for(i = 0; i < ROOMMAXPLAYER; i++)
		{
			if(strlen(gPC->m_GPlayerList[i].szID) == 0)
				continue;

			if(gPC->m_GPlayerList[i].nRank == nRank)
				m_rankIdx[nCount++] = i;

 			if(nCount >= nPlayerNum)
 				return;
		}
		nRank++;
	}

}

bool gUIGame::Restore()
{
	int			i;

	for(i = 0; i < UIIMG_END; i++)
		if(!m_ImgUI[i].Restore())
			return false;
	for(i = 0; i < UIBTN_END; i++)
		if(!m_BtnUI[i].Restore())
			return false;

	return true;
}

void gUIGame::DrawTargetButton()
{
	int		i;

	for(i = 0; i < m_nTargetNum; i++)
	{
		m_target[i].img->Draw(m_target[i].rcPos.left + 1, m_target[i].rcPos.top + 1);
		m_ImgUI[UIIMG_FACEOUTLINE].Draw(m_target[i].rcPos.left, m_target[i].rcPos.top);
	}
}

void gUIGame::pk_itemuse_rep(PK_ITEMUSE_REP* rep)
{
	gUIGame::GetIF()->m_bShowTimeCount = false;
	gPlaySoundCore::GetIF()->StopEffectSound(EFFECT_FILE_10);

	gItemContainer		*ic = gItemContainer::GetIF();
	gPlayerContainer	*pc = gPlayerContainer::GetIF();

	ITEMCARD	*item = &ic->m_ItemList[rep->nItemID];
	int			userIdx	= pc->GetGPIndex(rep->szUser);

	m_nCardIdx = rep->nItemID;

	// 사용자 셋팅
	m_itemuser.idx = userIdx;
	m_itemuser.img = &pc->m_ImgInfo[ pc->m_GPlayerList[userIdx].ctype ].ImgPic;
	SetRect(&m_itemuser.rcPos,
		USEINFO_USER_POS_X - TARGET_OUTLINE_SIZE_W/2,
		USEINFO_USER_POS_Y,
		USEINFO_USER_POS_X - TARGET_OUTLINE_SIZE_W/2 + TARGET_OUTLINE_SIZE_W,
		USEINFO_USER_POS_Y + TARGET_OUTLINE_SIZE_H );


	switch(item->target)
	{
		case TARGET_ME:
			{
				m_nTargetNum = 1;
				m_target[0] = m_itemuser;
				m_target[0].rcPos.left = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				m_target[0].rcPos.right = m_target[0].rcPos.left + TARGET_OUTLINE_SIZE_W;
			}
			break;
		case TARGET_OTHER: case TARGET_OTHERSEX:
			{
				m_nTargetNum = 1;
				int	targetIdx = pc->GetGPIndex(rep->szTarget);

				m_target[0].idx = targetIdx;
				m_target[0].img = &pc->m_ImgInfo[ pc->m_GPlayerList[targetIdx].ctype ].ImgPic;
				m_target[0].rcPos = m_itemuser.rcPos;
				m_target[0].rcPos.left = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				m_target[0].rcPos.right = m_target[0].rcPos.left + TARGET_OUTLINE_SIZE_W;
			}
			break;
		case TARGET_MEOTHER:
			{
				m_nTargetNum = 2;
				// 사용자
				m_target[0] = m_itemuser;

				// 상대
				int	targetIdx = pc->GetGPIndex(rep->szTarget);

				m_target[1].idx = targetIdx;
				m_target[1].img = &pc->m_ImgInfo[ pc->m_GPlayerList[targetIdx].ctype ].ImgPic;

				int		i;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case TARGET_ALL:
			{
				m_nTargetNum = pc->GetGPNum();

				// 사용자
				m_target[0] = m_itemuser;
				// 다른 애들
				int		i;
				int		nCount = 1;
				for(i = 0; i < ROOMMAXPLAYER; i++)
				{
					if(strlen(pc->m_GPlayerList[i].szID) != 0)
					{
						if(strcmp(pc->m_GPlayerList[i].szID, pc->m_MyGamePlayer.szID) == 0)
							continue;

						m_target[nCount].idx = i;
						m_target[nCount].img = &pc->m_ImgInfo[ pc->m_GPlayerList[i].ctype ].ImgPic;
						nCount++;
					}
				}
				SetTargetButton_UseInfo();
			}
			break;
		case TARGET_ALLEXCEPTME:
			{
				m_nTargetNum = pc->GetGPNum() - 1;

				int		i, j;
				j = 0;
				for(i = 0; i < ROOMMAXPLAYER; i++)
				{
					if(strlen(pc->m_GPlayerList[i].szID) != 0)
					{
						if(strcmp(pc->m_GPlayerList[i].szID, pc->m_MyGamePlayer.szID) == 0)
							continue;

						m_target[j].idx = i;
						m_target[j].img = &pc->m_ImgInfo[ pc->m_GPlayerList[i].ctype ].ImgPic;
						j++;
					}
				}
				SetTargetButton_UseInfo();
			}
			break;
		case TARGET_MYCOUPLE:
			{
				if(strlen(pc->m_GPlayerList[m_itemuser.idx].szCouple) == 0)
					break;

				m_nTargetNum = 2;
				// 사용자
				m_target[0] = m_itemuser;

				// 사용자 커플
				int	targetIdx = pc->GetGPIndex( pc->m_GPlayerList[m_itemuser.idx].szCouple );

				m_target[1].idx = targetIdx;
				m_target[1].img = &pc->m_ImgInfo[ pc->m_GPlayerList[targetIdx].ctype ].ImgPic;

				int		i;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case TARGET_OTHERCOUPLE:
			{
				int targetIdx = pc->GetGPIndex(rep->szTarget);

				if(strlen(pc->m_GPlayerList[targetIdx].szCouple) == 0)
					break;

				m_nTargetNum = 2;

				m_target[0].idx = targetIdx;
				m_target[0].img = &pc->m_ImgInfo[ pc->m_GPlayerList[targetIdx].ctype ].ImgPic;

				m_target[1].idx = pc->GetGPIndex( pc->m_GPlayerList[targetIdx].szCouple );
				m_target[1].img = &pc->m_ImgInfo[ pc->m_GPlayerList[ m_target[1].idx ].ctype ].ImgPic;

				int		i;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case TARGET_ALLSINGLE:
			{
				int		i, j;
				j = 0;
				for(i = 0; i < ROOMMAXPLAYER; i++)
				{
					if(strlen(pc->m_GPlayerList[i].szID) != 0)
					{
						if(strlen(pc->m_GPlayerList[i].szCouple) != 0)
							continue;
						m_target[j].idx = i;
						m_target[j].img = &pc->m_ImgInfo[ pc->m_GPlayerList[i].ctype ].ImgPic;
						j++;
					}
				}

				m_nTargetNum = j;

				SetTargetButton_UseInfo();
			}
			break;
		case TARGET_ALLCOUPLE:
			{
				int		i, j;
				j = 0;
				for(i = 0; i < ROOMMAXPLAYER; i++)
				{
					if(strlen(pc->m_GPlayerList[i].szID) != 0)
					{
						if(strlen(pc->m_GPlayerList[i].szCouple) == 0)
							continue;
						m_target[j].idx = i;
						m_target[j].img = &pc->m_ImgInfo[ pc->m_GPlayerList[i].ctype ].ImgPic;
						j++;
					}
				}

				m_nTargetNum = j;
				SetTargetButton_UseInfo();
			}
			break;
	}
	gPlaySoundCore	*sound = gPlaySoundCore::GetIF();
	sound->PlayEffectSound(EFFECT_FILE_3);
	m_uimode = UIM_ITEMUSEINFO;
	m_timer.frameStart(USEINFO_TICK, 2);
}

void gUIGame::SetTargetButton_UseInfo()
{
	int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W - USEINFO_TARGET_TERM_X/2;
	int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;

/*
	int i,j,k=0;

	for(i=0;i<3;i++)
		for(j=0;j<2;j++) {
			if(k>=m_nTargetNum) break;
			SetRect(&m_target[k].rcPos, startx+j*(TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X), starty + i*(TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
				startx+ j*(TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W, starty + i*(TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H);
			k++;
		}
*/

	switch(m_nTargetNum)
	{
		case 1:
			{
				// ㅁ
				m_target[0].rcPos = m_itemuser.rcPos;
				m_target[0].rcPos.left = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				m_target[0].rcPos.right = m_target[0].rcPos.left + TARGET_OUTLINE_SIZE_W;

			}
			break;
		case 2:
			{
				// ㅁ
				// ㅁ
				int		i;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case 3:
			{
				// ㅁ
				// ㅁ
				// ㅁ
				int		i;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case 4:
			{
				// ㅁ ㅁ
				// ㅁ ㅁ
				int		i, j;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W - USEINFO_TARGET_TERM_X/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < 2; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}

				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;
				for(j = 0; i < m_nTargetNum; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case 5:
			{
				//   ㅁ
				// ㅁ
				//   ㅁ 
				// ㅁ
				//   ㅁ
				int		i, j;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W - USEINFO_TARGET_TERM_X/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < 2; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}

				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;
				for(j = 0; i < m_nTargetNum; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case 6:
			{
				// ㅁ ㅁ
				// ㅁ ㅁ
				// ㅁ ㅁ
				int		i, j;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W - USEINFO_TARGET_TERM_X/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;

				for(i = 0; i < 3; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}

				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;
				for(j = 0; i < m_nTargetNum; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case 7:
			{
				//       ㅁ
				// ㅁ ㅁ
				//       ㅁ
				// ㅁ ㅁ
				//       ㅁ
				int		i, j;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W - USEINFO_TARGET_TERM_X/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < 2; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}

				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;
				for(j = 0; i < 4; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;
				for(j = 0; i < m_nTargetNum; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case 8:
			{
				//    ㅁ ㅁ
				// ㅁ 
				//    ㅁ ㅁ 
				// ㅁ
				//    ㅁ ㅁ
				int		i, j;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W - USEINFO_TARGET_TERM_X/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < 2; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;

				for(j = 0; i < 5; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;
				for(j = 0; i < m_nTargetNum; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
	}
}

void gUIGame::pk_infochange_rep(PK_INFOCHANGE_REP *rep)
{
	int		i;
	int		nCount = 0;
	
	bool	bBuff = false;
	bool	bDeBuff = false;
	bool	bClass = false;
	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strlen(rep->info[i].szID) == 0)
			continue;

		m_info[nCount] = rep->info[i];
		if(m_info[nCount].nGrade)
			bClass = true;
		if(m_info[nCount].nLang != 0)
		{
			if(m_info[nCount].nLang > 0)
				bBuff = true;
			else
				bDeBuff = true;
		}
		if(m_info[nCount].nMath != 0)
		{
			if(m_info[nCount].nMath > 0)
				bBuff = true;
			else
				bDeBuff = true;
		}
		if(m_info[nCount].nArt != 0)
		{
			if(m_info[nCount].nArt > 0)
				bBuff = true;
			else
				bDeBuff = true;
		}
		if(m_info[nCount].nStamina != 0)
		{
			if(m_info[nCount].nStamina > 0)
				bBuff = true;
			else
				bDeBuff = true;
		}

		nCount++;
	}
	m_uimode = UIM_INFOCHANGE;
	m_timer.frameStart(INFOCHANGE_TICK, 2);
	m_nTargetNum = nCount;
	SetTargetButton_InfoChange();

	gPlaySoundCore	*sound = gPlaySoundCore::GetIF();
	if(bClass)
		sound->PlayEffectSound(EFFECT_FILE_4);
	else if(bBuff)
		sound->PlayEffectSound(EFFECT_FILE_0);
	else if(bDeBuff)
		sound->PlayEffectSound(EFFECT_FILE_5);
}

void gUIGame::SetTargetButton_InfoChange()
{
	gPlayerContainer	*pc = gPlayerContainer::GetIF();

	int		i;

	for(i = 0; i < m_nTargetNum; i++)
	{
		m_target[i].idx		= pc->GetGPIndex(m_info[i].szID);
		m_target[i].img		= &pc->m_ImgInfo[ pc->m_GPlayerList[ m_target[i].idx ].ctype ].ImgPic;
	}

	switch(m_nTargetNum)
	{
		case 1:
			{
				//	ㅁ
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)/2;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H/2;

				SetRect(&m_target[0].rcPos,
					startx, starty,
					startx + TARGET_OUTLINE_SIZE_W,
					starty + TARGET_OUTLINE_SIZE_H );
			}
			break;
		case 2:
			{
				// ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W) - INFOCHANGE_TERM_X/2;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H/2;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
		case 3:
			{
				// ㅁ ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*3/2 - INFOCHANGE_TERM_X;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H/2;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
		case 4:
			{
				// ㅁ ㅁ ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*2 - INFOCHANGE_TERM_X/2;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H/2;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
		case 5:
			{
				//  ㅁ ㅁ
				// ㅁ ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W) - INFOCHANGE_TERM_X/2;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H - INFOCHANGE_TERM_Y/2;

				for(i = 0; i < 2; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}

				startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*3/2 - INFOCHANGE_TERM_X;
				starty += (TARGET_OUTLINE_SIZE_H + INFOCHANGE_TERM_Y);

				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + (i - 2) * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + (i - 2) * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
		case 6:
			{
				// ㅁ ㅁ ㅁ
				// ㅁ ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*3/2 - INFOCHANGE_TERM_X;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H - INFOCHANGE_TERM_Y/2;

				for(i = 0; i < 3; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}

				startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*3/2 - INFOCHANGE_TERM_X;
				starty += (TARGET_OUTLINE_SIZE_H + INFOCHANGE_TERM_Y);

				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + (i - 3) * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + (i - 3) * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
		case 7:
			{
				//  ㅁ ㅁ ㅁ
				// ㅁ ㅁ ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*3/2 - INFOCHANGE_TERM_X;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H - INFOCHANGE_TERM_Y/2;

				for(i = 0; i < 3; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}

				startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*2 - INFOCHANGE_TERM_X/2;
				starty += (TARGET_OUTLINE_SIZE_H + INFOCHANGE_TERM_Y);

				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
		case 8:
			{
				// ㅁ ㅁ ㅁ ㅁ
				// ㅁ ㅁ ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*2 - INFOCHANGE_TERM_X/2;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H - INFOCHANGE_TERM_Y/2;

				for(i = 0; i < 4; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}

				startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*2 - INFOCHANGE_TERM_X/2;
				starty += (TARGET_OUTLINE_SIZE_H + INFOCHANGE_TERM_Y);

				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
	}
}

#ifdef UI_ICON_DRAW
const char *CharToIcon[8] = {"애정도", "체력", "수업", "언어", "수리", "예술", "+", "-"};
#endif

void gUIGame::Draw_InfoChange()
{
	DrawTargetButton();

	int		i, j;
	int		nCount;		// change info갯수

	char	szBuf[5][64];

	gUtil::BeginText();
	for(i = 0; i < m_nTargetNum; i++)
	{
		nCount = 0;
		if(m_info[i].nGrade != 0)
		{
			if(m_info[i].nGrade > 0)
				wsprintf(szBuf[nCount], "수업 + %d", m_info[i].nGrade);
			else
				wsprintf(szBuf[nCount], "수업 - %d", -m_info[i].nGrade);
			nCount++;
		}
		if(m_info[i].nLang != 0)
		{
			if(m_info[i].nLang > 0)
				wsprintf(szBuf[nCount], "언어 + %d", m_info[i].nLang);
			else
				wsprintf(szBuf[nCount], "언어 - %d", -m_info[i].nLang);
			nCount++;
		}
		if(m_info[i].nMath != 0)
		{
			if(m_info[i].nMath > 0)
				wsprintf(szBuf[nCount], "수리 + %d", m_info[i].nMath);
			else
				wsprintf(szBuf[nCount], "수리 - %d", -m_info[i].nMath);
			nCount++;
		}
		if(m_info[i].nArt != 0)
		{
			if(m_info[i].nArt > 0)
				wsprintf(szBuf[nCount], "예술 + %d", m_info[i].nArt);
			else
				wsprintf(szBuf[nCount], "예술 - %d", -m_info[i].nArt);
			nCount++;
		}
		if(m_info[i].nStamina != 0)
		{
			if(m_info[i].nStamina > 0)
				wsprintf(szBuf[nCount], "체력 + %d", m_info[i].nStamina);
			else
				wsprintf(szBuf[nCount], "체력 - %d", -m_info[i].nStamina);
			nCount++;
		}
		if(m_info[i].nLove != 0)
		{
			if(m_info[i].nLove > 0)
				wsprintf(szBuf[nCount], "애정도 + %d", m_info[i].nLove);
			else
				wsprintf(szBuf[nCount], "애정도 - %d", -m_info[i].nLove);
			nCount++;
		}


		int		startx, starty;

		startx = m_target[i].rcPos.right + 10;
		starty = m_target[i].rcPos.top + TARGET_OUTLINE_SIZE_H/2
					- INFOCHANGE_INFOSIZE_H * nCount/2 - INFOCHANGE_INFOTERM_Y * (nCount - 1)/2;

		//2010.12.25 체력 및 애정도 등등 표시 UI 교체 작업 착수
#ifdef UI_ICON_DRAW
		int k=0;
		RECT rcSour, rcDest;
		while(k<nCount) {
			for(j=0;j<8;j++)
				if(strstr(szBuf[k], CharToIcon[j]) != NULL) {
					SetRect(&rcDest, startx, starty, 
						startx+m_ImgUI[UIIMG_ICON].m_nWidth/8, starty+m_ImgUI[UIIMG_ICON].m_nHeight);
					SetRect(&rcSour, j*m_ImgUI[UIIMG_ICON].m_nWidth/8, 0, (j+1)*m_ImgUI[UIIMG_ICON].m_nWidth/8, m_ImgUI[UIIMG_ICON].m_nHeight);
					m_ImgUI[UIIMG_ICON].Draw(rcDest, rcSour);

					SetRect(&rcDest, startx+m_ImgUI[UIIMG_ICON].m_nWidth/8, starty, 
						startx+m_ImgUI[UIIMG_ICON].m_nWidth/4, starty+m_ImgUI[UIIMG_ICON].m_nHeight);

					if(strchr(szBuf[k], '+'))
						SetRect(&rcSour, 6*m_ImgUI[UIIMG_ICON].m_nWidth/8, 0, 7*m_ImgUI[UIIMG_ICON].m_nWidth/8, m_ImgUI[UIIMG_ICON].m_nHeight);
					else
						SetRect(&rcSour, 7*m_ImgUI[UIIMG_ICON].m_nWidth/8, 0, 8*m_ImgUI[UIIMG_ICON].m_nWidth/8, m_ImgUI[UIIMG_ICON].m_nHeight);
					m_ImgUI[UIIMG_ICON].Draw(rcDest, rcSour);


					int l = 0, len=strlen(szBuf[k]), c = 0, sx = startx+m_ImgUI[UIIMG_ICON].m_nWidth/4+2;
					while(szBuf[k][l]<48 || szBuf[k][l]>57) l++;
					while(l<len) {
						int n=szBuf[k][l] - 48;

						SetRect(&rcDest, sx+c*m_ImgUI[UIIMG_NUMBER].m_nWidth/10, starty, 
							sx+(c+1)*m_ImgUI[UIIMG_NUMBER].m_nWidth/10, starty+m_ImgUI[UIIMG_NUMBER].m_nHeight);
						SetRect(&rcSour, n*m_ImgUI[UIIMG_NUMBER].m_nWidth/10, 0, (n+1)*m_ImgUI[UIIMG_NUMBER].m_nWidth/10, m_ImgUI[UIIMG_NUMBER].m_nHeight);
						
						m_ImgUI[UIIMG_NUMBER].Draw(rcDest,rcSour);
						l++; c++;
					}
					break;
				}
			k++; starty += m_ImgUI[UIIMG_ICON].m_nHeight+2;
		}
#else
		//요기서 완료. 2010.12.25.
		for(j = 0; j < nCount; j++)
		{
			gUtil::TextOutLine(startx, starty + j * (INFOCHANGE_INFOSIZE_H + INFOCHANGE_INFOTERM_Y), szBuf[j]);
		}
#endif
	}
	gUtil::EndText();
}

void gUIGame::SetbCouple(bool mode)
{
	gPlayerContainer	*pc = gPlayerContainer::GetIF();

	m_bCouple = mode;
	if(m_bCouple == false) {
		int i = pc->GetMyGPIndex();
		memset(pc->m_GPlayerList[i].szCouple, 0, sizeof(char)*IDLENGTH);
		memset(pc->m_MyGamePlayer.szCouple, 0, sizeof(char)*IDLENGTH);
	}
}

void gUIGame::pk_becouple_rep(PK_BECOUPLE_REP *rep)
{
	gPlayerContainer	*pc = gPlayerContainer::GetIF();
	gPlaySoundCore		*sound = gPlaySoundCore::GetIF();

	m_nTargetNum = 2;

	m_target[0].idx = pc->GetGPIndex(rep->szFeMale);
	m_target[0].img = &pc->m_ImgInfo[ pc->m_GPlayerList[m_target[0].idx].ctype ].ImgPic;
	SetRect(&m_target[0].rcPos,
			BECOUPLE_FEMALE_X,
			BECOUPLE_FEMALE_Y,
			BECOUPLE_FEMALE_X + INFOCHANGE_INFOSIZE_W + TARGET_OUTLINE_SIZE_W,
			BECOUPLE_FEMALE_Y + INFOCHANGE_INFOSIZE_H + TARGET_OUTLINE_SIZE_H );

	m_target[1].idx = pc->GetGPIndex(rep->szMale);
	m_target[1].img = &pc->m_ImgInfo[ pc->m_GPlayerList[m_target[1].idx].ctype ].ImgPic;
	SetRect(&m_target[1].rcPos,
		BECOUPLE_MALE_X,
		BECOUPLE_MALE_Y,
		BECOUPLE_MALE_X + INFOCHANGE_INFOSIZE_W + TARGET_OUTLINE_SIZE_W,
		BECOUPLE_MALE_Y + INFOCHANGE_INFOSIZE_H + TARGET_OUTLINE_SIZE_H );

	m_timer.frameStart(BECOUPLE_TICK, 2);
	m_uimode = UIM_BECOUPLE;

	int Me = pc->GetMyGPIndex();
	if(Me==m_target[0].idx || Me==m_target[1].idx)
	{
		m_bCouple = rep->bCouple;
		if(rep->bCouple)
		{
			sound->StartBGM(BGM_FILE_4);
		}
		else
		{
			gGameCore::GetIF()->m_bBreak = true;
			gGameCore::GetIF()->m_nCoupleDebuffRemain = COUPLE_DEBUFFTURN;
			sound->StartBGM(BGM_FILE_3);
		}
	}
}

void gUIGame::Clear()
{
	m_uimode = UIM_NONE;
	SetRankList();
	m_bCouple = false;
	m_bShowYourTurn = false;
	m_bShowTimeCount = true;
	m_bItemUsed = false;
}

void gUIGame::GameEnd()
{
	m_bShowTimeCount = false;
	gPlaySoundCore::GetIF()->StopEffectSound(EFFECT_FILE_10);
	m_uimode = UIM_RESULT;
	m_timer.frameStart(RESULT_SHOWTIME, 2);
}

void gUIGame::DrawTimerImage(int n)
{
	RECT	rcDest, rcSour;
	SetRect(&rcDest,
		TIMER_NUMBER_POS_X,
		TIMER_NUMBER_POS_Y,
		TIMER_NUMBER_POS_X + TIMER_NUMBER_SIZE_W,
		TIMER_NUMBER_POS_Y + TIMER_NUMBER_SIZE_H);
	SetRect(&rcSour,
		0, 0, TIMER_NUMBER_SIZE_W, TIMER_NUMBER_SIZE_H);

	OffsetRect(&rcSour, (n * TIMER_NUMBER_SIZE_W), 0);
	m_ImgUI[UIIMG_TIMER].Draw(rcDest, rcSour);
}