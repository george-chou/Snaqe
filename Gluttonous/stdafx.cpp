#include "stdafx.h"

int  v, L;
bool GameOver, Pause, Auto;
body Sn[N * N];
QPoint H, F;

int max(int x, int y)
{
	return (x > y) ? x : y;
}

int max_4(int a, int b, int c, int d)
{
	return max(max(max(a, b), c), d);
}

int Abs(int x)
{
	return (x >= 0) ? (x) : (-x);
}