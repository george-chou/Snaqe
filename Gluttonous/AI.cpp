#include "stdafx.h"
#include "AI.h"
#include "astar.h"
#include "time.h"
 
#include "BFS.h"

AI::AI()
{
}


AI::~AI()
{
}

bool AI::diag(QPoint p1, QPoint p2)
{
	int dx = (p1 - p2).x();
	int dy = (p1 - p2).y();

	return (Abs(dx) == 1) && (Abs(dy) == 1);
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
		maze[Sn[i].NOW.x() + 1][Sn[i].NOW.y() + 1] = 1;
	}

	return maze;
}

bool AI::Bound(QPoint p)
{
	return (0 > p.x() || p.x() > N - 1 || 0 > p.y() || p.y() > N - 1);
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
			else  if (diag(cp, pA[i - 1])) 
			{
				*(pA + i) = noBend(pA, cp, i, FALSE);
				*(pA + i + 1) = cp;

				//if (!neighbor(pA[i], pA[i + 1]))
				//{
				//	bool ntl = true;
				//}

				i += 2;   
			}
			//else 
			//{
			//	bool ntl = true;
			//}
		}
		else 
		{
			*pA = cp;
			i++;
		} 
	}
	 
	return i;
}


direction  AI::vDir(QPoint H, QPoint R)  // H is on the vDir of R
{
	QPoint d = H - R;

	if (d == QPoint(1, 0))
	{
		return  V_RIGHT;
	}
	else if (d == QPoint(-1, 0))
	{
		return V_LEFT;
	}
	else if (d == QPoint(0, 1))
	{
		return V_UP;
	}
	else if (d == QPoint(0, -1))
	{
		return V_DOWN;
	}
	else
	{
		return V_RIGHT;
	}
}


bool AI::neighbor(QPoint p1, QPoint p2)
{
	int dx = (p1 - p2).x();
	int dy = (p1 - p2).y();

	return ((Abs(dx) + Abs(dy)) == 1);
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

bool AI::virtualSnake(QPoint *s, int n)	//	放一条虚拟蛇去吃食物并预测吃到后能否找到尾巴
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
				p[i] = Sn[i - n + 1].NOW;
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
		if (Sn[i].NOW == p) return true;
	}

	return false;
}

bool AI::Border(QPoint p)
{
	return Bound(p) || (p == F);
}

int AI::bFilter(QPoint d[], QPoint *b)	// 筛选掉因触碰边界或咬到自身的方向选项
{
	int k = 0; 

	for (int i = 0; i < 4; i++)
	{
		if (!Bit(d[i]) && !Border(d[i]))
		{
			*(b + k) = d[i];
			k++;
			if (k > 2) break; 
		}
	}

	return k;
}

bool AI::canFindTail(QPoint bp)	//	判断蛇走到该点时还能否找得到尾巴
{
	QPoint *p = (QPoint *)malloc(sizeof(QPoint)* L);

	for (int i = 1; i <= L - 1; i++)
	{ 
		p[i] = Sn[i - 1].NOW;
	}
	p[0] = bp;

	return findTail(p, L - 1);
}


int AI::tFilter(QPoint b[], int n, QPoint *t)	//	筛选掉走后找不到尾巴的方向选项
{ 
	int k = 0;

	for (int i = 0; i < n; i++)
	{
		if (canFindTail(b[i]))
		{
			*(t + k) = b[i];
			k++;
			if (k > 2) break;
		}
	}

	return k;
}
 
QPoint AI::safeRandStep(QPoint H)	//	寻找安全随机步，这里很关键，尤其是对找不到安全随机步时的决策
{ 
	QPoint v[4] = { QPoint(0, 0) };
	QPoint T = Sn[L - 1].NOW;

	if (dirArray(T, H, v) != CENTER) 
	{
		QPoint *b = (QPoint *)malloc(sizeof(QPoint)* 3);
		int bn = bFilter(v, b);

		if (bn == 1)
		{
			return b[0];
		}
		else if (bn > 1)
		{

			QPoint *t = (QPoint *)malloc(sizeof(QPoint)* bn);
			int tn = tFilter(b, bn, t);

			if (tn == 0)
			{
				return b[0];
			}
			else if (tn >= 1)
			{ 
				if (L > N * N / 2)
				{
					QPoint vH(0, 0);
					BFS *bf = new BFS();
					if (bf->createGraph(&vH)) return vH; 
				}
				return t[0];
			}
			else
			{
				return QPoint(-1, -1);
			}

		}
		else
		{
			return QPoint(-1, -1);
		}

	}
	else
	{
		return QPoint(-1, -1);
	}
}

