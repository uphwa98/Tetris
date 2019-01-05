#include "common.h"
#include "point.h"

void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

point GetCurrentCursorPos(void)
{
	point curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	curPoint.x = curInfo.dwCursorPosition.X;
	curPoint.y = curInfo.dwCursorPosition.Y;

	return curPoint;
}

void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x, y };

	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hConsoleOut, pos);
}