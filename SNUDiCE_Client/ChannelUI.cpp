#include "ChannelUI.h"
#include "PlayerContainer.h"
#include "Util.h"
#include "Server.h"

gChannelUI::gChannelUI(void)
{
}

gChannelUI::~gChannelUI(void)
{
}

bool gChannelUI::SetUp()
{
	if(!m_ImgBack.Load(CH_FILE_BACK))
		return false;

	SetRect(&m_rcPos,
			CH_POS_X,
			CH_POS_Y,
			CH_POS_X + CH_SIZE_W,
			CH_POS_Y + CH_SIZE_H);

	RECT	btnPos;

	/*
	SetRect(&btnPos,
			CH_BTN_CHANNEL_POS_X,
			CH_BTN_CHANNEL_POS_Y,
			CH_BTN_CHANNEL_POS_X + CH_SIZE_MODEBTNW,
			CH_BTN_CHANNEL_POS_Y + CH_SIZE_MODEBTNH);
	OffsetRect(&btnPos, m_rcPos.left, m_rcPos.top);
	m_BtnMode[CM_CHANNEL].SetUp(CH_BTN_FILE_CHANNEL, false, btnPos);

	SetRect(&btnPos,
		CH_BTN_FRIEND_POS_X,
		CH_BTN_FRIEND_POS_Y,
		CH_BTN_FRIEND_POS_X + CH_SIZE_MODEBTNW,
		CH_BTN_FRIEND_POS_Y + CH_SIZE_MODEBTNH);
	OffsetRect(&btnPos, m_rcPos.left, m_rcPos.top);
	m_BtnMode[CM_FRIEND].SetUp(CH_BTN_FILE_FRIEND, false, btnPos);

	SetRect(&btnPos,
		CH_BTN_CLAN_POS_X,
		CH_BTN_CLAN_POS_Y,
		CH_BTN_CLAN_POS_X + CH_SIZE_MODEBTNW,
		CH_BTN_CLAN_POS_Y + CH_SIZE_MODEBTNH);
	OffsetRect(&btnPos, m_rcPos.left, m_rcPos.top);
	m_BtnMode[CM_CLAN].SetUp(CH_BTN_FILE_CLAN, false, btnPos);
	*/
	
	m_eChannel = CM_CHANNEL;
	m_BtnMode[m_eChannel].m_eBtnMode = EBM_CLICK;

	if(!m_ImgChName.Load(CH_FILE_CHNAME))
		return false;

	SetRect(&btnPos,
		CH_BTN_POS_CHCHANGEX,
		CH_BTN_POS_CHCHANGEY,
		CH_BTN_POS_CHCHANGEX + CH_BTN_SIZE_CHCHANGEW, 
		CH_BTN_POS_CHCHANGEY + CH_BTN_SIZE_CHCHANGEH );
	OffsetRect(&btnPos, m_rcPos.left, m_rcPos.top);
	if(!m_BtnChChange[CCB_CHANGE].SetUp(CH_FILE_CHCHANGE, false, btnPos))
		return false;

	SetRect(&btnPos,
		CH_BTN_POS_CHNAMEX,
		CH_BTN_POS_CHNAMEY,
		CH_BTN_POS_CHNAMEX + CH_BTN_SIZE_CHNAMEW,
		CH_BTN_POS_CHNAMEY + CH_BTN_SIZE_CHNAMEH );
	OffsetRect(&btnPos, m_rcPos.left, m_rcPos.top);
	if(!m_BtnChChange[CCB_CH1].SetUp(CH_BTN_FILE_CH1, false, btnPos))
		return false;

	OffsetRect(&btnPos, 0, CH_BTN_CHNAME_YTERM);
	if(!m_BtnChChange[CCB_CH2].SetUp(CH_BTN_FILE_CH2, false, btnPos))
		return false;

	OffsetRect(&btnPos, 0, CH_BTN_CHNAME_YTERM);
	if(!m_BtnChChange[CCB_CH3].SetUp(CH_BTN_FILE_CH3, false, btnPos))
		return false;

	OffsetRect(&btnPos, 0, CH_BTN_CHNAME_YTERM);
	if(!m_BtnChChange[CCB_CH4].SetUp(CH_BTN_FILE_CH4, false, btnPos))
		return false;

	OffsetRect(&btnPos, 0, CH_BTN_CHNAME_YTERM);
	if(!m_BtnChChange[CCB_CH5].SetUp(CH_BTN_FILE_CH5, false, btnPos))
		return false;

	OffsetRect(&btnPos, 0, CH_BTN_CHNAME_YTERM);
	if(!m_BtnChChange[CCB_CH6].SetUp(CH_BTN_FILE_CH6, false, btnPos))
		return false;

	return true;
}

void gChannelUI::Draw()
{
	switch(m_eChannel)
	{
		case CM_CHANNEL:
			DrawChannel();
		break;
		case CM_CHANNELCHANGE:
			DrawChannelChange();
		break;
	}
}

