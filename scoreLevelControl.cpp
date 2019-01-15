#include "common.h"
#include "keyCurControl.h"

static int gameLevel = 0;
static int gameScore = -20;

void UpdateLevel(void)
{
	SetCurrentCursorPos(30, 5);

	gameLevel++;
	printf("§ 현재 레벨: %d  §", gameLevel);

}

void UpdateScore(void)
{
	SetCurrentCursorPos(30, 8);

	gameScore += 20;
	printf("§ 현재 점수: %d  §", gameScore);

	if (gameScore != 0 && gameScore % 100 == 0)
	{
		UpdateLevel();
		UpdateKeyDelayRate();
	}
}