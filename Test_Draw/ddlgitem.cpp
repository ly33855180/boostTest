#include "ddlgitem.h"
#include "QPainter"
#include <QMouseEvent>

#include <QHBoxLayout>
#include <QMargins>
#include <QPen>
#include <QTimer>


#include <string>
#include <iostream>
#include <fstream>
#include <qDebug>
using namespace std;
#include <boost/bind.hpp>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "DBoxManager.h"
boost::mutex g_leadDataMutex;

#include "DToolBarBtn.h"
#include <QLabel.h>
int   g_nPixOfOneMM;
qreal g_nXStepUnitPix;// = MMToPixel(0.25);
static const QString s_LeadNames[12] = { "I", "II", "III", "aVR", "aVL", "aVF",
"V1", "V2", "V3", "V4", "V5", "V6" };

#include <QThread>
DDlgItem::DDlgItem(QWidget *parent)
	: QWidget(parent), m_nShowLeadNum(12), m_nGain(10), m_nStep(0), m_bUpadataBK(true), m_bFocus(false)
{
	//setAttribute(Qt::WA_DeleteOnClose);
	int n6 = this->winId();
    this->setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::ClickFocus);
    
    int n = MMToPixel(1) + 0.5;
    int m_PaperSpeed = 25;//mm/s
    g_nPixOfOneMM = MMToPixel(1) + 0.5;
    g_nXStepUnitPix = 25 * g_nPixOfOneMM / 100;


    connect(this, SIGNAL(sigTimeOut()), this, SLOT(_update()));


	connect(this, SIGNAL(sigGetLeadDataCallBack(const sPackageData& , int)), this, SLOT(slotGetLeadDataCallBack(const sPackageData&, int)), Qt::QueuedConnection);
  


	//QVBoxLayout* layoutV = new QVBoxLayout(this);
	//m_toolBar = new QItemToolBarDlg(this);
	//m_toolBar->setFixedHeight(25);
	//layoutV->addWidget(m_toolBar);
	//layoutV->addStretch();
	//setContentsMargins(0, 0, 0, 0);
	//layoutV->setContentsMargins(0, 0, 0, 0);
	//m_toolBar->setInfo();

	//setLayout(layoutV);
	//m_ptrBoxSocket = boost::shared_ptr<DBoxSocket>(new DBoxSocket("127.0.0.1", 4004));
	//m_ptrBoxSocket->StartGetMdData(boost::bind(&DDlgItem::GetLeadDataCallBack, this, _1, _2));
	createUI();
}
void DDlgItem::_update()
{

    //static int a = 0;
    //if (a >= m_nShowLeadNum *100)
    //{
    //    return;
    //}
    
    QPainter painter(&m_pixLeadData);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor colorWave = QColor(Qt::green);//qRgb(0, 200, 0);
    QPen pen(colorWave, 1, Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    painter.setPen(pen);

    //1 draw eraser
	//if(0)
    {

		QPainter& painter0 = painter;
		painter0.save();
		painter0.setCompositionMode(QPainter::CompositionMode_Clear);
		QRectF rectEraser(QRectF(m_arrLeadCurPt[0].x(), 0, 50, rect().height()));
		painter0.eraseRect(rectEraser);
		painter.restore();

    }

    // 2
#if 1
    for (int i = 0; i < m_nShowLeadNum; i++)
    { 
        QPainterPath pathVLines;
        QPointF ptCur = m_arrLeadCurPt[i];
        QPointF ptNext;
        qreal dBaseY = m_arrLeadStartPt[i].y();

        //less 10
        if (m_leadData.m_dLeadData[i].size() < 10)
        {
            continue;
        }
        for (int j = 0; j < 10 ;j ++)
        {
            pathVLines.moveTo(ptCur);
            
            ptNext.setX(ptCur.x() + g_nXStepUnitPix);
            qreal dNextY = MMToPixel(m_leadData.m_dLeadData[i][j] * m_nGain);
            ptNext.setY(dBaseY - dNextY);
            pathVLines.lineTo(ptNext);
            //qDebug() <<"m_nRow = "<<m_nRow << ",m_nCol = " << m_nCol <<",ptNext,x ="<< ptNext.x() <<", y = "<< ptNext.y();
            
            ptCur = ptNext;
        }
        painter.drawPath(pathVLines);
        if (ptNext.x() >= rect().width())
        {
            m_arrLeadCurPt[i] = ptNext;
            m_arrLeadCurPt[i].setX(m_arrLeadStartPt[i].x());
        }
        else
        {
            m_arrLeadCurPt[i] = ptNext;
        }
		boost::lock_guard<boost::mutex> lock(g_leadDataMutex);
        m_leadData.m_dLeadData[i].erase(m_leadData.m_dLeadData[i].begin(), m_leadData.m_dLeadData[i].begin() + 10);
    }
#endif
	 update();
}

void DDlgItem::slotGetLeadDataCallBack(const sPackageData& leadData, int nTag)
{
	//qDebug() << "GetLeadDataCallBack,  m_strRecvTime = " << QString(leadData.m_strRecvTime.c_str()) << ",m_nPackageNum = " << leadData.m_nPackageNum;
	int start = GetTickCount();
	boost::lock_guard<boost::mutex> lock(g_leadDataMutex);
	for (int j = 0; j < 12; j++)
	{
		m_leadData.m_dLeadData[j].insert(m_leadData.m_dLeadData[j].end(), &leadData.m_dData[j][0], &leadData.m_dData[j][0] + 112);
		if (j == 0)
		{
			//qDebug() << "j = " << j << ",size = " << m_leadData.m_dLeadData[j].size();
		}
	}
	int end = GetTickCount();
	//qDebug() << "*******span = " << end - start;
}


void DDlgItem::handle_timer(const boost::system::error_code& e, boost::asio::deadline_timer* t)
{
	if (e)
	{
		qDebug() << "error handle_timer e == null!";
		return;
	}

	if (!t)
	{
		qDebug() << "error handle_timer t == null!";
		return;
	}
    emit sigTimeOut();
	t->expires_at(t->expires_at() + boost::posix_time::millisec(1000));
	t->async_wait(boost::bind(&DDlgItem::handle_timer, this, boost::asio::placeholders::error, t));
}

void DDlgItem::GetLeadDataCallBack(const sPackageData& leadData, int nTag)
{
	sigGetLeadDataCallBack(leadData, nTag);
	//slotGetLeadDataCallBack(leadData, nTag);
}

void DDlgItem::createUI()
{
	QVBoxLayout* pMainLayoutV = new QVBoxLayout(this);
	pMainLayoutV->setSpacing(0);
	pMainLayoutV->setMargin(0);
	setLayout(pMainLayoutV);

	{//btn
		QHBoxLayout* ph = new QHBoxLayout;
		ph->setSpacing(0);
		ph->setMargin(0);
		pMainLayoutV->addLayout(ph);

		DToolBarBtn* pBtn = new DToolBarBtn;
		pBtn->setFixedSize(25, 25);
		ph->addWidget(pBtn);

		{//姓名信息
			QVBoxLayout* pV = new QVBoxLayout;
			pV->setSpacing(2);
			pV->setMargin(2);
			ph->addLayout(pV);
			{
				QString qsName = QStringLiteral("AAAA");
				QString qsAge = QStringLiteral("30岁");
				QString qsSex = QStringLiteral("男");
				QString qsTemp = QStringLiteral("%1 %2 %3").arg(qsName).arg(qsAge).arg(qsSex);
				QLabel* pLabel_0 = new QLabel(qsTemp);
				pLabel_0->setStyleSheet("color:red;");
				pV->addWidget(pLabel_0); 
			}
			{
				QString qsTemp = QStringLiteral("中日友好医院");;
				QLabel* pLabel_0 = new QLabel(qsTemp);
				pLabel_0->setStyleSheet("color:red;");
				pV->addWidget(pLabel_0);
			}
			{
				QString qsTemp = QStringLiteral("电话:123456789");;
				QLabel* pLabel_0 = new QLabel(qsTemp);
				pLabel_0->setStyleSheet("color:red;");
				pV->addWidget(pLabel_0);

			}
		}

		{//床号
			QString qsTemp = QStringLiteral("病床001床");
			QLabel* pLabel_0 = new QLabel(qsTemp);
			pLabel_0->setStyleSheet("color:red;");
			ph->addWidget(pLabel_0);
			pLabel_0->setAlignment(Qt::AlignCenter);
			pLabel_0->setMinimumSize(1,1);
			pLabel_0->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
		}

		{//心律
			QString qsTemp = QStringLiteral("120");;
			QLabel* pLabel_0 = new QLabel(qsTemp);
			pLabel_0->setAlignment(Qt::AlignRight);
			pLabel_0->setStyleSheet("color:red;");
			ph->addWidget(pLabel_0);
		}
	    //ph->addStretch();
	}

	pMainLayoutV->addStretch();

	//pMainLayoutV->setSizeConstraint(QLayout::SetFixedSize);   //设定其为固定的大小
	//setMinimumSize(400, 400);
	//pMainLayoutV->setSizeConstraint(QLayout::SetMinAndMaxSize);

}

DDlgItem::~DDlgItem()
{
	DBoxManager::Instance()->UnSubscribeLeadData(m_sMonFrame.m_qsDEV_IDX, this->winId(), boost::bind(&DDlgItem::GetLeadDataCallBack, this, _1, _2));
    disconnect(this, SIGNAL(sigTimeOut()), this, SLOT(_update()));
	disconnect(this, SIGNAL(sigGetLeadDataCallBack(const sPackageData&, int)), this, SLOT(slotGetLeadDataCallBack(const sPackageData&, int)));

}


void DDlgItem::LoadData(const DLeadDatas & data)
{
    m_leadData = data;
}

void DDlgItem::setRowAndCol(int nRow, int nCol)
{
    m_nRow = nRow;
    m_nCol = nCol;
}

void DDlgItem::SetEmptyMonFrame()
{
	m_sMonFrame.m_nNo = -1;
	DBoxManager::Instance()->UnSubscribeLeadData(m_sMonFrame.m_qsDEV_IDX, this->winId(), boost::bind(&DDlgItem::GetLeadDataCallBack, this, _1, _2));
	
	{
		boost::lock_guard<boost::mutex> lock(g_leadDataMutex);
		for (size_t i = 0; i < 12; i++)
		{
			m_leadData.m_dLeadData[i].clear();
		}
	}
	

	for (int i = 0; i < 12; i++)
	{
		m_arrLeadCurPt[i] = m_arrLeadStartPt[i];
	}

	m_pixLeadData = QPixmap(size());
	m_pixLeadData.fill(Qt::transparent);

	m_pix = QPixmap(size());
	m_pix.fill(Qt::black);

	update();

}

void DDlgItem::SetMonFrame(const sMonFrame & m0)
{
	m_sMonFrame = m0;
	//m_toolBar->setLable(m0.m_qsNO);
	resizeEvent(NULL);
	DBoxManager::Instance()->SubscribeLeadData(m_sMonFrame.m_qsDEV_IDX, this->winId(), boost::bind(&DDlgItem::GetLeadDataCallBack, this, _1, _2));
}

void DDlgItem::paintEvent(QPaintEvent *)
{
    //qDebug() << "************DDlgItem paintEvent!!!!!";

	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing, true);

		painter.drawPixmap(0, 0, m_pix);
		painter.drawPixmap(0, 0, m_pixLeadData);

		if (m_bFocus)
		{
			{
				QPen pen;
				pen.setWidth(2);
				pen.setStyle(Qt::SolidLine);
				pen.setColor(Qt::green);
				painter.setPen(pen);

				QRect rect0 = rect();
				rect0 += QMargins(0, 0, 0, 0);
				painter.drawRect(rect0);
			}
		}
	}
}

