#include "common.h"

int currentColor = FOREGROUND_INTENSITY;
int previousColor = FOREGROUND_INTENSITY;

void SetConsoleTextColor(int color)
{
	previousColor = currentColor;
	currentColor = color;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void RestoreTextColor(void)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), previousColor);
	currentColor = previousColor;
}