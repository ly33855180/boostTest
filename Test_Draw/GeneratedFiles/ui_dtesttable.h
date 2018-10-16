/********************************************************************************
** Form generated from reading UI file 'dtesttable.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DTESTTABLE_H
#define UI_DTESTTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DTestTable
{
public:

    void setupUi(QWidget *DTestTable)
    {
        if (DTestTable->objectName().isEmpty())
            DTestTable->setObjectName(QStringLiteral("DTestTable"));
        DTestTable->resize(400, 300);

        retranslateUi(DTestTable);

        QMetaObject::connectSlotsByName(DTestTable);
    } // setupUi

    void retranslateUi(QWidget *DTestTable)
    {
        DTestTable->setWindowTitle(QApplication::translate("DTestTable", "DTestTable", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DTestTable: public Ui_DTestTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DTESTTABLE_H
