#include "stdafx.h"
#include "game.h"
#include "stdlib.h"
#include "time.h"


game::game()
{
}


game::~game()
{
}

bool game::MissionImpossible(int Snake_Length)
{
	bool w = (Snake_Length >= N * N);
	if (w) GameOver = true; 
	return w;
}


bool game::Covered(int x, int y){
	bool cover = false;
	for (int i = 0; i <= Snake_Length - 1; i++){
		if (Sn[i].X_NOW == x && Sn[i].Y_NOW == y){
			cover = true;
			break;
		}
	}
	return cover;
}

void game::RandCoord(int *F_x, int *F_y)
{
	srand(time(NULL));
	*F_x = rand() % N;
	*F_y = rand() % N;
}

void game::CreateFood(void)
{
	do
	{
		RandCoord(&F_x, &F_y);

	} while (Covered(F_x, F_y));
}

void game::Direction(int v)
{
	switch (v)
	{
	case V_RIGHT: L_x++; break;
	case V_LEFT:  L_x--; break;
	case V_UP:    L_y++; break;
	case V_DOWN:  L_y--; break;
	default: break;
	}
}


int game::InitDir(int x, int y)
{
	int d_left = x;
	int d_down = y;
	int d_right = N - 1 - x;
	int d_up = N - 1 - y;

	int d_max = max_4(d_left, d_down, d_right, d_up);
	int dv = V_RIGHT;

	if (d_left == d_max)  dv = V_LEFT;
	else if (d_down == d_max)  dv = V_DOWN;
	else if (d_right == d_max) dv = V_RIGHT;
	else if (d_up == d_max)    dv = V_UP;

	return dv;
}

