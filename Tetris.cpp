#include "common.h"
#include "blockStageControl.h"
#include "keyCurControl.h"

#define SYS_DELAY 100

int main()
{
	RemoveCursor();

	InitNewBlockPos(10, 0);
	ChooseBlock();

	int i = 0;
	while (i < 20)
	{
		BlockDown();
		Sleep(SYS_DELAY);
		i++;
	}

    return 0;
}

