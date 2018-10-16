/********************************************************************************
** Form generated from reading UI file 'dtoolbarbattery.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DTOOLBARBATTERY_H
#define UI_DTOOLBARBATTERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <qlable.h>

QT_BEGIN_NAMESPACE

class Ui_DToolBarBattery
{
public:

    void setupUi(QLable *DToolBarBattery)
    {
        if (DToolBarBattery->objectName().isEmpty())
            DToolBarBattery->setObjectName(QStringLiteral("DToolBarBattery"));
        DToolBarBattery->resize(400, 300);

        retranslateUi(DToolBarBattery);

        QMetaObject::connectSlotsByName(DToolBarBattery);
    } // setupUi

    void retranslateUi(QLable *DToolBarBattery)
    {
        DToolBarBattery->setWindowTitle(QApplication::translate("DToolBarBattery", "DToolBarBattery", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DToolBarBattery: public Ui_DToolBarBattery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DTOOLBARBATTERY_H
