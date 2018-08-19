/********************************************************************************
** Form generated from reading UI file 'gluttonous.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLUTTONOUS_H
#define UI_GLUTTONOUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GluttonousClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GluttonousClass)
    {
        if (GluttonousClass->objectName().isEmpty())
            GluttonousClass->setObjectName(QStringLiteral("GluttonousClass"));
        GluttonousClass->resize(600, 400);
        menuBar = new QMenuBar(GluttonousClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        GluttonousClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GluttonousClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GluttonousClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(GluttonousClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GluttonousClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GluttonousClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GluttonousClass->setStatusBar(statusBar);

        retranslateUi(GluttonousClass);

        QMetaObject::connectSlotsByName(GluttonousClass);
    } // setupUi

    void retranslateUi(QMainWindow *GluttonousClass)
    {
        GluttonousClass->setWindowTitle(QApplication::translate("GluttonousClass", "Gluttonous", 0));
    } // retranslateUi

};

namespace Ui {
    class GluttonousClass: public Ui_GluttonousClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLUTTONOUS_H
