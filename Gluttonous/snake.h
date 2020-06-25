#pragma once
class snake
{
public:
	snake();
	~snake();

	void NewSnake(QPoint);
	void KillSnake(void);
	void SnakeMove(QPoint);
	void Grow(void);
	void Death(void);
};

