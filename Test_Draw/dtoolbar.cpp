#include "dtoolbar.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

DToolBar::DToolBar(QWidget *parent)
    : QWidget(parent)
    , m_pBtn_Next(NULL)
    , m_pBtn_Pre(NULL)
    , m_pLable_CurPage(NULL)
    , m_pBtn_2X2(NULL)
    , m_pBtn_2X3(NULL)
    , m_pBtn_3X3(NULL)
    , m_pBtn_7X7(NULL)
{
    setFixedHeight(30);
    QHBoxLayout* pHLayout = new QHBoxLayout(this);
    pHLayout->setMargin(0);
    pHLayout->setSpacing(0);
    setLayout(pHLayout);

    m_pBtn_Next = new QPushButton("next");
    m_pBtn_Next->setFixedSize(40, 30);
    m_pBtn_Pre = new QPushButton("pre");
    m_pBtn_Pre->setFixedSize(40, 30);
    m_pLable_CurPage = new QLabel("0/0");
    m_pLable_CurPage->setFixedSize(100, 30);

    pHLayout->addWidget(m_pBtn_Pre);
    pHLayout->addWidget(m_pBtn_Next);
    pHLayout->addWidget(m_pLable_CurPage);
    pHLayout->addStretch();



    m_pBtn_2X2 = new QPushButton("2X2");
    m_pBtn_2X3 = new QPushButton("2X3");
    m_pBtn_3X3 = new QPushButton("3X3");
    m_pBtn_7X7 = new QPushButton("7X7");


    m_pBtn_2X2->setFixedSize(40, 30);
    m_pBtn_2X3->setFixedSize(40, 30);
    m_pBtn_3X3->setFixedSize(40, 30);
    m_pBtn_7X7->setFixedSize(40, 30);

    pHLayout->addWidget(m_pBtn_2X2);
    pHLayout->addWidget(m_pBtn_2X3);
    pHLayout->addWidget(m_pBtn_3X3);
    pHLayout->addWidget(m_pBtn_7X7);



}

DToolBar::~DToolBar()
{

}

void DToolBar::slot_ChangeLable(int nCurPage, int nPageCount, int nMonFrameCounts)
{	
	QString qsTemp = QString("%1/%2-%3").arg(nCurPage).arg(nPageCount).arg(nMonFrameCounts);
	m_pLable_CurPage->setText(qsTemp);
}

