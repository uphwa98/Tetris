#include "common.h"
#include "blockStageControl.h"
#include "keyCurControl.h"

int main()
{
	//TestconHitRead();
#if 1
	InitKeyDelayRate(6);

	RemoveCursor();

	InitNewBlockPos(10, 0);
	ChooseBlock();

	int i = 0;
	while (i < 20)
	{
		BlockDown();
		
		ProcessKeyInput();

		i++;
	}
#endif
    return 0;
}