void DDlgItem::resizeEvent(QResizeEvent *event)
{
    //qDebug() << "resizeEvent************************************";

    m_pixLeadData = QPixmap(size());
    m_pixLeadData.fill(Qt::transparent);

    m_pix = QPixmap(size());
    m_pix.fill(Qt::black);

	if (m_sMonFrame.m_nNo != -1)
	{
		QPainter painter(&m_pix);

		drawBkGrid(&painter, rect());
		showLeadName(&painter, rect(), 1);

		m_bUpadataBK = true;
	}

}

void DDlgItem::focusInEvent(QFocusEvent *e)
{
    qDebug() << "focusInEvent m_nRow = " << m_nRow << ",m_nCol = "<< m_nCol;
    m_bFocus = true;
    update();

}

void DDlgItem::focusOutEvent(QFocusEvent *e)
{
    qDebug() << "focusOutEvent m_nRow = " << m_nRow << ",m_nCol = " << m_nCol;
    m_bFocus = false;
    update();
}


void DDlgItem::showEvent(QShowEvent *event)
{
}

void DDlgItem::show()
{
	int a = 10;
}

void DDlgItem::mousePressEvent(QMouseEvent *event)
{

}

void DDlgItem::drawBkGrid(QPainter *painter, QRect &rect)
{
    // 绘制小网格
    int nLineDistance = g_nPixOfOneMM * 5;
    int nStartX = rect.left();
    int nStartY = rect.top();

    int nWidth = rect.width();// -1;
    int nHeigh = rect.height();// -1;

    QPainterPath pathVLines;

    //竖线
    for (int nX = nStartX; nX < rect.width(); nX += nLineDistance)
    {
        pathVLines.moveTo(nX, nStartY);
        pathVLines.lineTo(nX, nStartY + nHeigh);
    }
    //横线
    QPainterPath pathHLines;
    for (int nY = nStartY; nY < rect.height(); nY += nLineDistance)
    {
        pathVLines.moveTo(nStartX, nY);
        pathVLines.lineTo(nStartX + nWidth, nY);
    }

    const QColor ColorLine(qRgb(50, 50, 50));
    QPen pen(ColorLine, 1, Qt::SolidLine);
    painter->setPen(pen);
    painter->drawPath(pathVLines);

    {
        //painter->save();
        //QPen pen;
        //pen.setWidth(4);
        //pen.setColor(Qt::gray);
        //painter->setPen(pen);

        //painter->drawRect(rect);
        //painter->restore(); 
    }
}

