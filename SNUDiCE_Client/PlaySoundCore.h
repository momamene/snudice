#pragma once
#include "Core.h"
#include "fmod.h"



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
	
	virtual ~gPlaySoundCore();

public:
	gPlaySoundCore();

	bool isBGMLoaded();
	void StartBGM(const char* filename);
	void PauseBGM();
	void ResumeBGM();
	void StopBGM();
	void PlayEffectSound(const char* filename);	

private:
	FSOUND_STREAM *bgmStream;	
	int channel,Volume;
	SOUNDSTATE bgmState;

private:
	static signed char F_CALLBACKAPI disposeEffectSoundStream(FSOUND_STREAM *stream,void *buff,int len,void *userdata);
};