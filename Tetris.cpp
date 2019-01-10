#include "common.h"
#include "blockStageControl.h"
#include "keyCurControl.h"


int main()
{
	DrawGameBoard();
#if 1
	InitKeyDelayRate(6);

	RemoveCursor();

	while (1)
	{
		InitNewBlockPos(10, 0);
		ChooseBlock();

		if (IsGameOver())
			break;

		int i = 0;
		while (1)
		{
			if (!BlockDown())
			{
				AddCurrentBlockInfoToBoard();
				break;
			}

			ProcessKeyInput();

			i++;
		}
	}
#endif
    return 0;
}

