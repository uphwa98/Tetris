#ifndef __BLOCK_STAGE_CONTROL_H__
#define __BLOCK_STAGE_CONTROL_H__

void InitNewBlockPos(int x, int y);
void ShowBlock(char blockInfo[][4]);
void DeleteBlock(char blockInfo[][4]);
void ChooseBlock(void);
int GetCurrentBlockIdx(void);

void BlockDown(void);
void ShiftLeft();
void ShiftRight();
void RotateBlock();

#endif
