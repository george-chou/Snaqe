#include "stdafx.h"

int  L_x, L_y, F_x, F_y, v, N, Snake_Length;
bool GameOver, Pause;
body Sn[Res * Res];

int max(int x, int y){
	return (x > y) ? x : y;
}

int max_4(int a, int b, int c, int d){
	return max(max(max(a, b), c), d);
}