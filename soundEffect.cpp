#include<Windows.h>
#include<fmod.h>

#define _C 1046.502
#define _D 1108.731
#define _E 1318.510
#define _F 1396.913
#define _G 1567.982
#define _A 1760.000
#define _B 1975.533

#define BGM_KALINKA "Kalinka.wav"
#define BGM_TROIKA "Troika.wav"
#define BGM_LOGINSKA "Loginska.wav"

#define BLOCK_DOWN "block_down.wav"
#define BLOCK_REMOVE "block_remove.wav"


FMOD_SYSTEM *g_System;
FMOD_SOUND *sound[5];
FMOD_CHANNEL *bgmChannel;

FMOD_CHANNELGROUP *channelGroup;

int index = 2;

void InitSound(void)
{
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(g_System, BLOCK_DOWN, FMOD_DEFAULT, 0, &sound[0]);
	FMOD_System_CreateSound(g_System, BLOCK_REMOVE, FMOD_DEFAULT, 0, &sound[1]);

	FMOD_System_CreateSound(g_System, BGM_KALINKA, FMOD_DEFAULT, 0, &sound[2]);
	FMOD_System_CreateSound(g_System, BGM_TROIKA, FMOD_DEFAULT, 0, &sound[3]);
	FMOD_System_CreateSound(g_System, BGM_LOGINSKA, FMOD_DEFAULT, 0, &sound[4]);
	//FMOD_System_CreateSound(g_System, BGM_LOGINSKA, FMOD_LOOP_NORMAL, 0, &sound[4]);

	FMOD_System_CreateChannelGroup(g_System, "bgm", &channelGroup);
}

void PlayBGM(void)
{
	FMOD_System_PlaySound(g_System, sound[index], channelGroup, 0, &bgmChannel);
	index++;
	if (index >= 5)
	{
		index = 2;
	}
}

void StopBGM(void)
{
	FMOD_Channel_Stop(bgmChannel);
}

void UpdateSound(void)
{
	FMOD_BOOL isPlaying;
	FMOD_Channel_IsPlaying(bgmChannel, &isPlaying);
	if (isPlaying)
	{
		FMOD_System_Update(g_System);
	}
	else
	{
		StopBGM();
		PlayBGM();
	}

}

void SoundRelease(void)
{
	FMOD_Sound_Release(sound[0]);
	FMOD_Sound_Release(sound[1]);
	FMOD_Sound_Release(sound[2]);
	FMOD_Sound_Release(sound[3]);
	FMOD_Sound_Release(sound[4]);

	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}

void PlaySpaceEffect(void)
{
	//PlaySound(TEXT(BLOCK_DOWN), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);

	//Beep(_G, 100);
	//Sleep(200);
	FMOD_CHANNEL *channel;
	FMOD_System_PlaySound(g_System, sound[0], channelGroup, 0, &channel);
}

void PlayRemoveEffect(void)
{
	//PlaySound(TEXT(BLOCK_REMOVE), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
	//Beep(_B, 100);
	//Sleep(200);
	FMOD_CHANNEL *channel;
	FMOD_System_PlaySound(g_System, sound[1], channelGroup, 0, &channel);
}