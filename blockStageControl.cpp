#include <time.h>
#include "common.h"
#include "keyCurControl.h"
#include "blockInfo.h"
#include "blockStageControl.h"

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20

#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2

static int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = { 0, }; // 1 ���� ���� �Ʒ��� ��, 2 ���� ���� ���� ���� ��Ÿ��.

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
				printf("��");
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

int BlockDown(void)
{
	if (isCollision(curPosX, curPosY + 1, blockModel[currentBlockModel]))
	{
		return 0;
	}

	DeleteBlock(blockModel[currentBlockModel]);

	curPosY++;
	SetCurrentCursorPos(curPosX, curPosY);

	ShowBlock(blockModel[currentBlockModel]);

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

#if 0
void DrawGameBoard(void)
{
	int x;
	int y;

	SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);


	for (y = 0; y < GBOARD_HEIGHT; y++)
	{
		puts("��");
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
	}
	printf("��");

	for (x = 1; x <= GBOARD_WIDTH; x++)
	{
		printf("��");
		//SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT - 1);
		//printf("��");
	}

	int tempX = GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 2;
	SetCurrentCursorPos(tempX, GBOARD_ORIGIN_Y);

	for (y = 0; y < GBOARD_HEIGHT; y++)
	{
		puts("��");
		SetCurrentCursorPos(tempX, GBOARD_ORIGIN_Y + y);
	}
	printf("��");

	SetCurrentCursorPos(0, 0);

	// ���� ��
	for (y = 0; y <= GBOARD_HEIGHT; y++)
	{
		// ����
		gameBoardInfo[y][0] = 1;
		
		// ������
		gameBoardInfo[y][GBOARD_WIDTH + 1] = 1;
	}

	// �Ʒ��� ��
	for (x = 0; x < GBOARD_WIDTH + 2; x++)
	{
		gameBoardInfo[GBOARD_HEIGHT][x] = 1;
	}
}
#endif

void DrawGameBoard(void)
{
	int x;
	int y;

	for (y = 0; y <= GBOARD_HEIGHT; y++)
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);

		if (y == GBOARD_HEIGHT)
			printf("��");
		else
			puts("��");
	}

	for (y = 0; y <= GBOARD_HEIGHT; y++)
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);

		if (y == GBOARD_HEIGHT)
			printf("��");
		else
			puts("��");
	}

	for (x = 1; x <= GBOARD_WIDTH; x++)
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
		printf("��");
	}



	SetCurrentCursorPos(0, 0);

	// ���� ��
	for (y = 0; y <= GBOARD_HEIGHT; y++)
	{
		// ����
		gameBoardInfo[y][0] = 1;

		// ������
		gameBoardInfo[y][GBOARD_WIDTH + 1] = 1;
	}

	// �Ʒ��� ��
	for (x = 0; x < GBOARD_WIDTH + 2; x++)
	{
		gameBoardInfo[GBOARD_HEIGHT][x] = 1;
	}
}

int isCollision(int posX, int posY, char blockModel[][4])
{
	int tempX = (posX - GBOARD_ORIGIN_X) / 2;
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

void AddCurrentBlockInfoToBoard(void)
{
	int x;
	int y;

	int arrCurX;
	int arrCurY;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int tempX = (curPosX - GBOARD_ORIGIN_X) / 2;
			int tempY = curPosY - GBOARD_ORIGIN_Y;

			if (blockModel[currentBlockModel][y][x] == 1)
			{
				gameBoardInfo[tempY + y][tempX + x] = 1;
			}
		}
	}
}

int IsGameOver(void)
{
	if (isCollision(curPosX, curPosY, blockModel[currentBlockModel]))
	{
		return 1;
	}

	return 0;
}