Towards AI::dirArray(QPoint F, QPoint H, QPoint *v)	//	获取远离食物的方向
{
	BOOL i = 0;
	int x = (H - F).x();
	int y = (H - F).y();

	if (0 < y && y < x)
	{
		*(v + 0) = dir2p(H, V_RIGHT);
		*(v + 1) = dir2p(H, V_UP);
		*(v + 2) = dir2p(H, V_DOWN);
		*(v + 3) = dir2p(H, V_LEFT);
		return E2NE;
	}
	else if (0 < x && x < y)
	{
		*(v + 0) = dir2p(H, V_UP);
		*(v + 1) = dir2p(H, V_RIGHT);
		*(v + 2) = dir2p(H, V_LEFT);
		*(v + 3) = dir2p(H, V_DOWN);
		return NE2N;
	}
	else if (0 < -x && -x < y)
	{
		*(v + 0) = dir2p(H, V_UP);
		*(v + 1) = dir2p(H, V_LEFT);
		*(v + 2) = dir2p(H, V_RIGHT);
		*(v + 3) = dir2p(H, V_DOWN);
		return N2NW;
	}
	else if (0 < y && y < -x)
	{
		*(v + 0) = dir2p(H, V_LEFT);
		*(v + 1) = dir2p(H, V_UP);
		*(v + 2) = dir2p(H, V_DOWN);
		*(v + 3) = dir2p(H, V_RIGHT);
		return NW2W;
	}
	else if (x < y && y < 0)
	{
		*(v + 0) = dir2p(H, V_LEFT);
		*(v + 1) = dir2p(H, V_DOWN);
		*(v + 2) = dir2p(H, V_UP);
		*(v + 3) = dir2p(H, V_RIGHT);
		return W2SW;
	}
	else if (y < x && x < 0)
	{
		*(v + 0) = dir2p(H, V_DOWN);
		*(v + 1) = dir2p(H, V_LEFT);
		*(v + 2) = dir2p(H, V_RIGHT);
		*(v + 3) = dir2p(H, V_UP);
		return SW2S;
	}
	else if (y < -x && -x < 0)
	{
		*(v + 0) = dir2p(H, V_DOWN);
		*(v + 1) = dir2p(H, V_RIGHT);
		*(v + 2) = dir2p(H, V_LEFT);
		*(v + 3) = dir2p(H, V_UP);
		return S2SE;
	}
	else if (-x < y && y < 0)
	{
		*(v + 0) = dir2p(H, V_RIGHT);
		*(v + 1) = dir2p(H, V_DOWN);
		*(v + 2) = dir2p(H, V_UP);
		*(v + 3) = dir2p(H, V_LEFT);
		return SE2E;
	}

	else if (y == 0 && 0 < x)
	{
		i = randBOOL();
		*(v + 0) = dir2p(H, V_RIGHT);
		*(v + 1 + i) = dir2p(H, V_UP);
		*(v + 1 + !i) = dir2p(H, V_DOWN);
		*(v + 3) = dir2p(H, V_LEFT);
		return EAST;
	}
	else if (y == x && x > 0)
	{
		i = randBOOL();
		*(v + i) = dir2p(H, V_RIGHT);
		*(v + !i) = dir2p(H, V_UP);
		i = randBOOL();
		*(v + 2 + i) = dir2p(H, V_LEFT);
		*(v + 2 + !i) = dir2p(H, V_DOWN);
		return NE;
	}
	else if (y > 0 && 0 == x)
	{
		i = randBOOL();
		*(v + 0) = dir2p(H, V_UP);
		*(v + 1 + i) = dir2p(H, V_RIGHT);
		*(v + 1 + !i) = dir2p(H, V_LEFT);
		*(v + 3) = dir2p(H, V_DOWN);
		return NORTH;
	}
	else if (0 < y && y == -x)
	{
		i = randBOOL();
		*(v + i) = dir2p(H, V_LEFT);
		*(v + !i) = dir2p(H, V_UP);
		i = randBOOL();
		*(v + 2 + i) = dir2p(H, V_RIGHT);
		*(v + 2 + !i) = dir2p(H, V_DOWN);
		return NW;
	}
	else if (y == 0 && 0 > x)
	{
		i = randBOOL();
		*(v + 0) = dir2p(H, V_LEFT);
		*(v + 1 + i) = dir2p(H, V_UP);
		*(v + 1 + !i) = dir2p(H, V_DOWN);
		*(v + 3) = dir2p(H, V_RIGHT);
		return WEST;
	}
	else if (y == x && x < 0)
	{
		i = randBOOL();
		*(v + i) = dir2p(H, V_LEFT);
		*(v + !i) = dir2p(H, V_DOWN);
		i = randBOOL();
		*(v + 2 + i) = dir2p(H, V_RIGHT);
		*(v + 2 + !i) = dir2p(H, V_UP);
		return SW;
	}
	else if (x == 0 && 0 > y)
	{
		i = randBOOL();
		*(v + 0) = dir2p(H, V_DOWN);
		*(v + 1 + i) = dir2p(H, V_LEFT);
		*(v + 1 + !i) = dir2p(H, V_RIGHT);
		*(v + 3) = dir2p(H, V_UP);
		return SOUTH;
	}
	else if (0 > y && y == -x)
	{
		i = randBOOL();
		*(v + i) = dir2p(H, V_RIGHT);
		*(v + !i) = dir2p(H, V_DOWN);
		i = randBOOL();
		*(v + 2 + i) = dir2p(H, V_LEFT);
		*(v + 2 + !i) = dir2p(H, V_UP);
		return SE;
	}
	else  // impossible
	{
		return CENTER;
	}

}

