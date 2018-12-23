#ifndef GLUTTONOUS_H
#define GLUTTONOUS_H

#include <QtWidgets/QMainWindow>
#include<QTimer> 

class Gluttonous : public QMainWindow
{
	Q_OBJECT

public:
	Gluttonous(QWidget * = 0);
	~Gluttonous();

	QWidget *centralWidget;
	QLabel *Score;
	QOpenGLWidget *openGLWidget;
	QLabel *Length;
	QLabel *LengthLabel;
	QLabel *ScoreLabel;
	QLabel *MessageLabel;
	QLabel *AutoLabel;
	QTimer *refresh;

private: 
	void setupUi(QMainWindow *);
	void retranslateUi(QMainWindow *);

public slots:

	void PrintScore(int);
	void PrintLength(int);
	void ResetGame(void);
	void RestartGame(void);
	void GameResume(void);
	void GamePause(void);
	void Win(void);
	void ModeChange(bool);
};

#endif // GLUTTONOUS_H
