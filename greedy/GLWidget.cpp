//#include<gl/glut.h>
#include<QVector3D>
#include<QDebug>
#include<QPoint>
#include<qmath.h>
#include<QKeyEvent> 

#include "global.h" 
#include "GLWidget.h"  

 

GLWidget::GLWidget(QWidget *parent) :QOpenGLWidget(parent)
{

	N = Res;
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

		if (!Pause){
			glClear(GL_COLOR_BUFFER_BIT);
			DrawBlock(F_x, F_y, C_RED);    //Draw food. //DrawFood();
			DrawSnake();
		}

	}
	else{

		glClear(GL_COLOR_BUFFER_BIT);
		sf->KillSnake();

		if (!Pause){
			Pause = true;
			emit (Snake_Length >= N * N) ? Winner() : Wasted();
		}

	}
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Space){
		GameOver ? Start() : Resume();
	}

	if (!Pause){
		switch (event->key()){

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
	gf->Direction(v);    //Update orientation
	sf->SnakeMove();
	EatFood();
	sf->Death();
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

	while (L_x == F_x && L_y == F_y){
		sf->Grow(); 
		emit UpdLength(Snake_Length);
		if (gf->MissionImpossible(Snake_Length)) {
			break;
		}
		else
		{
			gf->CreateFood();
		}
	}

}

// signals above


void GLWidget::InitVar(void){

	gf->RandCoord(&L_x, &L_y);
	v = gf->InitDir(L_x, L_y);
	sf->NewSnake(L_x, L_y);
	gf->CreateFood();

}


void GLWidget::DrawBlock(int x, int y, float c)
{
	float h = 1.0f / N;
	float d = 0.125 * h;

	glBegin(GL_QUADS);
	glColor3f(1.0, c, c); glVertex2f(x * h + d, y * h + d);
	glColor3f(1.0, c, c); glVertex2f(x * h + d, (y + 1) * h - d);
	glColor3f(1.0, c, c); glVertex2f((x + 1) * h - d, (y + 1) * h - d);
	glColor3f(1.0, c, c); glVertex2f((x + 1) * h - d, y * h + d);
	glEnd();

}
 

void GLWidget::DrawSnake(void)
{
	for (int i = 0; i <= Snake_Length - 1; i++){
		DrawBlock(Sn[i].X_NOW, Sn[i].Y_NOW, C_WHITE);
	}
}


