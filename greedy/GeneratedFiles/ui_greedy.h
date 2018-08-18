/********************************************************************************
** Form generated from reading UI file 'greedy.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GREEDY_H
#define UI_GREEDY_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_greedyClass
{
public:
    QWidget *centralWidget;
    QLabel *Score;
    QOpenGLWidget *openGLWidget;
    QLabel *Length;
    QLabel *LengthLabel;
    QLabel *ScoreLabel;
    QLabel *MessageLabel;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *greedyClass)
    {
        if (greedyClass->objectName().isEmpty())
            greedyClass->setObjectName(QStringLiteral("greedyClass"));
        greedyClass->resize(512, 584);
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/Snake_24px_1186148_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        greedyClass->setWindowIcon(icon);
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
        openGLWidget = new QOpenGLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(30, 60, 450, 450));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setFont(font);
        openGLWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
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
        statusBar = new QStatusBar(greedyClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        greedyClass->setStatusBar(statusBar);

        retranslateUi(greedyClass);

        QMetaObject::connectSlotsByName(greedyClass);
    } // setupUi

    void retranslateUi(QMainWindow *greedyClass)
    {
        greedyClass->setWindowTitle(QApplication::translate("greedyClass", "greedy", 0));
        Score->setText(QApplication::translate("greedyClass", "0", 0));
        Length->setText(QApplication::translate("greedyClass", "2", 0));
        LengthLabel->setText(QApplication::translate("greedyClass", "Length:", 0));
        ScoreLabel->setText(QApplication::translate("greedyClass", "Score:", 0));
        MessageLabel->setText(QApplication::translate("greedyClass", "Press [Space] to play.", 0));
    } // retranslateUi

};

namespace Ui {
    class greedyClass: public Ui_greedyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GREEDY_H