void DDlgItem::showLeadName(QPainter *painter, QRect &rect, int box)
{
    QColor colorWave = QColor(Qt::white);//qRgb(0, 200, 0);
    QPen pen(colorWave, 1, Qt::SolidLine);
    painter->setPen(pen);

    qreal dStartX = rect.left();
    qreal dStartY  = rect.top();
    qreal dDistance = rect.height() / (m_nShowLeadNum + 1);

    dStartY += dDistance;
    for (int i = 0; i < m_nShowLeadNum; i++)
    {
        // 绘制导联号
        QRect textRect;
        textRect.setRect(dStartX + 20, dStartY - 15, 25, 15);
        painter->drawText(textRect, Qt::AlignHCenter | Qt::AlignBottom, s_LeadNames[i]);
        //painter->drawRect(textRect);
        
        QVector<QPointF> points;
        QPointF pt;
        pt.setX(dStartX);
        pt.setY(dStartY);
        points.append(pt);

        pt.setX(dStartX + 5);
        points.append(pt);

        pt.setY(dStartY - m_nGain * g_nPixOfOneMM);
        points.append(pt);

        pt.setX(pt.x() + 10);
        points.append(pt);
        
        pt.setY(dStartY);
        points.append(pt);

        pt.setX(pt.x() + 5);
        points.append(pt);
        painter->drawPolyline(points);

        dStartY += dDistance;

        m_arrLeadStartPt[i] = pt;
        m_arrLeadCurPt[i] = pt;

    }
}

QVector<qreal> DDlgItem::CalLeadsY(QRect rect)
{
    //重上到下；0 1 2
    QVector<qreal> vecLeadsY(m_nShowLeadNum);


    for (int i = 0; i < m_nShowLeadNum; i++)
    {
        //vecLeadsY.push_back(dStartY + i * dDistance);
    }
    return QVector<qreal>();
}
