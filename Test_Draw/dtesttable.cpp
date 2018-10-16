#include "dtesttable.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QPushButton>
DTestTable::DTestTable(QWidget *parent)
    : QWidget(parent)
{


    QTableView* pTable = new QTableView(this);



    m_pModel = new QStandardItemModel;
    m_pModel->setColumnCount(3);
    m_pModel->setHeaderData(0, Qt::Horizontal,QStringLiteral("事件时间"));
    m_pModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("事件名称"));
    m_pModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("事件类型"));

    pTable->setModel(m_pModel);

    pTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    pTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    pTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    pTable->setSelectionMode(QAbstractItemView::SingleSelection);
    pTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pTable->setSelectionBehavior(QAbstractItemView::SelectRows);


    QPushButton* pbtnadd = new QPushButton(QStringLiteral("add"), this);
    QPushButton* pbtndel = new QPushButton(QStringLiteral("del"), this);
    QPushButton* pbtnmodify = new QPushButton(QStringLiteral("modify"), this);
    QPushButton* pbtnquery = new QPushButton(QStringLiteral("query"), this);

    QHBoxLayout* playout = new QHBoxLayout(this);

    playout->addWidget(pTable);
    playout->addWidget(pbtnadd);
    playout->addWidget(pbtndel);
    playout->addWidget(pbtnmodify);
    playout->addWidget(pbtnquery);

 
    connect(pbtnadd, SIGNAL(clicked()), this, SLOT(clicked_add()));
    connect(pbtndel, SIGNAL(clicked()), this, SLOT(clicked_del()));
    connect(pbtnmodify, SIGNAL(clicked()), this, SLOT(clicked_modify()));
    connect(pbtnquery, SIGNAL(clicked()), this, SLOT(clicked_query()));

    connect(pTable, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(slotRowDoubleClicked(const QModelIndex &)));
}

DTestTable::~DTestTable()
{

}

void DTestTable::clicked_add()
{

        int row = m_pModel->rowCount();
        QString str1 = QStringLiteral("时间%1").arg(row + 1);
        m_pModel->setItem(row, 0, new QStandardItem(str1));
        m_pModel->item(row, 0)->setForeground(QBrush(QColor(255, 0, 0)));

        QString str2 = QStringLiteral("名称%1").arg(row + 1);
        m_pModel->item(row, 0)->setTextAlignment(Qt::AlignCenter);
        m_pModel->setItem(row, 1, new QStandardItem(str2));

        QString str3 = QStringLiteral("类型%1").arg(row + 1);
        m_pModel->item(row, 0)->setTextAlignment(Qt::AlignCenter);
        m_pModel->setItem(row, 2, new QStandardItem(str3));

}

void DTestTable::clicked_del()
{

}

void DTestTable::clicked_modify()
{

}

void DTestTable::clicked_query()
{

}

void DTestTable::slotRowDoubleClicked(const QModelIndex &index)
{
    int nrow = index.row();
    //m_pModel->removeRow(nrow);
    m_pModel->removeRows(0, m_pModel->rowCount());
}
