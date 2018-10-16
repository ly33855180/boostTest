/********************************************************************************
** Form generated from reading UI file 'qitemtoolbardlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QITEMTOOLBARDLG_H
#define UI_QITEMTOOLBARDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QItemToolBarDlg
{
public:

    void setupUi(QWidget *QItemToolBarDlg)
    {
        if (QItemToolBarDlg->objectName().isEmpty())
            QItemToolBarDlg->setObjectName(QStringLiteral("QItemToolBarDlg"));
        QItemToolBarDlg->resize(400, 300);

        retranslateUi(QItemToolBarDlg);

        QMetaObject::connectSlotsByName(QItemToolBarDlg);
    } // setupUi

    void retranslateUi(QWidget *QItemToolBarDlg)
    {
        QItemToolBarDlg->setWindowTitle(QApplication::translate("QItemToolBarDlg", "QItemToolBarDlg", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QItemToolBarDlg: public Ui_QItemToolBarDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QITEMTOOLBARDLG_H
