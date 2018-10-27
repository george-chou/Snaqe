#include "stdafx.h"

int  v, N, Snake_Length;
bool GameOver, Pause;
body Sn[Res * Res];

QPoint L, F;  

int max(int x, int y)
{
	return (x > y) ? x : y;
}

int max_4(int a, int b, int c, int d)
{
	return max(max(max(a, b), c), d);
}