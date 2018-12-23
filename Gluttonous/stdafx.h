#include <QtWidgets>
#define N 16

enum colour
{
	C_RED = 0,
	C_WHITE,
	C_GREEN,
	C_BLUE,
	C_YELLOW,
	C_PURPLE,
	C_SKYBLUE
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
extern bool GameOver, Pause, Auto;
extern body Sn[N * N];
extern QPoint H, F; 

//extern 	int pL;
//extern QPoint pA[N * N - 2];

extern int max(int, int);
extern int max_4(int, int, int, int);
extern int Abs(int);
