/********************************************************************************
** Form generated from reading UI file 'ddrawwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DDRAWWIDGET_H
#define UI_DDRAWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DDrawWidget
{
public:

    void setupUi(QWidget *DDrawWidget)
    {
        if (DDrawWidget->objectName().isEmpty())
            DDrawWidget->setObjectName(QStringLiteral("DDrawWidget"));
        DDrawWidget->resize(400, 300);

        retranslateUi(DDrawWidget);

        QMetaObject::connectSlotsByName(DDrawWidget);
    } // setupUi

    void retranslateUi(QWidget *DDrawWidget)
    {
        DDrawWidget->setWindowTitle(QApplication::translate("DDrawWidget", "DDrawWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DDrawWidget: public Ui_DDrawWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DDRAWWIDGET_H
