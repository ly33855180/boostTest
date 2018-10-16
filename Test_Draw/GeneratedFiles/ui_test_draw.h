/********************************************************************************
** Form generated from reading UI file 'test_draw.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_DRAW_H
#define UI_TEST_DRAW_H

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

class Ui_Test_DrawClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Test_DrawClass)
    {
        if (Test_DrawClass->objectName().isEmpty())
            Test_DrawClass->setObjectName(QStringLiteral("Test_DrawClass"));
        Test_DrawClass->resize(600, 400);
        menuBar = new QMenuBar(Test_DrawClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        Test_DrawClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Test_DrawClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Test_DrawClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Test_DrawClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Test_DrawClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Test_DrawClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Test_DrawClass->setStatusBar(statusBar);

        retranslateUi(Test_DrawClass);

        QMetaObject::connectSlotsByName(Test_DrawClass);
    } // setupUi

    void retranslateUi(QMainWindow *Test_DrawClass)
    {
        Test_DrawClass->setWindowTitle(QApplication::translate("Test_DrawClass", "Test_Draw", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Test_DrawClass: public Ui_Test_DrawClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_DRAW_H
