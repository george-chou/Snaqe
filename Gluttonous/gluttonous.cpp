#include "stdafx.h"
#include "gluttonous.h"
#include "GLWidget.h"

Gluttonous::Gluttonous(QWidget *parent)
	: QMainWindow(parent)
{ 
	setupUi(this);
}

Gluttonous::~Gluttonous()
{

}


void Gluttonous::setupUi(QMainWindow *greedyClass)
{
	if (greedyClass->objectName().isEmpty())
		greedyClass->setObjectName(QStringLiteral("greedyClass"));
	greedyClass->setFixedSize(512, 615);
	greedyClass->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

	centralWidget = new QWidget(greedyClass);
	centralWidget->setObjectName(QStringLiteral("centralWidget"));
	Score = new QLabel(centralWidget);
	Score->setObjectName(QStringLiteral("Score"));
	Score->setGeometry(QRect(120, 20, 80, 20));
	QFont font;
	font.setFamily(QStringLiteral("Courier New"));
	font.setPointSize(10);
	Score->setFont(font);
	Score->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
	Score->setTextFormat(Qt::AutoText);

	openGLWidget = new GLWidget(centralWidget);
	openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
	openGLWidget->setGeometry(QRect(30, 60, 450, 450));
	openGLWidget->setFont(font);
	openGLWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

	QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
	openGLWidget->setSizePolicy(sizePolicy);

	Length = new QLabel(centralWidget);
	Length->setObjectName(QStringLiteral("Length"));
	Length->setGeometry(QRect(400, 20, 72, 21));
	Length->setFont(font);
	Length->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
	Length->setTextFormat(Qt::AutoText);

	LengthLabel = new QLabel(centralWidget);
	LengthLabel->setObjectName(QStringLiteral("LengthLabel"));
	LengthLabel->setGeometry(QRect(320, 20, 65, 21));
	LengthLabel->setFont(font);
	LengthLabel->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
	LengthLabel->setTextFormat(Qt::AutoText);
	ScoreLabel = new QLabel(centralWidget);
	ScoreLabel->setObjectName(QStringLiteral("ScoreLabel"));
	ScoreLabel->setGeometry(QRect(40, 20, 51, 20));
	ScoreLabel->setFont(font);
	ScoreLabel->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
	ScoreLabel->setTextFormat(Qt::AutoText);
	MessageLabel = new QLabel(centralWidget);
	MessageLabel->setObjectName(QStringLiteral("MessageLabel"));
	MessageLabel->setGeometry(QRect(40, 530, 431, 31));
	MessageLabel->setFont(font);
	MessageLabel->setTextFormat(Qt::AutoText);

	AutoLabel = new QLabel(centralWidget);
	AutoLabel->setObjectName(QStringLiteral("AutoLabel"));
	AutoLabel->setGeometry(QRect(40, 565, 431, 31));
	AutoLabel->setFont(font);
	AutoLabel->setTextFormat(Qt::AutoText);

	greedyClass->setCentralWidget(centralWidget);
	 
	LastTime = 0;
	refresh = new QTimer; 

	retranslateUi(greedyClass); 

	QObject::connect(refresh, SIGNAL(timeout()), openGLWidget, SLOT(Update())); 

	QObject::connect(openGLWidget, SIGNAL(GameStart()), this, SLOT(ResetGame()));
	QObject::connect(refresh, SIGNAL(timeout()), this, SLOT(PrintScore()));
	QObject::connect(openGLWidget, SIGNAL(UpdLength(int)), this, SLOT(PrintLength(int)));
	QObject::connect(openGLWidget, SIGNAL(Wasted()), this, SLOT(RestartGame()));
	QObject::connect(openGLWidget, SIGNAL(ResumeGame()), this, SLOT(GameResume()));
	QObject::connect(openGLWidget, SIGNAL(PauseGame()), this, SLOT(GamePause()));
	QObject::connect(openGLWidget, SIGNAL(Winner()), this, SLOT(Win()));
	QObject::connect(openGLWidget, SIGNAL(Mode(bool)), this, SLOT(ModeChange(bool)));

	QObject::connect(openGLWidget, SIGNAL(Winner()), refresh, SLOT(stop()));
	QObject::connect(openGLWidget, SIGNAL(Wasted()), refresh, SLOT(stop()));
	QObject::connect(openGLWidget, SIGNAL(GameStart()), refresh, SLOT(start()));
	QObject::connect(openGLWidget, SIGNAL(ResumeGame()), refresh, SLOT(start()));
	QObject::connect(openGLWidget, SIGNAL(PauseGame()), refresh, SLOT(stop()));

	QMetaObject::connectSlotsByName(greedyClass);
} // setupUi

void Gluttonous::retranslateUi(QMainWindow *greedyClass)
{
	greedyClass->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
	greedyClass->setWindowTitle(QApplication::translate("greedyClass", "Snaqe", 0));
	Score->setText(QApplication::translate("greedyClass", "--:--:--", 0));
	Length->setText(QApplication::translate("greedyClass", "-", 0));
	LengthLabel->setText(QApplication::translate("greedyClass", "Length:", 0));
	ScoreLabel->setText(QApplication::translate("greedyClass", "Time:", 0));
	MessageLabel->setText(QApplication::translate("greedyClass", "Press [Space] to start a new game.", 0));
	AutoLabel->setText(QApplication::translate("greedyClass", "Press [F1] to enter AI mode.", 0));
	refresh->setInterval(INTERVAL);
}

void Gluttonous::PrintScore() 
{   
	LastTime += INTERVAL;

	int ms = LastTime;
	int ss = 1000;
	int mi = ss * 60;
	int hh = mi * 60;

	long hour = ms / hh;
	long minute = (ms - hour * hh) / mi;
	long second = (ms - hour * hh - minute * mi) / ss;

	QString strBuffer = QString("%1:%2:%3").arg(hour, 2, 10, QLatin1Char('0')).arg(minute, 2, 10, QLatin1Char('0')).arg(second, 2, 10, QLatin1Char('0'));
	
	Score->setText(strBuffer);
}

void Gluttonous::PrintLength(int l)
{
	Length->setText(QString::number(l));
}

void Gluttonous::ResetGame()
{
	LastTime = 0;
	Length->setNum(2);
	MessageLabel->setText(QApplication::translate("greedyClass", "Press [Space] to pause.", 0));
}

void Gluttonous::RestartGame()
{
	MessageLabel->setText(QApplication::translate("greedyClass", "Press [Space] to try again.", 0));  // Game over! 
}

void Gluttonous::GameResume()
{
	MessageLabel->setText(QApplication::translate("greedyClass", "Press [Space] to pause.", 0));
}

void Gluttonous::GamePause()
{
	MessageLabel->setText(QApplication::translate("greedyClass", "Press [Space] to continue.", 0));
}

void Gluttonous::Win()
{
	MessageLabel->setText(QApplication::translate("greedyClass", "Press [Space] to play again", 0));  // Congratulations! 
}

void Gluttonous::ModeChange(bool Auto)
{
	if (Auto)
	{
		AutoLabel->setText(QApplication::translate("greedyClass", "Press [F1] to enter MANUAL mode.", 0));
	}
	else
	{
		AutoLabel->setText(QApplication::translate("greedyClass", "Press [F1] to enter AI mode.", 0));
	} 

}