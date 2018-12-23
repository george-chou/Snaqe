#pragma once
using namespace std;

class AI
{
public:
	AI();
	~AI();

	QPoint  amoveSnake(QPoint, QPoint); 

private:
	
	int findPath(QPoint, QPoint, QPoint *);
	vector<vector<int>> initMaze(body *);
	bool findTail(QPoint *, int);
	bool virtualSnake(QPoint *, int);
	bool neighbor(QPoint, QPoint);
	QPoint departFood(QPoint);
	bool Bit(QPoint);
	bool Border(QPoint);
	bool safeRandStep(QPoint, direction);
	void dirArray(QPoint, QPoint, direction *);
	QPoint dir2p(QPoint, direction);
};

