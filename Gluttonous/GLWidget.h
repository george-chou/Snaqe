#ifndef GLWIDGET_H
#define GLWIDGET_H
 
#include <QtWidgets/QOpenGLWidget>
#include "snake.h"
#include "game.h"
#include "AI.h"

class QVector3D;
class GLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:

	GLWidget(QWidget * = 0);

private:

	snake *sf;
	game *gf;
	AI *af;

	void InitVar(void); 
	void DrawSnake(void); 
	void EatFood(void);
	void DrawFood(void);
	void DrawBlock(QPoint, colour);
	direction curDir(QPoint, QPoint);
	void  LinkBlocks(int);

	void DrawCup(void);
	void DrawLose(void);

	int index;

protected:
	void initializeGL();
	void resizeGL(int, int);
	void paintGL();
	void keyPressEvent(QKeyEvent *);

signals:
	
	void UpdLength(int);
	void Wasted(void);
	void PauseGame(void);
	void ResumeGame(void);
	void GameStart(void);
	void Winner(void);
	void Mode(bool);

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

