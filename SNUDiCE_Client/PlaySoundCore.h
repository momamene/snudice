#pragma once
#include "fmod.h"
#include "SoundFiles.h"
#include <vector>

using namespace std;

#define VOLUME_MAX	200

struct PAIR_SOUND
{
	char			szFileName[256];
	FSOUND_STREAM*	pStream;
};

class gPlaySoundCore
{
	enum SOUNDSTATE
	{
		BGM_NOT_LOADED,
		BGM_PLAYING,
		BGM_PAUSED,
	};

public:
	static gPlaySoundCore *GetIF();
	
	gPlaySoundCore();
	virtual ~gPlaySoundCore();
	
public:
	int		m_nBGM;
	int		m_nEffect;
	bool	m_bFull;

	int		m_nTempBGM;
	int		m_nTempEffect;
	bool	m_bTempFull;

public:
	bool	SetUp();
	void	Release();

	bool	isBGMLoaded();

	void	StartBGM(const char* filename);
	void	PauseBGM();
	void	ResumeBGM();
	void	StopBGM();
	void	PlayEffectSound(const char* filename, bool bRepeat = false);
	void	StopEffectSound(const char* filename);

	int		getBGMVolume();
	void	setBGMVolume(int newBGMVolume);
	int		getEffectSoundVolume();
	void	setEffectSoundVolume(int newEffectSoundVolume);

private:
	vector<PAIR_SOUND>	m_vSoundList;

	FSOUND_STREAM	*bgmStream;	
	int				bgmChannel;
	int				bgmVolume;
	SOUNDSTATE		bgmState;
	int				effectSoundVolume;

private:
	static signed char F_CALLBACKAPI disposeEffectSoundStream(FSOUND_STREAM *stream,void *buff,int len,void *userdata);
};