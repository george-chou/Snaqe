#ifndef GLWIDGET_H
#define GLWIDGET_H

//#include <GL/glut.h>
#include <QtWidgets/QOpenGLWidget>
#include "snake.h"
#include "game.h"

class QVector3D;
class GLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:

	GLWidget(QWidget *parent = 0);

private:

	snake *sf;
	game *gf;

	void InitVar(void); 
	void DrawSnake(void); 
	void EatFood(void);
	void DrawFood(void);
	void DrawBlock(int x, int y, float c);
	

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	void keyPressEvent(QKeyEvent *event);

signals:
	
	void UpdLength(int);
	void Wasted(void);
	void PauseGame(void);
	void ResumeGame(void);
	void GameStart(void);
	void Winner(void);

public slots:

	void Right(void);
	void Left(void);
	void Up(void);
	void Down(void);
	void Resume(void); 
	void Start(void); 
	void Update(void);
};

#endif // GLWIDGET_H

