/********************************************************************************
** Form generated from reading UI file 'ddlgitem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DDLGITEM_H
#define UI_DDLGITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DDlgItem
{
public:

    void setupUi(QWidget *DDlgItem)
    {
        if (DDlgItem->objectName().isEmpty())
            DDlgItem->setObjectName(QStringLiteral("DDlgItem"));
        DDlgItem->resize(400, 300);

        retranslateUi(DDlgItem);

        QMetaObject::connectSlotsByName(DDlgItem);
    } // setupUi

    void retranslateUi(QWidget *DDlgItem)
    {
        DDlgItem->setWindowTitle(QApplication::translate("DDlgItem", "DDlgItem", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DDlgItem: public Ui_DDlgItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DDLGITEM_H
