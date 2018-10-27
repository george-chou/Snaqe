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

bool game::MissionImpossible(int L)
{
	bool w = (L >= N * N);
	if (w) GameOver = true; 
	return w;
}


bool game::Covered(QPoint p)
{
	int i;
	bool cover = false;

	for (i = 0; i <= L - 1; i++)
	{
		if (Sn[i].X_NOW == p.x() && Sn[i].Y_NOW == p.y())
		{
			cover = true;
			break;
		}
	}
	return cover;
}

QPoint game::RandCoord(void)
{
	QPoint p(0, 0);
	srand(time(NULL));
	p.setX(rand() % N);
	p.setY(rand() % N);
	return p;
}

void game::CreateFood(void)
{
	QPoint prf(0, 0);
	do
	{
		prf = RandCoord();

	} while (Covered(prf));
	F = prf;
}

void game::Direction(int v)
{
	switch (v)
	{
	case V_RIGHT: H.setX(H.x() + 1); break;
	case V_LEFT:  H.setX(H.x() - 1); break;
	case V_UP:    H.setY(H.y() + 1); break;
	case V_DOWN:  H.setY(H.y() - 1); break;
	default: break;
	}
}


int game::InitDir(QPoint p)
{
	int d_left = p.x();
	int d_down = p.y();
	int d_right = N - 1 - p.x();
	int d_up = N - 1 - p.y();

	int d_max = max_4(d_left, d_down, d_right, d_up);
	int dv = V_RIGHT;

	if      (d_left == d_max)  dv = V_LEFT;
	else if (d_down == d_max)  dv = V_DOWN;
	else if (d_right == d_max) dv = V_RIGHT;
	else if (d_up == d_max)    dv = V_UP;

	return dv;
}

