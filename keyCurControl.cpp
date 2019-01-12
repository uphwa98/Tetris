#include <conio.h>
#include "common.h"
#include "point.h"
#include "blockStageControl.h"

#define KEY_SENSITIVE 100
#define SYS_DELAY 20

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

static int keyDelayRate;

void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

point GetCurrentCursorPos(void)
{
	point curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	curPoint.x = curInfo.dwCursorPosition.X;
	curPoint.y = curInfo.dwCursorPosition.Y;

	return curPoint;
}

void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x, y };

	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hConsoleOut, pos);
}

void ProcessKeyInput(void)
{
	int i;
	int key;

	for (i = 0; i < KEY_SENSITIVE; i++)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case LEFT:
				ShiftLeft();
				break;
			case RIGHT:
				ShiftRight();
				break;
			case UP:
				RotateBlock();
				break;
			case DOWN:
				BlockDown();
				break;
			case SPACE:
				DropBlock();
				break;
			}
		}

		if (i % keyDelayRate == 0)
		{
			Sleep(SYS_DELAY);
		}
	}
}

void InitKeyDelayRate(int rate)
{
	if (rate < 1)
		return;

	keyDelayRate = rate;
}