#include <time.h>
#include "common.h"
#include "keyCurControl.h"
#include "blockInfo.h"
#include "blockStageControl.h"
#include "scoreLevelControl.h"
#include "soundEffect.h"
#include "color.h"

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20

#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2

static int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = { 0, }; // 1 더한 것은 아랫쪽 벽, 2 더한 것은 양쪽 벽을 나타냄.

static int currentBlockModel = -1;
static int nextBlockModel;
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
				printf("■");
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

int GetBlockColor(int model)
{
	switch (model)
	{
	case 0:
		return 12;
	case 4:
		return 9;
	case 8:
		return 11;
	case 12:
		return 2;
	case 16:
		return 14;
	case 20:
		return 12;
	case 24:
		return 13;
	}
}

void ChooseBlock(void)
{
	if (currentBlockModel == -1)
	{
		srand((unsigned int)time(NULL));
		currentBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4; // 각 BlockModel 의 첫 번째 index
	}
	else
	{
		currentBlockModel = nextBlockModel;
	}

	srand((unsigned int)time(NULL));
	nextBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4; // 각 BlockModel 의 첫 번째 index

	SetConsoleTextColor(GetBlockColor(currentBlockModel));
}

void DeleteNextBlock()
{
	int y, x;

	point curPos = GetCurrentCursorPos();

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			SetCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);
			printf("  ");
		}
	}
	SetCurrentCursorPos(curPos.x, curPos.y);
}

void ShowNextBlock(void)
{
	SetCurrentCursorPos(30, 1);

	DeleteNextBlock();

	SetConsoleTextColor(GetBlockColor(nextBlockModel));
	ShowBlock(blockModel[nextBlockModel]);
	RestoreTextColor();
}

int GetCurrentBlockIdx(void)
{
	return currentBlockModel;
}

int BlockDown(void)
{
	if (isCollision(curPosX, curPosY + 1, blockModel[GetCurrentBlockIdx()]))
	{
		return 0;
	}

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);

	curPosY++;
	SetCurrentCursorPos(curPosX, curPosY);

	ShowBlock(blockModel[GetCurrentBlockIdx()]);

	return 1;
}

void RotateBlock()
{
	int restoreBlockModel = currentBlockModel;
	if ((restoreBlockModel + 1) % 4 == 0)
	{
		restoreBlockModel -= 3;
	}
	else
	{
		restoreBlockModel += 1;
	}

	if (isCollision(curPosX, curPosY, blockModel[restoreBlockModel]))
	{
		return;
	}

	DeleteBlock(blockModel[currentBlockModel]);

	if ((currentBlockModel + 1) % 4 == 0)
	{
		currentBlockModel -= 3;
	}
	else
	{
		currentBlockModel += 1;
	}

	ShowBlock(blockModel[currentBlockModel]);
}

void ShiftLeft(void)
{
	if (isCollision(curPosX - 2, curPosY, blockModel[currentBlockModel]))
	{
		return;
	}

	DeleteBlock(blockModel[currentBlockModel]);

	curPosX -= 2;
	SetCurrentCursorPos(curPosX, curPosY);

	ShowBlock(blockModel[currentBlockModel]);
}

void ShiftRight(void)
{
	if (isCollision(curPosX + 2, curPosY, blockModel[currentBlockModel]))
	{
		return;
	}

	DeleteBlock(blockModel[currentBlockModel]);

	curPosX += 2;
	SetCurrentCursorPos(curPosX, curPosY);

	ShowBlock(blockModel[currentBlockModel]);
}

void DropBlock(void)
{
	int posY = curPosY;

	while (!isCollision(curPosX, posY, blockModel[currentBlockModel]))
	{
		posY++;
	}

	DeleteBlock(blockModel[currentBlockModel]);

	curPosY = posY - 1;
	SetCurrentCursorPos(curPosX, curPosY);

	ShowBlock(blockModel[currentBlockModel]);
}

void DrawGameBoard(void)
{
	int x;
	int y;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

	for (y = 0; y <= GBOARD_HEIGHT; y++)
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);

		if (y == GBOARD_HEIGHT)
			printf("▧");  //printf("┘");
		else
			puts("▧");  //puts("│");
	}

	for (y = 0; y <= GBOARD_HEIGHT; y++)
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);

		if (y == GBOARD_HEIGHT)
			printf("▧"); //printf("┘");
		else
			puts("▧"); //puts("│");
	}

	for (x = 1; x < GBOARD_WIDTH + 1; x++)
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
		printf("▧"); //printf("─");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	SetCurrentCursorPos(0, 0);


	// 양쪽 벽
	for (y = 0; y < GBOARD_HEIGHT; y++)
	{
		// 왼쪽
		gameBoardInfo[y][0] = 1;

		// 오른쪽
		gameBoardInfo[y][GBOARD_WIDTH + 1] = 1;
	}

	// 아랫쪽 벽
	for (x = 0; x < GBOARD_WIDTH + 2; x++)
	{
		gameBoardInfo[GBOARD_HEIGHT][x] = 1;
	}
}

int isCollision(int posX, int posY, char blockModel[][4])
{
	int tempX = (posX - GBOARD_ORIGIN_X) / 2; // 븍럭이 2칸을 차지하기 때문
	int tempY = posY - GBOARD_ORIGIN_Y;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockModel[y][x] == 1 && gameBoardInfo[tempY + y][tempX + x] == 1)
			{
				return 1;
			}
		}
	}

	return 0;
}

void removeLine(int index)
{
	for (int y = index; y > 0; y--)
	{
		int posY = GBOARD_ORIGIN_Y + y;
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 2, posY);

		for (int x = 1; x <= GBOARD_WIDTH; x++)
		{
			gameBoardInfo[y][x] = gameBoardInfo[y - 1][x];

			if (gameBoardInfo[y][x] == 1)
				printf("■");
			else
				printf("  ");
		}
	}

	for (int x = 1; x <= GBOARD_WIDTH; x++)
	{
		gameBoardInfo[0][x] = 0;
	}
}

int cal_score(int removeCount)
{
	int score;
	switch (removeCount)
	{
	case 0:
	case 1:
		score = 0;
		break;
	case 2:
		score = 20;
		break;
	case 3:
		score = 30;
		break;
	case 4:
		score = 60;
		break;
	}

	return score;
}

void AddCurrentBlockInfoToBoard(void)
{
	int extra_score = 0;
	int x;
	int y;

	int arrCurX = (curPosX - GBOARD_ORIGIN_X) / 2;
	int arrCurY = curPosY - GBOARD_ORIGIN_Y;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockModel[currentBlockModel][y][x] == 1)
			{
				gameBoardInfo[arrCurY + y][arrCurX + x] = 1;
			}
		}
	}

	y = 3;
	while (arrCurY + y >= GBOARD_HEIGHT)
	{
		y--;

	}

	for (int i = 0; i < 4 && y >= 0; i++)
	{
		for (x = 1; x <= GBOARD_WIDTH; x++)
		{
			if (gameBoardInfo[arrCurY + y][x] == 0)
				break;
		}

		if (x == GBOARD_WIDTH + 1 && gameBoardInfo[arrCurY + y][GBOARD_WIDTH] == 1)
		{
			extra_score++;

			PlayRemoveEffect();
			removeLine(arrCurY + y);
			UpdateScore(10);
			Sleep(500);
		}
		else
		{
			y--;
		}
	}

	UpdateScore(cal_score(extra_score));
}

int IsGameOver(void)
{
	if (isCollision(curPosX, curPosY, blockModel[currentBlockModel]))
	{
		return 1;
	}

	return 0;
}