#include "stdafx.h"
#include "BFS.h"
#include "Hamilton.h"

BFS::BFS()
{
	sNum = 1;
	eNum = 0;
	memset(Steps, 0, sizeof(Steps));
	memset(Edges, 0, sizeof(Edges));

	Steps[0].coord = H; 
	 
}


BFS::~BFS()
{
}

BOOL BFS::onSnake(int x, int y) 
{
	for (int i = 1; i <= L - 2; i++)
	{
		if (QPoint(x, y) == Sn[i].NOW) return TRUE;
	}
	return FALSE;
}

void BFS::initMap() 
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			map[i][j] = (int)onSnake(i, j); 
		}
	} 
}

bool BFS::inMap(QPoint p)
{
	return !(0 > p.x() || p.x() > N - 1 || 0 > p.y() || p.y() > N - 1);
}

int BFS::isTail()
{
	QPoint T = Sn[L - 1].NOW;
	for (int i = 1; i < sNum; i++)
	{
		if (Steps[i].coord == T) return i; 
	}
	return 0;
}

bool BFS::createGraph(QPoint *vH) 
{
	initMap();

	for (int i = 0; i < sNum; i++)
	{
		searchNeighbor(i);
	}

	int Tid = isTail();
	Hamilton *hf = new Hamilton();
	int nextStep = hf->existPath(Edges, sNum, eNum, Tid);

	if (nextStep > 0)
	{
		*vH = Steps[nextStep].coord;
		return true;
	}
	else
	{
		return false;
	}

}

bool BFS::inArray(vertex v, QPoint p)
{
	for (int i = 0; i < v.ajNum; i++)
	{
		if (Steps[v.ajp[i]].coord == p)
		{
			return true;
		}
	}

	return false;
}

int BFS::unVisited(vertex p, QPoint *neighbor)
{
	int k = 0;

	QPoint adjacent[4] =
	{
		p.coord + QPoint(0, 1),
		p.coord - QPoint(0, 1),
		p.coord + QPoint(1, 0),
		p.coord - QPoint(1, 0)
	};

	for (int i = 0; i < 4; i++)
	{
		if (!inArray(p, adjacent[i]))
		{
			*(neighbor + k) = adjacent[i];
			k++;
		}
	}

	return k;
}

bool BFS::isChild(QPoint np)
{
	return inMap(np) && !map[np.x()][np.y()];
}

int BFS::Visited(QPoint p)
{
	for (int i = sNum - 1; i > 0; i--)
	{
		if (Steps[i].coord == p) return i;
	} 
	return 0;
}

bool BFS::searchNeighbor(int j)
{
	int pNum = 0;
	QPoint Neighbors[4] = { QPoint(0, 0) }; 
	int k = unVisited(Steps[j], &Neighbors[0]);

	for (int i = 0; i < k; i++)
	{
		if (isChild(Neighbors[i]))
		{
			int n = Visited(Neighbors[i]);
			if (n > 0)
			{
				Steps[n].ajp[Steps[n].ajNum] = j;
				Steps[n].ajNum++;
				Steps[j].ajp[Steps[j].ajNum] = n; 
				Edges[eNum] = QPoint(j, n);
			}
			else
			{  
				Steps[sNum + pNum].coord = Neighbors[i];
				Steps[sNum + pNum].deep = Steps[j].deep + 1;
				Steps[sNum + pNum].ajp[Steps[sNum + pNum].ajNum] = j;
				Steps[sNum + pNum].ajNum++; 
				Steps[j].ajp[Steps[j].ajNum] = sNum + pNum;  
				Edges[eNum] = QPoint(j, sNum + pNum);
				pNum++;
			}

			Steps[j].ajNum++; 
			eNum++;
		}
	}

	sNum += pNum; 
	return (pNum > 0);
}