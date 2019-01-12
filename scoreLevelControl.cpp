#include "common.h"
#include "keyCurControl.h"

static int gameLevel = 0;
static int gameScore = -10;

void UpdateLevel(void)
{
	SetCurrentCursorPos(30, 4);

	gameLevel++;
	printf("�� ���� ����: %d  ��", gameLevel);

}

void UpdateScore(void)
{
	SetCurrentCursorPos(30, 7);

	gameScore += 10;
	printf("�� ���� ����: %d  ��", gameScore);

	if (gameScore != 0 && gameScore % 100 == 0)
	{
		UpdateLevel();
		UpdateKeyDelayRate();
	}
}