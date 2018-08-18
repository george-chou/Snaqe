#pragma once
class snake
{
public:
	snake();
	~snake();

	void NewSnake(int x, int y);
	void KillSnake(void);
	void SnakeMove(void);
	void Grow(void);
	void Death(void);
};

