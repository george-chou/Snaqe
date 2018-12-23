#include "stdafx.h"
#include "AI.h"
#include "astar.h"


AI::AI()
{
}


AI::~AI()
{
}


vector<vector<int>> AI::initMaze(body *Sn)
{
	int i, j;
	vector<vector<int>> maze(N + 2);

	for (i = 0; i < N + 2; i++)
	{
		maze[i].resize(N + 2);
	}

	for (i = 0; i < N + 2; i++)
	{
		for (j = 0; j < N + 2; j++)
		{
			maze[i][j] = (int)(i == 0 || j == 0 || i == N + 1 || j == N + 1);
		}
	}

	for (i = 1; i < L; i++)    // involve tail while searching food
	{
		maze[Sn[i].X_NOW + 1][Sn[i].Y_NOW + 1] = 1;
	}

	return maze;
}

int AI::findPath(QPoint H, QPoint F, QPoint *pA)
{
	int i = 0; 
	Astar astar; 	
	Point start(H.x() + 1, H.y() + 1);
	Point end(F.x() + 1, F.y() + 1);

	vector<vector<int>> maze = initMaze(Sn);
	astar.InitAstar(maze);
	list<Point *> path = astar.GetPath(start, end, false);

	for (auto &p : path)
	{

		QPoint cp(p->x - 1, p->y - 1);
 
		if (i > 0)
		{
			if (neighbor(cp, pA[i - 1]))
			{
				*(pA + i) = cp;
				i++;
			}
			else
			{
				(pA + i)->setX(pA[i - 1].x());
				(pA + i)->setY(cp.y());
				*(pA + i + 1) = cp;
				i += 2;
			}
		}
		else
		{
			*(pA + i) = cp;
			i++;
		}
	}

	return i;
}

bool AI::neighbor(QPoint p1, QPoint p2)
{
	return (Abs(p1.x() - p2.x()) + Abs(p1.y() - p2.y()) == 1);
}

bool AI::findTail(QPoint *s, int n)
{
	int i, j;
	Astar astar; 
	vector<vector<int>> maze(N + 2);
	Point start(s[0].x() + 1, s[0].y() + 1);
	Point end(s[n].x() + 1, s[n].y() + 1); 

	for (i = 0; i < N + 2; i++)
	{
		maze[i].resize(N + 2);
	}

	for (i = 0; i < N + 2; i++)
	{
		for (j = 0; j < N + 2; j++)
		{
			maze[i][j] = (int)(i == 0 || j == 0 || i == N + 1 || j == N + 1);
		}
	}

	for (i = 1; i < n; i++)
	{
		maze[s[i].x() + 1][s[i].y() + 1] = 1;
	}
	
	astar.InitAstar(maze);
	list<Point *> path = astar.GetPath(start, end, false);

	i = 0;
	for (auto &p : path)
	{
		i++;
		if (i > 0) break;
	}

	return (i > 0);
}

bool AI::virtualSnake(QPoint *s, int n)
{ 
	if (n > 0)
	{
		int i;
		QPoint *p = (QPoint *)malloc(sizeof(QPoint)* (L + 1));

		if (n > L)
		{
			for (i = 0; i <= L; i++)
			{
				p[i] = s[n - 1 - i];
			}
		}
		else
		{

			for (i = 0; i <= n - 1; i++)
			{
				p[i] = s[n - 1 - i];
			}

			for (i = n; i <= L; i++)
			{
				p[i].setX(Sn[i - n + 1].X_NOW);
				p[i].setY(Sn[i - n + 1].Y_NOW);
			}

		}

		return findTail(p, L);
	}
	else
	{
		return false;
	}
}

bool AI::Bit(QPoint p)
{ 
	for (int i = 1; i < L - 1; i++)
	{
		if (Sn[i].X_NOW == p.x() && Sn[i].Y_NOW == p.y())
		{
			return true;
		}
	}

	return false;
}

bool AI::Border(QPoint p)
{
	return (0 > p.x() || p.x() > N - 1 || 0 > p.y() || p.y() > N - 1);
}

