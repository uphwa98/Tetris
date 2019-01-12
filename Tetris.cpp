#include "common.h"
#include "blockStageControl.h"
#include "keyCurControl.h"
#include "scoreLevelControl.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define TETRIS_SOUND "tetris_sound.wav"//"F:\\Tetris\\tetris_sound.wav"

#define START_CURPOS_X (5 * 2)
#define START_CURPOS_Y (0)

int main()
{
	PlaySound(TEXT(TETRIS_SOUND), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	//사운드 파일 위치, SND_ASYNC, SND_LOOP 세가지가 제일 중요
	//SND_ASYNC : 재생하면서 다음코드 실행
	//SND_LOOP : 반복재생

	UpdateLevel();
	UpdateScore();

#if 1
	InitKeyDelayRate(2);

	RemoveCursor();

	DrawGameBoard();

	while (1)
	{
		InitNewBlockPos(START_CURPOS_X, START_CURPOS_Y);

		ChooseBlock();

		if (IsGameOver())
			break;

		while (1)
		{
			if (!BlockDown())
			{
				AddCurrentBlockInfoToBoard();
				break;
			}

			ProcessKeyInput();
		}
	}
	SetCurrentCursorPos(10, 10);
	puts("GAME OVER ^^");

	PlaySound(NULL, 0, 0);

#endif
    return 0;
}

