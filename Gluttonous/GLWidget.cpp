#include "stdafx.h" 

#include<QVector3D>
#include<QDebug>
#include<QPoint>
#include<qmath.h>
#include<QKeyEvent> 
#include "GLWidget.h"  

//#include<time.h>

GLWidget::GLWidget(QWidget *parent) :QOpenGLWidget(parent)
{ 
	Auto = false;
	GameOver = true;
	Pause = true; 
	InitVar();
}


void GLWidget::initializeGL()
{	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	setFocusPolicy(Qt::StrongFocus);
}

void GLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
}

void GLWidget::paintGL()
{
	if (!GameOver){

		if (!Pause)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			DrawBlock(F, C_RED);    //Draw food. 
			DrawSnake();
		}

	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT);
		sf->KillSnake();

		if (!Pause)
		{
			Pause = true;
			if (gf->MissionImpossible(L))
			{
				DrawCup();
				emit Winner();
			}
			else
			{
				DrawLose();
				emit Wasted();
			}
		}

	}
}

direction GLWidget::curDir(QPoint H, QPoint R)
{
	QPoint d = H - R;

	if (d == QPoint(1, 0))
	{
		return V_RIGHT;
	}
	else if (d == QPoint(-1, 0))
	{
		return V_LEFT;
	}
	else if (d == QPoint(0, 1))
	{
		return V_UP;
	}
	else
	{
		return V_DOWN;
	}
 
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Space)
	{
		GameOver ? Start() : Resume();
	}
	else if (event->key() == Qt::Key_F1)
	{
		Auto = !Auto;
		if (!Auto) v = curDir(H, QPoint(Sn[1].X_NOW, Sn[1].Y_NOW));
		emit Mode(Auto);
	}

	if (!Pause)
	{
		switch (event->key())
		{

		case Qt::Key_Left:  Left();  break;
		case Qt::Key_Right: Right(); break;
		case Qt::Key_Up:    Up();    break;
		case Qt::Key_Down:  Down();  break;

		default: break;
		}
	}
}

// protected above

void GLWidget::Resume(void)
{
	Pause = !Pause; 
	emit Pause ? PauseGame() : ResumeGame();
}

void GLWidget::Start(void)
{
	GameOver = false;
	Pause = false;
	InitVar();
	emit GameStart();
}

void GLWidget::Update(void)
{ 
	Auto ? H = af->amoveSnake(H, F) : gf->Direction(v);

	sf->SnakeMove(H); 
	sf->Death();
	EatFood();
	update();
}

void GLWidget::Right(void)
{
	bool RightPermitted = !((Sn[0].X_NOW + 1 == Sn[1].X_NOW) && (Sn[0].Y_NOW == Sn[1].Y_NOW));
	if ((v != V_LEFT) && RightPermitted) v = V_RIGHT;
}

void GLWidget::Up(void)
{
	bool UpPermitted = !((Sn[0].X_NOW == Sn[1].X_NOW) && (Sn[0].Y_NOW + 1 == Sn[1].Y_NOW));
	if ((v != V_DOWN) && UpPermitted) v = V_UP;
}

void GLWidget::Left(void)
{
	bool LeftPermitted = !((Sn[0].X_NOW - 1 == Sn[1].X_NOW) && (Sn[0].Y_NOW == Sn[1].Y_NOW));
	if ((v != V_RIGHT) && LeftPermitted) v = V_LEFT;
}

void GLWidget::Down(void)
{
	bool DownPermitted = !((Sn[0].X_NOW == Sn[1].X_NOW) && (Sn[0].Y_NOW - 1 == Sn[1].Y_NOW));
	if ((v != V_UP) && DownPermitted) v = V_DOWN;
}

void GLWidget::EatFood(void){

	if (H == F)
	{
		sf->Grow(); 
		emit UpdLength(L);
		
		if (gf->MissionImpossible(L)) 
		{ 
			GameOver = true;
		}
		else
		{
			gf->CreateFood();
		}
 
	}

}

// signals above


void GLWidget::InitVar(void)
{ 
	gf->CreateHead();
	v = gf->InitDir(H);
	sf->NewSnake(H);
	gf->CreateFood(); 
}


void GLWidget::DrawBlock(QPoint p, colour c)
{
	float h = 1.0f / N;
	float d = 0.125 * h;
	float cl[3] = { 0.0 };

	switch (c)
	{
	case C_WHITE:
		cl[0] = 1.0;
		cl[1] = 1.0;
		cl[2] = 1.0;
		break;

	case C_RED: 
		cl[0] = 1.0;
		cl[1] = 0.0;
		cl[2] = 0.0;
		break;

	case C_GREEN:
		cl[0] = 0.0;
		cl[1] = 1.0;
		cl[2] = 0.0;
		break;

	case C_BLUE:
		cl[0] = 0.0;
		cl[1] = 0.0;
		cl[2] = 1.0;
		break;

	case C_YELLOW:
		cl[0] = 1.0;
		cl[1] = 1.0;
		cl[2] = 0.0;
		break;

	case C_PURPLE:
		cl[0] = 1.0;
		cl[1] = 0.0;
		cl[2] = 1.0;
		break;

	case C_SKYBLUE:
		cl[0] = 0.0;
		cl[1] = 1.0;
		cl[2] = 1.0;
		break;

	default:
		break;
	}

	glBegin(GL_QUADS);
	glColor3f(cl[0], cl[1], cl[2]); glVertex2f(p.x() * h + d, p.y() * h + d);
	glColor3f(cl[0], cl[1], cl[2]); glVertex2f(p.x() * h + d, (p.y() + 1) * h - d);
	glColor3f(cl[0], cl[1], cl[2]); glVertex2f((p.x() + 1) * h - d, (p.y() + 1) * h - d);
	glColor3f(cl[0], cl[1], cl[2]); glVertex2f((p.x() + 1) * h - d, p.y() * h + d);
	glEnd();

}
 
