#ifndef __KEY_CUR_CONTROL_H__
#define __KEY_CUR_CONTROL_H__
#include "point.h"

void RemoveCursor(void);
point GetCurrentCursorPos(void);
void SetCurrentCursorPos(int x, int y);

void ProcessKeyInput(void);
void InitKeyDelayRate(int rate);

#endif

