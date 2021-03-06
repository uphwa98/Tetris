#include "common.h"
#include "blockStageControl.h"
#include "keyCurControl.h"
#include "scoreLevelControl.h"
#include "soundEffect.h"

//#include <mmsystem.h>
//#pragma comment(lib, "winmm.lib")
//#define TETRIS_SOUND "tetris_sound.wav"

#define START_CURPOS_X (5 * 2)
#define START_CURPOS_Y (0)

int main(void)
{
	//SND_ASYNC : 재생하면서 다음코드 실행
	//SND_LOOP : 반복재생
	//PlaySound(TEXT(TETRIS_SOUND), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

	InitSound();
	PlayBGM();

	UpdateLevel();
	UpdateScore(0);

	InitKeyDelayRate(2);

	RemoveCursor();

	DrawGameBoard();

	while (1)
	{
		ChooseBlock();

		ShowNextBlock();

		InitNewBlockPos(START_CURPOS_X, START_CURPOS_Y);

		if (IsGameOver())
		{
			break;
		}

		while (1)
		{
			if (!BlockDown())
			{
				PlaySpaceEffect();
				AddCurrentBlockInfoToBoard();
				break;
			}

			ProcessKeyInput();
		}

		UpdateSound();
	}

	SetCurrentCursorPos(10, 10);
	puts("GAME OVER ^^");

	//PlaySound(NULL, 0, 0);
	StopBGM();
	SoundRelease();

	system("pause");

    return 0;
}

