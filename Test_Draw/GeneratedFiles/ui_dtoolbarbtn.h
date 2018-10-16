/********************************************************************************
** Form generated from reading UI file 'dtoolbarbtn.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DTOOLBARBTN_H
#define UI_DTOOLBARBTN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DToolBarBtn
{
public:

    void setupUi(QPushButton *DToolBarBtn)
    {
        if (DToolBarBtn->objectName().isEmpty())
            DToolBarBtn->setObjectName(QStringLiteral("DToolBarBtn"));
        DToolBarBtn->resize(400, 300);

        retranslateUi(DToolBarBtn);

        QMetaObject::connectSlotsByName(DToolBarBtn);
    } // setupUi

    void retranslateUi(QPushButton *DToolBarBtn)
    {
        DToolBarBtn->setWindowTitle(QApplication::translate("DToolBarBtn", "DToolBarBtn", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DToolBarBtn: public Ui_DToolBarBtn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DTOOLBARBTN_H
