/********************************************************************************
** Form generated from reading UI file 'dtoolbarlable.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DTOOLBARLABLE_H
#define UI_DTOOLBARLABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DToolBarLable
{
public:

    void setupUi(QWidget *DToolBarLable)
    {
        if (DToolBarLable->objectName().isEmpty())
            DToolBarLable->setObjectName(QStringLiteral("DToolBarLable"));
        DToolBarLable->resize(400, 300);

        retranslateUi(DToolBarLable);

        QMetaObject::connectSlotsByName(DToolBarLable);
    } // setupUi

    void retranslateUi(QWidget *DToolBarLable)
    {
        DToolBarLable->setWindowTitle(QApplication::translate("DToolBarLable", "DToolBarLable", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DToolBarLable: public Ui_DToolBarLable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DTOOLBARLABLE_H
