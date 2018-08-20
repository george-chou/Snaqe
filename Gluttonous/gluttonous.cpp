#include "stdafx.h"
#include "gluttonous.h"
#include "GLWidget.h"

Gluttonous::Gluttonous(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	setupUi(this);
}

Gluttonous::~Gluttonous()
{

}


void Gluttonous::setupUi(QMainWindow *greedyClass)
{
	if (greedyClass->objectName().isEmpty())
		greedyClass->setObjectName(QStringLiteral("greedyClass"));
	greedyClass->setFixedSize(512, 584);
	greedyClass->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

	centralWidget = new QWidget(greedyClass);
	centralWidget->setObjectName(QStringLiteral("centralWidget"));
	Score = new QLabel(centralWidget);
	Score->setObjectName(QStringLiteral("Score"));
	Score->setGeometry(QRect(120, 20, 72, 20));
	QFont font;
	font.setFamily(QStringLiteral("Microsoft YaHei UI"));
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
	LengthLabel->setGeometry(QRect(320, 20, 61, 21));
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
	greedyClass->setCentralWidget(centralWidget);

	refresh = new QTimer;

	retranslateUi(greedyClass);

	QObject::connect(refresh, SIGNAL(timeout()), openGLWidget, SLOT(Update()));

	QObject::connect(openGLWidget, SIGNAL(GameStart()), this, SLOT(ResetGame()));
	QObject::connect(openGLWidget, SIGNAL(UpdLength(int)), this, SLOT(PrintScore(int)));
	QObject::connect(openGLWidget, SIGNAL(UpdLength(int)), this, SLOT(PrintLength(int)));
	QObject::connect(openGLWidget, SIGNAL(Wasted()), this, SLOT(RestartGame()));
	QObject::connect(openGLWidget, SIGNAL(ResumeGame()), this, SLOT(GameResume()));
	QObject::connect(openGLWidget, SIGNAL(PauseGame()), this, SLOT(GamePause()));
	QObject::connect(openGLWidget, SIGNAL(Winner()), this, SLOT(Win()));

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
	Score->setText(QApplication::translate("greedyClass", "-", 0));
	Length->setText(QApplication::translate("greedyClass", "-", 0));
	LengthLabel->setText(QApplication::translate("greedyClass", "Length:", 0));
	ScoreLabel->setText(QApplication::translate("greedyClass", "Score:", 0));
	MessageLabel->setText(QApplication::translate("greedyClass", "Press [Space] to play.", 0));
	refresh->setInterval(100);
}

void Gluttonous::PrintScore(int l)
{
	int s = (l - 2) * 50;
	Score->setText(QString::number(s));
}

void Gluttonous::PrintLength(int l)
{
	Length->setText(QString::number(l));
}

void Gluttonous::ResetGame()
{
	Score->setNum(0);
	Length->setNum(2);
	MessageLabel->setText(QApplication::translate("greedyClass", "Press [Space] to pause.", 0));
}

void Gluttonous::RestartGame()
{
	MessageLabel->setText(QApplication::translate("greedyClass", "Game over! Press [Space] to replay.", 0));
}

void Gluttonous::GameResume()
{
	MessageLabel->setText(QApplication::translate("greedyClass", "Press [Space] to pause.", 0));
}

void Gluttonous::GamePause()
{
	MessageLabel->setText(QApplication::translate("greedyClass", "Press [Space] to resume.", 0));
}

void Gluttonous::Win()
{
	MessageLabel->setText(QApplication::translate("greedyClass", "Congratulations! Press [Space] to replay.", 0));
}