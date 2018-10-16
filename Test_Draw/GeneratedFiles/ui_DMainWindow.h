/********************************************************************************
** Form generated from reading UI file 'DMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DMAINWINDOW_H
#define UI_DMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DMainWindow
{
public:

    void setupUi(QWidget *DMainWindow)
    {
        if (DMainWindow->objectName().isEmpty())
            DMainWindow->setObjectName(QStringLiteral("DMainWindow"));
        DMainWindow->resize(400, 300);

        retranslateUi(DMainWindow);

        QMetaObject::connectSlotsByName(DMainWindow);
    } // setupUi

    void retranslateUi(QWidget *DMainWindow)
    {
        DMainWindow->setWindowTitle(QApplication::translate("DMainWindow", "DMainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DMainWindow: public Ui_DMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DMAINWINDOW_H
