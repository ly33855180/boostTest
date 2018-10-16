/********************************************************************************
** Form generated from reading UI file 'DTestListWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DTESTLISTWIDGET_H
#define UI_DTESTLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DTestListWidget
{
public:

    void setupUi(QWidget *DTestListWidget)
    {
        if (DTestListWidget->objectName().isEmpty())
            DTestListWidget->setObjectName(QStringLiteral("DTestListWidget"));
        DTestListWidget->resize(400, 300);

        retranslateUi(DTestListWidget);

        QMetaObject::connectSlotsByName(DTestListWidget);
    } // setupUi

    void retranslateUi(QWidget *DTestListWidget)
    {
        DTestListWidget->setWindowTitle(QApplication::translate("DTestListWidget", "DTestListWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DTestListWidget: public Ui_DTestListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DTESTLISTWIDGET_H