bool AI::safeRandStep(QPoint H, direction V)
{
	QPoint vH = dir2p(H, V);

	if (!Bit(vH) && !Border(vH))
	{
		QPoint *p = (QPoint *)malloc(sizeof(QPoint)* L);

		p[0] = vH;

		for (int i = 1; i <= L - 1; i++)
		{
			p[i].setX(Sn[i - 1].X_NOW);
			p[i].setY(Sn[i - 1].Y_NOW);
		}

		return findTail(p, L - 1);

	}
	else
	{
		return false;
	}
}

void AI::dirArray(QPoint F, QPoint H, direction *v)
{
	int x = (H - F).x();
	int y = (H - F).y();

	if (0 <= y && y <= x)
	{
		*(v + 0) = V_RIGHT;
		*(v + 1) = V_UP;
		*(v + 2) = V_DOWN;
		*(v + 3) = V_LEFT;
	}
	else if (0 <= x && x <= y)
	{
		*(v + 0) = V_UP;
		*(v + 1) = V_RIGHT;
		*(v + 2) = V_LEFT;
		*(v + 3) = V_DOWN;
	}
	else if (0 <= -x && -x <= y)
	{
		*(v + 0) = V_UP;
		*(v + 1) = V_LEFT;
		*(v + 2) = V_RIGHT;
		*(v + 3) = V_DOWN;
	}
	else if (0 <= y && y <= -x)
	{
		*(v + 0) = V_LEFT;
		*(v + 1) = V_UP;
		*(v + 2) = V_DOWN;
		*(v + 3) = V_RIGHT;
	}
	else if (x <= y && y <= 0)
	{
		*(v + 0) = V_LEFT;
		*(v + 1) = V_DOWN;
		*(v + 2) = V_UP;
		*(v + 3) = V_RIGHT;
	}
	else if (y <= x && x <= 0)
	{
		*(v + 0) = V_DOWN;
		*(v + 1) = V_LEFT;
		*(v + 2) = V_RIGHT;
		*(v + 3) = V_UP;
	}
	else if (y <= -x && -x <= 0)
	{
		*(v + 0) = V_DOWN;
		*(v + 1) = V_RIGHT;
		*(v + 2) = V_LEFT;
		*(v + 3) = V_UP;
	}
	else 
	{
		*(v + 0) = V_RIGHT;
		*(v + 1) = V_DOWN;
		*(v + 2) = V_UP;
		*(v + 3) = V_LEFT;
	} 
}

QPoint AI::dir2p(QPoint H, direction v)
{
	switch (v)
	{
	case V_RIGHT: return QPoint(H.x() + 1, H.y());
	case V_LEFT:  return QPoint(H.x() - 1, H.y());
	case V_UP:	  return QPoint(H.x(), H.y() + 1);
	default:	  return QPoint(H.x(), H.y() - 1);
	}
}

QPoint AI::departFood(QPoint H)
{ 
	  QPoint pUp(H.x(), H.y() + 1);
	  QPoint pDown(H.x(), H.y() - 1);
	  QPoint pRight(H.x() + 1, H.y());
	  QPoint pLeft(H.x() - 1, H.y());

	  QPoint R = (L <= N * N / 2) ? F : QPoint(Sn[L - 1].X_NOW, Sn[L - 1].Y_NOW);
	  direction v[4] = { V_RIGHT }; 
	  dirArray(R, H, v);

	  if (safeRandStep(H, v[0]))
	  {
		  return dir2p(H, v[0]);
	  }
	  else if (safeRandStep(H, v[1]))
	  {
		  return dir2p(H, v[1]);
	  }
	  else if (safeRandStep(H, v[2]))
	  {
		  return dir2p(H, v[2]);
	  }
	  else
	  {
		  return dir2p(H, v[3]);
	  }
}

QPoint AI::amoveSnake(QPoint H, QPoint F)
{ 

	QPoint *pn = (QPoint *)malloc(sizeof(QPoint)* (N * N - 2));
	memset(pn, 0, sizeof(pn));
	int pathLength = findPath(H, F, &pn[0]);

	if (pathLength > 0)
	{
		if (virtualSnake(pn, pathLength))
		{
			return pn[1];
		}
		else
		{
			return departFood(H);
		}
	}
	else
	{
		return departFood(H);
	} 
	 
}