void GLWidget::LinkBlocks(int i)
{
	float h = 1.0f / N;
	float d = 0.125 * h;

	QPoint p0(Sn[i].X_NOW, Sn[i].Y_NOW);
	QPoint p1(Sn[i + 1].X_NOW, Sn[i + 1].Y_NOW);
	direction v = curDir(p0, p1);  // p0 is on the v direction of p1

	glBegin(GL_QUADS);

	switch (v)
	{
	case V_RIGHT: 
		glColor3f(0.0, 1.0, 0.0); glVertex2f(p0.x() * h - d, p0.y() * h + d);
		glColor3f(0.0, 1.0, 0.0); glVertex2f(p0.x() * h - d, (p0.y() + 1) * h - d);
		glColor3f(0.0, 1.0, 0.0); glVertex2f(p0.x() * h + d, (p0.y() + 1) * h - d);
		glColor3f(0.0, 1.0, 0.0); glVertex2f(p0.x() * h + d, p0.y() * h + d);
		break;

	case V_LEFT:
		glColor3f(0.0, 1.0, 0.0); glVertex2f(p1.x() * h - d, p1.y() * h + d);
		glColor3f(0.0, 1.0, 0.0); glVertex2f(p1.x() * h - d, (p1.y() + 1) * h - d);
		glColor3f(0.0, 1.0, 0.0); glVertex2f(p1.x() * h + d, (p1.y() + 1) * h - d);
		glColor3f(0.0, 1.0, 0.0); glVertex2f(p1.x() * h + d, p1.y() * h + d);
		break; 

	case V_UP:
		glColor3f(0.0, 1.0, 0.0); glVertex2f(p0.x() * h + d, p0.y() * h - d);
		glColor3f(0.0, 1.0, 0.0); glVertex2f(p0.x() * h + d, p0.y() * h + d);
		glColor3f(0.0, 1.0, 0.0); glVertex2f((p0.x() + 1) * h - d, p0.y() * h + d);
		glColor3f(0.0, 1.0, 0.0); glVertex2f((p0.x() + 1) * h - d, p0.y() * h - d);
		break;
	
	default:
		glColor3f(0.0, 1.0, 0.0); glVertex2f(p1.x() * h + d, p1.y() * h - d);
		glColor3f(0.0, 1.0, 0.0); glVertex2f(p1.x() * h + d, p1.y() * h + d);
		glColor3f(0.0, 1.0, 0.0); glVertex2f((p1.x() + 1) * h - d, p1.y() * h + d);
		glColor3f(0.0, 1.0, 0.0); glVertex2f((p1.x() + 1) * h - d, p1.y() * h - d);
		break;
	}

	glEnd();
}

void GLWidget::DrawSnake(void)
{
	int i;
	for (i = 0; i <= L - 1; i++)
	{
		colour c = C_GREEN;
		if (i == 0) c = C_YELLOW;
		if (i == L - 1) c = C_SKYBLUE;

		DrawBlock(QPoint(Sn[i].X_NOW, Sn[i].Y_NOW), c);
	}

	for (i = 0; i <= L - 2; i++)
	{
		LinkBlocks(i);
	}
}

void GLWidget::DrawCup(void)
{
	int i, j;

	int cup[N][N] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	// 15
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },	// 14
		{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 },	// 13
		{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 },	// 12
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1 },	// 11
		{ 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0 },	// 10
		{ 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0 },	// 9
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },	// 8
		{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },	// 7
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },	// 6
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },	// 5
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },	// 4
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },	// 3
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },	// 2
		{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },	// 1
		{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 }  // 0
	};

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (cup[i][j])
			{
				DrawBlock(QPoint(j, N - i - 1), C_YELLOW);
			}
		}
	}
}

void GLWidget::DrawLose(void)
{
	int i, j;
	int Lose[N][N] =
	{
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },	// 15
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },	// 14
		{ 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0 },	// 13
		{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },	// 12
		{ 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },	// 11
		{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0 },	// 10
		{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },	// 9
		{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },	// 8
		{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },	// 7
		{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },	// 6
		{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0 },	// 5
		{ 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },	// 4
		{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },	// 3
		{ 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0 },	// 2
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },	// 1
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 }  // 0
	};

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (Lose[i][j])
			{
				DrawBlock(QPoint(j, N - i - 1), C_PURPLE);
			}
		}
	}

}