void gChannelUI::DrawChannel()
{
	int		i;

	m_ImgBack.Draw(m_rcPos.left, m_rcPos.top);

	//for(i = 0; i < CM_END; i++)
	//	m_BtnMode[i].Draw();

	m_BtnChChange[CCB_CHANGE].Draw();

	RECT	rcSour, rcDest;

	SetRect(&rcSour,
		0, 0, CH_SIZE_CHNAMEW, CH_SIZE_CHNAMEH);

	CHANNEL		*channel = &gPlayerContainer::GetIF()->m_MyChannel;

	int		channelnum = channel->nChannelNum;

	OffsetRect(&rcSour, 0, CH_SIZE_CHNAMEH * (channelnum - 1));

	SetRect(&rcDest,
		CH_POS_CHNAMEX,
		CH_POS_CHNAMEY,
		CH_POS_CHNAMEX + CH_SIZE_CHNAMEW,
		CH_POS_CHNAMEY + CH_SIZE_CHNAMEH );
	OffsetRect(&rcDest, m_rcPos.left, m_rcPos.top);

	m_ImgChName.Draw(rcDest, rcSour, false);

	m_BtnChChange[CCB_CHANGE].Draw();

	gUtil::BeginText();
	for(i = 0; i < channel->nUserNum; i++)
	{
		gUtil::Text(m_rcPos.left + CH_POS_PLAYERNAMEX,
			m_rcPos.top + CH_POS_PLAYERNAMEY + CH_POS_PLAYERNAMETERM * i, channel->szUserInCh[i]);
	}
	gUtil::EndText();
}

void gChannelUI::DrawChannelChange()
{
	m_ImgBack.Draw(m_rcPos.left, m_rcPos.top);

	RECT	rcSour, rcDest;

	SetRect(&rcSour,
		0, 0, CH_SIZE_CHNAMEW, CH_SIZE_CHNAMEH);

	CHANNEL		*channel = &gPlayerContainer::GetIF()->m_MyChannel;

	int		channelnum = channel->nChannelNum;

	OffsetRect(&rcSour, 0, CH_SIZE_CHNAMEH * (channelnum - 1));

	SetRect(&rcDest,
		CH_POS_CHNAMEX,
		CH_POS_CHNAMEY,
		CH_POS_CHNAMEX + CH_SIZE_CHNAMEW,
		CH_POS_CHNAMEY + CH_SIZE_CHNAMEH );
	OffsetRect(&rcDest, m_rcPos.left, m_rcPos.top);

	m_ImgChName.Draw(rcDest, rcSour, false);

	m_BtnChChange[CCB_CHANGE].Draw();

	int		i;

	for(i = 0; i < CM_END; i++)
		m_BtnMode[i].Draw();

	for(i = CCB_CANCEL; i < CCB_END; i++)
		m_BtnChChange[i].Draw();
}

void gChannelUI::Release()
{
	m_ImgBack.Release();
	m_ImgChName.Release();

	int		i;
	
	for(i = 0; i < CM_END; i++)
		m_BtnMode[i].Release();

	for(i = 0; i < CCB_END; i++)
		m_BtnChChange[i].Release();
}

bool gChannelUI::isPointInUI(int x, int y)
{
	return gUtil::PointInRect(x, y, m_rcPos);
}

void gChannelUI::OnLButtonDown(int x, int y)
{
	int			i;

	for(i = 0; i < CM_END; i++)
	{
		if(m_BtnMode[i].PointInButton(x, y))
		{
			m_eChannel = (CHANNELMODE)i;
			m_BtnMode[i].m_eBtnMode = EBM_CLICK;
			OnMouseMove(x, y);
			return;
		}
	}

	switch(m_eChannel)
	{
		case CM_CHANNEL:
			{
				if(m_BtnChChange[CCB_CHANGE].PointInButton(x, y))
					m_eChannel = CM_CHANNELCHANGE;
			}
		break;
		case CM_CHANNELCHANGE:
			{
				if(m_BtnChChange[CCB_CANCEL].PointInButton(x, y))
					m_eChannel = CM_CHANNEL;

				for(i = CCB_CH1; i < CCB_END; i++)
				{
					if(m_BtnChChange[i].PointInButton(x, y))
					{
						PK_CHANNELCHANGE_ASK		ask;

						ask.nChannel	= i - CCB_CH1 + 1;
						strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyPlayer.szID);
						gServer::GetIF()->Send(PL_CHANNELCHANGE_ASK, sizeof(ask), &ask);
						return;
					}
				}
			}
		break;
	}
}

void gChannelUI::OnLButtonUp(int x, int y)
{

}

void gChannelUI::OnMouseMove(int x, int y)
{
	int		i;

	switch(m_eChannel)
	{
		case CM_CHANNEL:
			{
				for(i = 0; i < CM_END; i++)
				{
					if(i == CM_CHANNEL)
						continue;

					if(m_BtnMode[i].PointInButton(x, y))
						m_BtnMode[i].m_eBtnMode = EBM_HOVER;
					else
						m_BtnMode[i].m_eBtnMode	= EBM_NONE;
				}

				if(m_BtnChChange[CCB_CHANGE].PointInButton(x, y))
					m_BtnChChange[CCB_CHANGE].m_eBtnMode = EBM_HOVER;
				else
					m_BtnChChange[CCB_CHANGE].m_eBtnMode = EBM_NONE;

			}
		break;
		case CM_CHANNELCHANGE:
			{
				for(i = 0; i < CM_END; i++)
				{
					if(i == CM_CHANNEL)
						continue;

					if(m_BtnMode[i].PointInButton(x, y))
						m_BtnMode[i].m_eBtnMode = EBM_HOVER;
					else
						m_BtnMode[i].m_eBtnMode	= EBM_NONE;
				}

				for(i = CCB_CANCEL; i < CCB_END; i++)
				{
					if(m_BtnChChange[i].PointInButton(x, y))
						m_BtnChChange[i].m_eBtnMode = EBM_HOVER;
					else
						m_BtnChChange[i].m_eBtnMode = EBM_NONE;
				}
			}
			break;
	}
}

void gChannelUI::OnRButtonDown(int x, int y)
{

}
