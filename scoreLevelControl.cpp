#include "common.h"
#include "keyCurControl.h"

#define LEVEL_UP_SCORE_DIFF 100

static int gameLevel = 0;
static int gameScore = 0;

void UpdateLevel(void)
{
	SetCurrentCursorPos(30, 5);

	gameLevel++;
	printf("�� ���� ����: %d  ��", gameLevel);

}

void UpdateScore(int score)
{
	SetCurrentCursorPos(30, 8);

	gameScore += score;
	printf("�� ���� ����: %d  ��", gameScore);

	if (gameScore >= gameLevel * LEVEL_UP_SCORE_DIFF)
	{
		UpdateLevel();
		UpdateKeyDelayRate();
	}
}