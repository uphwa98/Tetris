#ifndef __BLOCK_STAGE_CONTROL_H__
#define __BLOCK_STAGE_CONTROL_H__

void InitNewBlockPos(int x, int y);
void ShowBlock(char blockInfo[][4]);
void DeleteBlock(char blockInfo[][4]);
void ChooseBlock(void);
void ShowNextBlock(void);
int GetCurrentBlockIdx(void);

int BlockDown(void);
void ShiftLeft(void);
void ShiftRight(void);
void RotateBlock(void);
void DropBlock(void);

void DrawGameBoard(void);
int isCollision(int posX, int posY, char blockModel[][4]);

void AddCurrentBlockInfoToBoard(void);
int IsGameOver(void);

#endif