BOOL AI::randBOOL(void)
{
	srand(time(NULL));
	return (BOOL)(rand() % 2);
}

QPoint AI::dir2p(QPoint H, direction v)	//	已知蛇头及朝向预测下一步蛇头位置
{
	switch (v)
	{
	case V_RIGHT:	return QPoint(H.x() + 1, H.y());
	case V_LEFT:	return QPoint(H.x() - 1, H.y());
	case V_UP:		return QPoint(H.x(), H.y() + 1);
	default:		return QPoint(H.x(), H.y() - 1); 
	}
}

QPoint AI::compass(QPoint H, QPoint F)
{
	int x = (F - H).x();
	int y = (F - H).y();

	if (x > 0 && y > 0)
	{
		return QPoint(H.x() + 1, H.y() + 1);
	}
	else if (x > 0 && y < 0)
	{
		return  QPoint(H.x() + 1, H.y() - 1);
	}
	else if (x < 0 && y > 0)
	{
		return QPoint(H.x() - 1, H.y() + 1);
	}
	else if (x < 0 && y < 0)
	{
		return QPoint(H.x() - 1, H.y() - 1);
	}
	else
	{
		return H;
	}

}

bool AI::boundFood(QPoint F)
{
	return Bound(dir2p(F, V_RIGHT)) || Bound(dir2p(F, V_LEFT)) || Bound(dir2p(F, V_UP)) || Bound(dir2p(F, V_DOWN));
}


QPoint AI::noBend(QPoint pA[], QPoint cp, int i, BOOL vNeck) 
{

	QPoint neck = (i == 1) ? Sn[1 - vNeck].NOW : pA[i - 2];
	 
	direction v = vDir(pA[i - 1], neck);
	QPoint pi = dir2p(pA[i - 1], v);

	if (neighbor(cp, pi))
	{
		return pi;
	}
	else
	{
		QPoint pi1(cp.x(), pA[i - 1].y());
		QPoint pi2(pA[i - 1].x(), cp.y());
		return (neck != pi1) ? pi1 : pi2;
	}

}

