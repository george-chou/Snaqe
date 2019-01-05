#include <QtWidgets>
#define N 8
#define N_MAX 16

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
	V_RIGHT = 1,
	V_LEFT = -1,
	V_UP = 2,
	V_DOWN = -2
};

struct body
{ 
	QPoint NOW;
	QPoint OLD;
};

extern int  v, L;
extern bool GameOver, Pause, Auto;
extern body Sn[N * N];
extern QPoint H, F; 
 
extern int max(int, int);
extern int max_4(int, int, int, int);
extern int Abs(int);
