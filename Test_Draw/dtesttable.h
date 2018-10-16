#ifndef DTESTTABLE_H
#define DTESTTABLE_H

#include <QWidget>
#include "ui_dtesttable.h"
class QTableView;
class QStandardItemModel;

class DTestTable : public QWidget
{
    Q_OBJECT

public:
    DTestTable(QWidget *parent = 0);
    ~DTestTable();

private:
    Ui::DTestTable ui;


    QTableView* pTable;
    QStandardItemModel* m_pModel;

private slots:

    void clicked_add();
    void clicked_del();
    void clicked_modify();
    void clicked_query();
    void slotRowDoubleClicked(const QModelIndex &index);
};

#endif // DTESTTABLE_H
