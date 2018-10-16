/********************************************************************************
** Form generated from reading UI file 'DTestCurContrl.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DTESTCURCONTRL_H
#define UI_DTESTCURCONTRL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DTestCurContrl
{
public:

    void setupUi(QWidget *DTestCurContrl)
    {
        if (DTestCurContrl->objectName().isEmpty())
            DTestCurContrl->setObjectName(QStringLiteral("DTestCurContrl"));
        DTestCurContrl->resize(400, 300);

        retranslateUi(DTestCurContrl);

        QMetaObject::connectSlotsByName(DTestCurContrl);
    } // setupUi

    void retranslateUi(QWidget *DTestCurContrl)
    {
        DTestCurContrl->setWindowTitle(QApplication::translate("DTestCurContrl", "DTestCurContrl", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DTestCurContrl: public Ui_DTestCurContrl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DTESTCURCONTRL_H
