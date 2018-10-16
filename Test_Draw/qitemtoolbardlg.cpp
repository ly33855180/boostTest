#include "qitemtoolbardlg.h"
#include <QPainter>
#include "DToolBarBtn.h"
#include "dtoolbarlable.h"
#include "DToolBarSignal.h"
#include "dtoolbarbattery.h"
#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

QItemToolBarDlg::QItemToolBarDlg(QWidget *parent)
    : QWidget(parent)
{
    //ui.setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    
    QHBoxLayout* layout = new QHBoxLayout(this);
   
    //m_pBtn = new DToolBarBtn(this);
    //connect(m_pBtn, SIGNAL(clicked(bool)), this, SLOT(slotBtnClicked(bool)));

    m_pLable_PatientInfo = new DToolBarLable(this);
	m_pLable_PatientInfo->setFixedSize(25, 100);
    //m_pLable_DrawInfo = new DToolBarLable(this);

    m_pLable_Battery = new DToolBarBattery(this);
    //m_pLable_Signal = new DToolBarSignal(this);

    //layout->addWidget(m_pBtn);
    layout->addWidget(m_pLable_PatientInfo);

    layout->addStretch();

    //layout->addWidget(m_pLable_DrawInfo);
    //layout->addWidget(m_pLable_Signal);
    //layout->addWidget(m_pLable_Battery);

    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

QItemToolBarDlg::~QItemToolBarDlg()
{

}

void QItemToolBarDlg::setInfo()
{
    //int nHeigh = size().height();
    //QString qsPatientInfo = QStringLiteral("黄冈测试%1 男 39岁").arg(QStringLiteral("李白"));
    //m_pLable_PatientInfo->setLable(qsPatientInfo, nHeigh);
    //m_pLable_DrawInfo->setLable(QStringLiteral("走纸速度:25 mm/s 增益:10mm/mV"), nHeigh);
}

void QItemToolBarDlg::setLable(QString qsLable)
{
	//m_pLable_PatientInfo->setLable(qsLable,25);
}


void QItemToolBarDlg::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	p.setPen(Qt::red);
	QRect re = rect() + QMargins(0, 0, -1, -1);
	p.drawRect(re);
	//p.drawPixmap(0, 0, pix);
}

void QItemToolBarDlg::resizeEvent(QResizeEvent *event)
{
	return;
    int nBtnW = size().height();
    int nLableBatteryW = size().height() * 3;
    int nLableSignalW = size().height() * 2;

    int nLablePatientInfoW = m_pLable_PatientInfo->m_nWide;
    int nLableDrawInfoW = m_pLable_DrawInfo->m_nWide;

    m_pBtn->setFixedSize(nBtnW, size().height());
    m_pLable_Battery->setFixedSize(nLableBatteryW, size().height());
    m_pLable_Signal->setFixedSize(nLableSignalW, size().height());
    
    //简单处理 是不是需要显示;
    int nSurplusW = size().width() - nBtnW - nLableBatteryW - nLableSignalW;
    if (nSurplusW >= (nLablePatientInfoW + nLableDrawInfoW))
    {
        m_pLable_PatientInfo->setFixedSize(nLablePatientInfoW, size().height());
        m_pLable_DrawInfo->setFixedSize(nLableDrawInfoW, size().height());
    }
    else
    {
        if(nSurplusW > nLablePatientInfoW)
        {
            m_pLable_PatientInfo->setFixedSize(nLablePatientInfoW, size().height());
            m_pLable_DrawInfo->setFixedSize(0, size().height());
        }
        else
        {
            m_pLable_PatientInfo->setFixedSize(0, size().height());
            m_pLable_DrawInfo->setFixedSize(0, size().height());
        }

    }
}

void QItemToolBarDlg::slotBtnClicked(bool)
{
    qDebug() << "slotBtnClicked(bool)!";
}