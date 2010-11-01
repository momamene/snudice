#include "PlaySoundCore.h"
#include "fmod.h"

#define TRUE 1
#define FALSE 0
#define NULL 0

static gPlaySoundCore s_PlaySoundCore;

gPlaySoundCore *gPlaySoundCore::GetIF()
{
	return &s_PlaySoundCore;
}

gPlaySoundCore::gPlaySoundCore() 
{
	this->bgmVolume = 100;
	this->bgmStream = NULL;	
	this->bgmState = BGM_NOT_LOADED;
	this->effectSoundVolume = 100;

	FSOUND_Init(44100,32,0);
	FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(),TRUE);		
}

gPlaySoundCore::~gPlaySoundCore() {}

bool gPlaySoundCore::isBGMLoaded()
{
	return (this->bgmState!=BGM_NOT_LOADED);
}

void gPlaySoundCore::StartBGM(const char* filename)
{
	this->bgmStream=FSOUND_Stream_Open(filename,FSOUND_LOOP_NORMAL, 0, 0);
	if (this->bgmStream!=NULL) {
		this->bgmChannel=FSOUND_Stream_Play(FSOUND_FREE, this->bgmStream);		
		// 새로 생성되는 채널은 항상 최대 볼륨이므로 강제로 맞춰줘야 함
		FSOUND_SetVolume(this->bgmChannel,this->bgmVolume);		

		this->bgmState = BGM_PLAYING;
	}	
}
void gPlaySoundCore::PauseBGM()
{
	if(this->bgmState!=BGM_PLAYING)
		return;

	FSOUND_SetPaused(bgmChannel,TRUE);
	this->bgmState = BGM_PAUSED;
}
void gPlaySoundCore::ResumeBGM()
{
	if(this->bgmState!=BGM_PAUSED)
		return;

	FSOUND_SetPaused(bgmChannel,FALSE);
	this->bgmState = BGM_PLAYING;
}
void gPlaySoundCore::StopBGM()
{
	if(this->bgmState!=BGM_PLAYING || this->bgmState!=BGM_PAUSED)
		return;

	FSOUND_Stream_Stop(bgmStream);
	FSOUND_Stream_Close(bgmStream);
	bgmStream = NULL;
	this->bgmState = BGM_NOT_LOADED;
}

void gPlaySoundCore::PlayEffectSound(const char* filename)
{
	FSOUND_STREAM *effectSoundStream = FSOUND_Stream_Open(filename,FSOUND_NORMAL,0,0);
	int effectSoundChannel = FSOUND_Stream_Play(FSOUND_FREE,effectSoundStream);
	FSOUND_SetVolume(effectSoundChannel,this->effectSoundVolume);
	FSOUND_Stream_SetEndCallback(effectSoundStream,&gPlaySoundCore::disposeEffectSoundStream,NULL);
}


signed char F_CALLBACKAPI gPlaySoundCore::disposeEffectSoundStream(FSOUND_STREAM *stream, void *buff, int len, void *userdata)
{
	FSOUND_Stream_Stop(stream);
	FSOUND_Stream_Close(stream);

	return 0;
}

int gPlaySoundCore::getBGMVolume()
{
	return this->bgmVolume;
}
void gPlaySoundCore::setBGMVolume(int newBGMVolume)
{
	this->bgmVolume = newBGMVolume;
	FSOUND_SetVolume(this->bgmChannel,this->bgmVolume);
}
int gPlaySoundCore::getEffectSoundVolume()
{
	return this->effectSoundVolume;
}
//effect sound 의 바뀐 음량은 다음 effect sound play 때부터 적용된다.
void gPlaySoundCore::setEffectSoundVolume(int newEffectSoundVolume)
{
	this->effectSoundVolume = newEffectSoundVolume;
}
