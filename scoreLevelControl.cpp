#include "common.h"
#include "keyCurControl.h"
#include "soundEffect.h"
#include "color.h"

#define LEVEL_UP_SCORE_DIFF 100

static int gameLevel = 0;
static int gameScore = 0;

void UpdateLevel(void)
{


	SetCurrentCursorPos(30, 5);

	gameLevel++;

	SetConsoleTextColor(7);
	printf("§ 현재 레벨: %d  §", gameLevel);
	RestoreTextColor();
}

void UpdateScore(int score)
{
	SetCurrentCursorPos(30, 8);

	gameScore += score;
	SetConsoleTextColor(7);
	printf("§ 현재 점수: %d  §", gameScore);
	RestoreTextColor();

	if (gameScore >= gameLevel * LEVEL_UP_SCORE_DIFF)
	{
		UpdateLevel();
		UpdateKeyDelayRate();
	}
}