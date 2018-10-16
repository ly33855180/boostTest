/********************************************************************************
** Form generated from reading UI file 'dtoolbarsignal.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DTOOLBARSIGNAL_H
#define UI_DTOOLBARSIGNAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <qlable.h>

QT_BEGIN_NAMESPACE

class Ui_DToolBarSignal
{
public:

    void setupUi(QLable *DToolBarSignal)
    {
        if (DToolBarSignal->objectName().isEmpty())
            DToolBarSignal->setObjectName(QStringLiteral("DToolBarSignal"));
        DToolBarSignal->resize(400, 300);

        retranslateUi(DToolBarSignal);

        QMetaObject::connectSlotsByName(DToolBarSignal);
    } // setupUi

    void retranslateUi(QLable *DToolBarSignal)
    {
        DToolBarSignal->setWindowTitle(QApplication::translate("DToolBarSignal", "DToolBarSignal", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DToolBarSignal: public Ui_DToolBarSignal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DTOOLBARSIGNAL_H
