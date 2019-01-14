#include<Windows.h>

#define _C 1046.502
#define _D 1108.731
#define _E 1318.510
#define _F 1396.913
#define _G 1567.982
#define _A 1760.000
#define _B 1975.533

#define BLOCK_DOWN "block_down.wav"
#define BLOCK_REMOVE "block_remove.wav"

void PlaySpaceEffect(void)
{
	//PlaySound(TEXT(BLOCK_DOWN), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);

	Beep(_G, 100);
	Sleep(200);
}

void PlayRemoveEffect(void)
{
	//PlaySound(TEXT(BLOCK_REMOVE), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
	Beep(_B, 100);
	Sleep(200);
}