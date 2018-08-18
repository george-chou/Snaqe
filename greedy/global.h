#define C_WHITE 1.0
#define C_RED 0.0

#define V_RIGHT 0
#define V_LEFT 1
#define V_UP 2
#define V_DOWN 3 

#define Res 32


struct body{
	int X_OLD;
	int Y_OLD;
	int X_NOW;
	int Y_NOW;
};

extern int  L_x, L_y, F_x, F_y, v, N, Snake_Length;
extern bool GameOver, Pause;
extern body Sn[Res * Res];

extern int max(int x, int y);
extern int max_4(int a, int b, int c, int d);
 