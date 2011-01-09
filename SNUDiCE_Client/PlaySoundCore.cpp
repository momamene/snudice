#include "PlaySoundCore.h"
#include "fmod.h"
#include <windows.h>
#include "MainWin.h"

#define TRUE 1
#define FALSE 0
#define NULL 0

#define REG_DIRECTORY	"SOFTWARE\\Project N\\SNUDiCE"

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
	if(!gMainWin::GetIF()->m_bActive)
		return;

	if(this->bgmState == BGM_PLAYING || this->bgmState == BGM_PAUSED)
		StopBGM();
	
	this->bgmStream=FSOUND_Stream_Open(filename,FSOUND_LOOP_NORMAL, 0, 0);
	if (this->bgmStream!=NULL) {
		this->bgmChannel=FSOUND_Stream_Play(FSOUND_FREE, this->bgmStream);		
		// 새로 생성되는 채널은 항상 최대 볼륨이므로 강제로 맞춰줘야 함
		FSOUND_SetVolume(this->bgmChannel,this->m_nBGM);		

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
	if(this->bgmState != BGM_PLAYING && this->bgmState!=BGM_PAUSED)
		return;

	FSOUND_Stream_Stop(bgmStream);
	FSOUND_Stream_Close(bgmStream);
	bgmStream = NULL;
	this->bgmState = BGM_NOT_LOADED;
}

void gPlaySoundCore::PlayEffectSound(const char* filename, bool bRepeat)
{
	if(!gMainWin::GetIF()->m_bActive)
		return;

	FSOUND_STREAM *effectSoundStream;
	if(bRepeat)
	{
		effectSoundStream = FSOUND_Stream_Open(filename,FSOUND_LOOP_NORMAL,0,0);
		PAIR_SOUND		add;
		strcpy(add.szFileName, filename);
		add.pStream = effectSoundStream;

		// 이미 반복재생하려는 사운드가 목록에 있으면 return
		vector<PAIR_SOUND>::iterator		it;
		for(it = m_vSoundList.begin(); it != m_vSoundList.end(); it++)
			if(strcmp(it->szFileName, filename) == 0)
				return;

		m_vSoundList.push_back(add);
	}
	else
		effectSoundStream = FSOUND_Stream_Open(filename,FSOUND_NORMAL,0,0);

	if(!effectSoundStream)
		return;
	int effectSoundChannel = FSOUND_Stream_Play(FSOUND_FREE,effectSoundStream);
	FSOUND_SetVolume(effectSoundChannel,this->effectSoundVolume);
	if(!bRepeat)
		FSOUND_Stream_SetEndCallback(effectSoundStream,&gPlaySoundCore::disposeEffectSoundStream,NULL);
}

void gPlaySoundCore::StopEffectSound(const char* filename)
{
	vector<PAIR_SOUND>::iterator		it;

	for(it = m_vSoundList.begin(); it != m_vSoundList.end(); it++)
	{
		if(strcmp(it->szFileName, filename) == 0)
		{
			FSOUND_Stream_Stop(it->pStream);
			FSOUND_Stream_Close(it->pStream);
			m_vSoundList.erase(it);
			return;
		}
	}
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


bool gPlaySoundCore::SetUp()
{
	HKEY			key;
	DWORD			dwDisp;
	DWORD			dwSize;

	m_nBGM = VOLUME_MAX / 2;
	m_nEffect = VOLUME_MAX / 2;

	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, REG_DIRECTORY, 0, NULL,
		REG_OPTION_VOLATILE, KEY_READ, NULL, &key, &dwDisp) != ERROR_SUCCESS)
		return false;

	dwSize = sizeof(int);
	if(RegQueryValueEx(key, "bgm", 0, NULL, (LPBYTE)&m_nBGM, &dwSize) == ERROR_SUCCESS)
		RegCloseKey(key);
	else
	{
		RegCloseKey(key);

		if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, REG_DIRECTORY, 0, NULL,
			REG_OPTION_VOLATILE, KEY_WRITE, NULL, &key, &dwDisp) == ERROR_SUCCESS)
		{
			RegSetValueEx(key, "bgm", 0, REG_DWORD, (LPBYTE)&m_nBGM, sizeof(int));
		}
		RegCloseKey(key);
	}

	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, REG_DIRECTORY, 0, NULL,
		REG_OPTION_VOLATILE, KEY_READ, NULL, &key, &dwDisp) != ERROR_SUCCESS)
		return false;

	dwSize = sizeof(int);
	if(RegQueryValueEx(key, "effect", 0, NULL, (LPBYTE)&m_nEffect, &dwSize) == ERROR_SUCCESS)
		RegCloseKey(key);
	else
	{
		RegCloseKey(key);

		if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, REG_DIRECTORY, 0, NULL,
			REG_OPTION_VOLATILE, KEY_WRITE, NULL, &key, &dwDisp) == ERROR_SUCCESS)
		{
			RegSetValueEx(key, "effect", 0, REG_DWORD, (LPBYTE)&m_nEffect, sizeof(int));
		}
		RegCloseKey(key);
	}

	setBGMVolume(m_nBGM);
	setBGMVolume(m_nEffect);

	return true;
}

void gPlaySoundCore::Release()
{
	HKEY		key;
	DWORD		dwDisp;

	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, REG_DIRECTORY, 0, NULL,
		REG_OPTION_VOLATILE, KEY_WRITE, NULL, &key, &dwDisp) != ERROR_SUCCESS)
		return;
	if(RegSetValueEx(key, "bgm", 0, REG_DWORD, (LPBYTE)&m_nBGM, sizeof(int)) != ERROR_SUCCESS)
		return;
	RegCloseKey(key);

	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, REG_DIRECTORY, 0, NULL,
		REG_OPTION_VOLATILE, KEY_WRITE, NULL, &key, &dwDisp) != ERROR_SUCCESS)
		return;
	if(RegSetValueEx(key, "effect", 0, REG_DWORD, (LPBYTE)&m_nEffect, sizeof(int)) != ERROR_SUCCESS)
		return;
	RegCloseKey(key);
}