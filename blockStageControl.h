#ifndef __BLOCK_STAGE_CONTROL_H__
#define __BLOCK_STAGE_CONTROL_H__

void InitNewBlockPos(int x, int y);
void ShowBlock(char blockInfo[][4]);
void DeleteBlock(char blockInfo[][4]);
void ChooseBlock(void);
int GetCurrentBlockIdx(void);

int BlockDown(void);
void ShiftLeft();
void ShiftRight();
void RotateBlock();

void DrawGameBoard(void);
int isCollision(int posX, int posY, char blockModel[][4]);

void AddCurrentBlockInfoToBoard(void);
int IsGameOver(void);

#endif
