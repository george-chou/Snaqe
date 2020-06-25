#pragma once 

struct vertex
{
	QPoint coord; 
	int ajp[4];
	int ajNum;
	int deep;
};
 

class BFS
{
private:

	int map[N][N];
	QPoint Edges[4 * N * N];
	vertex Steps[N * N];
	int sNum;
	int eNum;

public:
	BFS();
	~BFS(); 
	bool createGraph(QPoint *);// body *);

private:

	
	void initMap(void);// body *);
	BOOL onSnake(int, int);// , body *);

	bool inMap(QPoint);
	bool searchNeighbor(int);// vertex *);
	bool inArray(vertex, QPoint);
	bool isChild(QPoint);
	int unVisited(vertex, QPoint *);
	int Visited(QPoint);
	int isTail(void);
};