int AI::canVeer(QPoint vH, QPoint F, QPoint *pB)
{
	int i = 0;
	Astar astar; 

	Point start(vH.x() + 1, vH.y() + 1);
	Point end(F.x() + 1, F.y() + 1);

	vector<vector<int>> maze = initMaze(Sn); 
	maze[H.x() + 1][H.y() + 1] = 1;
	maze[Sn[L - 1].NOW.x() + 1][Sn[L - 1].NOW.y() + 1] = 0;

	astar.InitAstar(maze);
	list<Point *> path = astar.GetPath(start, end, false);

	*pB = H;
	QPoint *pA = pB + 1;

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
			else  if (diag(cp, pA[i - 1]))
			{
				*(pA + i) = noBend(pA, cp, i, TRUE);
				*(pA + i + 1) = cp;

				//if (!neighbor(pA[i], pA[i + 1]))
				//{
				//	bool ntl = true;
				//}

				i += 2;
			}
			//else
			//{
			//	bool ntl = true;
			//}
		}
		else
		{
			*pA = cp;
			i++;
		}
	}

	return i;
}

bool AI::mayEndlessLoop(body *Sn, QPoint *p)	//	判断是否可能出现绕边界死循环情形
{
	QPoint H = Sn[0].NOW;
	QPoint neck = Sn[1].NOW;
	direction v = vDir(H, neck);
	QPoint pi = dir2p(H, v);
	*p = pi;

	return Bound(dir2p(F, v)) && Bound(dir2p(pi, v)) && !Bound(pi) && pi != F && !Bit(pi);
}

QPoint AI::avoidLoop(QPoint pi)	//	避免绕边界死循环的决策函数
{
	QPoint pV = compass(H, F);
	if (!Bit(H + pV - pi))
	{
		QPoint *pa = new QPoint[N * N - 2];
		int pLength = canVeer(pi, F, &pa[0]);
		if (pLength > 1)
		{
			if (virtualSnake(pa, pLength + 1))
			{
				return pi;
			}
			else
			{
				pLength = canVeer(H + pV - pi, F, &pa[0]);
				if (pLength > 1)
				{
					return virtualSnake(pa, pLength + 1) ? (H + pV - pi) : pi;
				}
				else
				{
					return pi;
				}
			}
		}
		else
		{
			return (H + pV - pi);
		}
	}
	else
	{
		return pi;
	}
}

bool AI::tryfillMode(int L)	//	判断是否进入哈密顿路径模式
{
	if (L < N * (N - 2)) return false;
	if (!canFindTail(H)) return false;

	QPoint H = Sn[0].NOW;
	QPoint neck = Sn[1].NOW;
	direction forward = vDir(H, neck);
	QPoint pH = dir2p(H, forward);

	if (Bit(pH) || Bound(pH)) return false;

	QPoint turnLeft(0, 0);
	QPoint turnRight(0, 0);

	switch (forward)
	{
	case V_RIGHT:
	case V_LEFT:
		turnLeft = dir2p(H, V_UP);
		turnRight = dir2p(H, V_DOWN);
		return (!Bit(turnLeft) && !Bound(turnLeft)) || (!Bit(turnRight) && !Bound(turnRight));

	default:
		turnLeft = dir2p(H, V_RIGHT);
		turnRight = dir2p(H, V_LEFT);
		return (!Bit(turnLeft) && !Bound(turnLeft)) || (!Bit(turnRight) && !Bound(turnRight));
	}
}

QPoint AI::amoveSnake(QPoint H, QPoint F)
{
	if (tryfillMode(L))	//	如果蛇长该进入哈密顿通路模式
	{
		QPoint vH(0, 0);
		BFS *bf = new BFS();
		if (bf->createGraph(&vH)) return vH;	//	如果存在哈密顿通路则返回哈密顿通路的下一步
	}

	QPoint *pn = new QPoint[N * N - 2];
	int pLength = findPath(H, F, &pn[0]);	//	寻找吃食物的路径
	if (pLength > 0)	//	如果找得到吃食物的路径
	{
		QPoint pi(0, 0);
		if (mayEndlessLoop(Sn, &pi))
		{
			return avoidLoop(pi);
		}
		else
		{
			return virtualSnake(pn, pLength) ? pn[1] : safeRandStep(H);	//	如果进不到绕边界死循环情形，则能吃食物就吃，不能就走安全随即步
		} 
	}
	else
	{
		return safeRandStep(H);	//	如果找不到吃食物的通路则走一步安全的随机步
	}

}