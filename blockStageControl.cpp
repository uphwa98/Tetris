#include <time.h>
#include "common.h"
#include "keyCurControl.h"
#include "blockInfo.h"

static int currentBlockModel;
static int curPosX;
static int curPosY;

void InitNewBlockPos(int x, int y)
{
	if (x < 0 || y < 0)
		return;

	curPosX = x;
	curPosY = y;

	SetCurrentCursorPos(x, y);
}

void ShowBlock(char blockInfo[][4])
{
	int y, x;

	point curPos = GetCurrentCursorPos();

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			SetCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);

			if (blockInfo[y][x] == 1)
			{
				printf("бс");
			}
		}
	}
	SetCurrentCursorPos(curPos.x, curPos.y);
}

void DeleteBlock(char blockInfo[][4])
{
	int y, x;

	point curPos = GetCurrentCursorPos();

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			SetCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);

			if (blockInfo[y][x] == 1)
			{
				printf("  ");
			}
		}
	}
	SetCurrentCursorPos(curPos.x, curPos.y);
}


void ChooseBlock(void)
{
	srand((unsigned int)time(NULL));
	currentBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4;
}

int GetCurrentBlockIdx(void)
{
	return currentBlockModel;
}

void BlockDown(void)
{
	DeleteBlock(blockModel[currentBlockModel]);

	curPosY++;
	SetCurrentCursorPos(curPosX, curPosY);

	ShowBlock(blockModel[currentBlockModel]);
}