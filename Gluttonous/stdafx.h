#include <QtWidgets>
#define N 32

enum colour
{
	C_RED = 0,
	C_WHITE
};

enum direction
{
	V_RIGHT = 0,
	V_LEFT,
	V_UP,
	V_DOWN
};

struct body{
	int X_OLD;
	int Y_OLD;
	int X_NOW;
	int Y_NOW;
};

extern int  v, L;
extern bool GameOver, Pause;
extern body Sn[N * N];
extern QPoint H, F; 

extern int max(int x, int y);
extern int max_4(int a, int b, int c, int d);
