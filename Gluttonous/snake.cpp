#include "stdafx.h"
#include "snake.h"



snake::snake()
{
}


snake::~snake()
{
}


void snake::NewSnake(QPoint p){
	Snake_Length = 2;

	Sn[0].X_NOW = p.x();
	Sn[0].Y_NOW = p.y();

	switch (v)
	{
	case V_RIGHT:
		Sn[1].X_NOW = Sn[0].X_NOW - 1;
		Sn[1].Y_NOW = Sn[0].Y_NOW;
		break;
	case V_LEFT:
		Sn[1].X_NOW = Sn[0].X_NOW + 1;
		Sn[1].Y_NOW = Sn[0].Y_NOW;
		break;
	case V_UP:
		Sn[1].X_NOW = Sn[0].X_NOW;
		Sn[1].Y_NOW = Sn[0].Y_NOW - 1;
		break;
	case V_DOWN:
		Sn[1].X_NOW = Sn[0].X_NOW;
		Sn[1].Y_NOW = Sn[0].Y_NOW + 1;
		break;
	default:
		break;
	}
}


void snake::Death(void)
{
	GameOver = (L.x() >= N || L.y() >= N || L.x() < 0 || L.y() < 0);

	if (Snake_Length > 4){
		bool Bitten = false;
		for (int i = 4; i <= Snake_Length - 1; i++){
			if (Sn[0].X_NOW == Sn[i].X_NOW && Sn[0].Y_NOW == Sn[i].Y_NOW){
				Bitten = true;
				break;
			}
		}
		GameOver = GameOver || Bitten; 
	}
}



void snake::SnakeMove(void)
{
	Sn[Snake_Length - 1].X_OLD = Sn[Snake_Length - 1].X_NOW;
	Sn[Snake_Length - 1].Y_OLD = Sn[Snake_Length - 1].Y_NOW;
	for (int i = Snake_Length - 1; i >= 1; i--){
		Sn[i].X_NOW = Sn[i - 1].X_NOW;
		Sn[i].Y_NOW = Sn[i - 1].Y_NOW;
	}
	Sn[0].X_NOW = L.x();
	Sn[0].Y_NOW = L.y();
}

void snake::KillSnake(void)
{
	for (int i = 0; i <= Snake_Length - 1; i++){
		Sn[i].X_NOW = Sn[i].X_OLD = Sn[i].Y_NOW = Sn[i].Y_OLD = -1;
	}
}

void snake::Grow(void)
{
	Snake_Length++;
	Sn[Snake_Length - 1].X_NOW = Sn[Snake_Length - 2].X_OLD;
	Sn[Snake_Length - 1].Y_NOW = Sn[Snake_Length - 2].Y_OLD;
}

