#include "stdafx.h"
#include "snake.h"



snake::snake()
{
}


snake::~snake()
{
}


void snake::NewSnake(QPoint p)
{
	L = 2;

	//Sn[0].X_NOW = p.x();
	//Sn[0].Y_NOW = p.y();
	Sn[0].NOW = p;

	switch (v)
	{
	case V_RIGHT:
		//Sn[1].X_NOW = Sn[0].X_NOW - 1;
		//Sn[1].Y_NOW = Sn[0].Y_NOW;
		Sn[1].NOW.setX(Sn[0].NOW.x() - 1);
		Sn[1].NOW.setY(Sn[0].NOW.y());
		break;

	case V_LEFT:
		//Sn[1].X_NOW = Sn[0].X_NOW + 1;
		//Sn[1].Y_NOW = Sn[0].Y_NOW;
		Sn[1].NOW.setX(Sn[0].NOW.x() + 1);
		Sn[1].NOW.setY(Sn[0].NOW.y());
		break;

	case V_UP:
		//Sn[1].X_NOW = Sn[0].X_NOW;
		//Sn[1].Y_NOW = Sn[0].Y_NOW - 1;
		Sn[1].NOW.setX(Sn[0].NOW.x());
		Sn[1].NOW.setY(Sn[0].NOW.y() - 1);
		break;

	case V_DOWN:
		//Sn[1].X_NOW = Sn[0].X_NOW;
		//Sn[1].Y_NOW = Sn[0].Y_NOW + 1;
		Sn[1].NOW.setX(Sn[0].NOW.x());
		Sn[1].NOW.setY(Sn[0].NOW.y() + 1);
		break;

	default:
		break;
	}
}


void snake::Death(void)
{
	GameOver = (H.x() >= N || H.y() >= N || H.x() < 0 || H.y() < 0);

	if (L > 4){
		bool Bitten = false;
		for (int i = 4; i <= L - 1; i++)
		{
			if (Sn[0].NOW == Sn[i].NOW)	// Sn[0].X_NOW == Sn[i].X_NOW && Sn[0].Y_NOW == Sn[i].Y_NOW)
			{
				Bitten = true;
				break;
			}
		}
		GameOver = GameOver || Bitten;
	}
}



void snake::SnakeMove(QPoint H)
{ 
	//Sn[L - 1].X_OLD = Sn[L - 1].X_NOW;
	//Sn[L - 1].Y_OLD = Sn[L - 1].Y_NOW; 
	Sn[L - 1].OLD = Sn[L - 1].NOW;

	for (int i = L - 1; i >= 1; i--)
	{
		//Sn[i].X_NOW = Sn[i - 1].X_NOW;
		//Sn[i].Y_NOW = Sn[i - 1].Y_NOW;
		Sn[i].NOW = Sn[i - 1].NOW;
	}

	//Sn[0].X_NOW = H.x();
	//Sn[0].Y_NOW = H.y();
	Sn[0].NOW = H;
}

void snake::KillSnake(void)
{ 
	for (int i = 0; i <= L - 1; i++)
	{
		//Sn[i].X_NOW = Sn[i].X_OLD = Sn[i].Y_NOW = Sn[i].Y_OLD = -1;
		Sn[i].NOW = Sn[i].OLD = QPoint(-1, -1);
	}
}

void snake::Grow(void)
{
	L++;
	//Sn[L - 1].X_NOW = Sn[L - 2].X_OLD;
	//Sn[L - 1].Y_NOW = Sn[L - 2].Y_OLD;
	Sn[L - 1].NOW = Sn[L - 2].OLD;
}

