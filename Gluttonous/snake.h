#pragma once
class snake
{
public:
	snake();
	~snake();

	void NewSnake(QPoint);
	void KillSnake(void);
	void SnakeMove(void);
	void Grow(void);
	void Death(void);
};

