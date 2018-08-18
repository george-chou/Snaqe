#ifndef GREEDY_H
#define GREEDY_H

#include <QtWidgets/QMainWindow>
#include<QTimer>
#include "ui_greedy.h"


class Greedy : public QMainWindow
{
	Q_OBJECT

public:
	Greedy(QWidget *parent = 0);
	~Greedy();

	QWidget *centralWidget;
	QLabel *Score;
	QOpenGLWidget *openGLWidget;
	QLabel *Length;
	QLabel *LengthLabel;
	QLabel *ScoreLabel;
	QLabel *MessageLabel;
	QTimer *refresh;

private:
	Ui::greedyClass ui;

	void setupUi(QMainWindow *MainWindow);
	void retranslateUi(QMainWindow *MainWindow);

public slots:

	void PrintScore(int);
	void PrintLength(int);
	void ResetGame(void);
	void RestartGame(void);
	void GameResume(void);
	void GamePause(void);
	void Win(void);

};

#endif // GREEDY_H
