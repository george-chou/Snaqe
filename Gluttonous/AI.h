#pragma once
using namespace std;

enum Towards
{
	EAST = 0,
	E2NE,
	NE,
	NE2N,
	NORTH,
	N2NW,
	NW,
	NW2W,
	WEST,
	W2SW,
	SW,
	SW2S,
	SOUTH,
	S2SE,
	SE,
	SE2E,
	CENTER
};

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
	QPoint compass(QPoint, QPoint);
	bool Bit(QPoint);
	bool Border(QPoint);
	QPoint safeRandStep(QPoint); 
	Towards dirArray(QPoint, QPoint, QPoint *);
	BOOL randBOOL(void);
	QPoint dir2p(QPoint, direction);
	bool boundFood(QPoint);
	direction vDir(QPoint, QPoint);
	QPoint noCircle(QPoint *, QPoint, int, BOOL);
	bool  diag(QPoint, QPoint);

	int bFilter(QPoint *, QPoint *);
	int tFilter(QPoint *, int, QPoint *);
	bool canFindTail(QPoint);

	int findPath(QPoint *, QPoint, QPoint *);

	bool Bound(QPoint);
	bool mayEndlessLoop(body *, QPoint *);

	int canVeer(QPoint, QPoint, QPoint *);

	QPoint avoidLoop(QPoint);
	bool tryfillMode(int);
};

