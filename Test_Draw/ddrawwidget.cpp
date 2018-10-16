#include "ddrawwidget.h"
#include "QPainter"
#include <QMouseEvent>

#include <QHBoxLayout>
#include <QMargins>
#include <QPen>
#include <QGridLayout>
#include "ddlgitem.h"
#include <QSizePolicy>
#include "DBoxSocket.h"

#include "DMonitorBox.h"
#include "DBoxManager.h"
DDrawWidget::DDrawWidget(QWidget *parent)
    : QWidget(parent)
	, m_nCurPageNum(0)
	, m_nMonFrameCount(0)
{
    //ui->setupUi(this);
    //setFixedSize(600, 500);    //窗口大小设置为600*500
    pix = QPixmap(size());
    pix.fill(Qt::white);
    isDrawing = false;

    pLayout = new QGridLayout(this);
    pLayout->setMargin(0);
    int nDis = 2;
    // 设置水平间距
    pLayout->setHorizontalSpacing(nDis);
    // 设置垂直间距
    pLayout->setVerticalSpacing(nDis);
    // 设置外间距
    pLayout->setContentsMargins(2*nDis, 2*nDis, 2*nDis, 2*nDis);
    
    setLayout(pLayout);

    

    for (int i = 0; i < 12 ; i++)
    {
        //m_leadData.LoadLeadData(i);
    }

	onClicked_2X2();

    m_loginThread = boost::thread(boost::bind(&DDrawWidget::LoginServer, this));

	connect(this, SIGNAL(sig_LogoInFinish()), this, SLOT(slot_LogoInFinish()));


	m_thread = boost::thread(boost::bind(&DDrawWidget::WorkThread, this));
}
/*获得dpi：图像每英寸面积内的像素点数
1英寸等于2.54cm*/
qreal DDrawWidget::MMToPixel(qreal mm)
{
    return mm / 25.4 * logicalDpiX();
}
DDrawWidget::~DDrawWidget()
{
    if (m_ptrLoginServer)
    {
        m_ptrLoginServer->StopStartGetMdData();
    }
	m_loginThread.join();
}

void DDrawWidget::LayOutUI(int nRow, int nCol)
{
    if((nRow == m_nPreRow)&&(nCol == m_nPreCol))
    {
        return;
    }

    for (int i = 0; i < m_nPreCol; i++)
    {
        pLayout->setColumnStretch(i, 0);
    }

	if (m_ptrTimer)
	{
		m_ptrTimer->cancel();
		m_ptrTimer = boost::shared_ptr<boost::asio::deadline_timer>();
	}
    m_nPreRow = nRow;
    m_nPreCol = nCol;

	m_nCurPageNum = 0;
	m_nShowCountOfPage = nRow * nCol;


	for (size_t i = 0; i < m_vecItems.size(); i++)
	{
		QVector<DDlgItem*>& vecRow = m_vecItems[i];
		for (size_t j = 0; j < vecRow.size(); j++)
		{
			DDlgItem* pItem = vecRow[j];
			if (pItem)
			{
				pItem->setParent(NULL);
				pLayout->removeWidget(pItem);
			}
		}
	}


    QLayoutItem *child;
    while ((child = pLayout->takeAt(0)) != 0) {
            delete child;
    }

	//
	for (size_t i = 0; i < m_vecItems.size(); i++)
	{
		QVector<DDlgItem*>& vecRow = m_vecItems[i];
		for (size_t j = 0; j < vecRow.size(); j++)
		{
			DDlgItem* pItem = vecRow[j];
			if (pItem)
			{
				delete pItem;
				pItem = NULL;
			}
		}
		vecRow.clear();
	}
	m_vecItems.clear();

	for (int i = 0; i < nCol; i++)
	{
		pLayout->setColumnStretch(i, 1);
	}

    for (int i = 0; i < nRow; i++)
    {
		QVector<DDlgItem*> vecRow;
        for (int j = 0; j < nCol; j++)
        {
            DDlgItem* pitem = new DDlgItem();
            pitem->setRowAndCol(i, j);
            pLayout->addWidget(pitem, i, j);
			vecRow.push_back(pitem);

        }
		m_vecItems.push_back(vecRow);
    }

}

void DDrawWidget::paintEvent(QPaintEvent *)
{
    QPixmap pix(size());
    //pix.fill(QColor(195,195,195));
    pix.fill(Qt::gray);
    QPainter p(this);
    p.drawPixmap(0, 0, pix);
}

void DDrawWidget::LoginServer()
{
    m_ptrLoginServer = boost::shared_ptr<DLoginServer>(new DLoginServer);
    if (m_ptrLoginServer)
    {
        m_ptrLoginServer->StartGetMdData(boost::bind(&DDrawWidget::LoginHandle, this, _1, _2));
    }
}

void DDrawWidget::LoginHandle(const s_Md& sMDInfo, bool bOk)
{
    sMDInfo.log();

    vector<sMonitorStation>::const_iterator iter = std::find_if(sMDInfo.m_vecMonitorStation.begin(), sMDInfo.m_vecMonitorStation.end(), [&](sMonitorStation item)
    {
        return  item.m_qsID == QString("001");
     
    });

    if (iter == sMDInfo.m_vecMonitorStation.end())
    {
        return;
    }

    const sMonitorStation & monitorStation = *iter;

	m_nMonFrameCount = monitorStation.m_vecMonFrame.size();
    if (0 == m_nMonFrameCount)
    {
        return;
    }

	m_sMonitorStation = monitorStation;
	/**/
	vector<sMonFrame> vecMonFrame;
	int nIndex = 341701186;
	m_sMonitorStation.m_vecMonFrame.clear();
	m_sMonitorStation.m_vecMonFrame.swap(vector<sMonFrame>());
	for (int i = 0; i < 49; i++)
	{
		sMonFrame item;
		item.m_nNo = i + 1;
		item.m_qsNO = QString::number(i + 1);
		item.m_qsDEV_IDX = QString("C") + QString::number(nIndex);
		nIndex++;
		m_sMonitorStation.m_vecMonFrame.push_back(item);
	}
	/**/

    sig_LogoInFinish();
}

void DDrawWidget::showEvent(QShowEvent * event)
{
	//最小化时，再弹出时;
	QSize oldsize = size();
	resize(QSize(0, 0));
	resize(oldsize);
}

void DDrawWidget::onClicked_2X2()
{
    LayOutUI(2, 2);
    m_eShowCountOfPage = EShowCountOfPage_2X2;

	m_nPageCounts = int((m_nMonFrameCount / m_nShowCountOfPage) + 0.5);
	ShowBoxsOfCurPage(m_eShowCountOfPage, m_nCurPageNum, m_nShowCountOfPage);
	sig_ChangeLable(m_nCurPageNum, m_nPageCounts, m_nMonFrameCount);
}

void DDrawWidget::onClicked_2X3()
{
    LayOutUI(2, 3);
    m_eShowCountOfPage = EShowCountOfPage_2X3;

	m_nPageCounts = int((m_nMonFrameCount / m_nShowCountOfPage) + 0.5);
	ShowBoxsOfCurPage(m_eShowCountOfPage, m_nCurPageNum, m_nShowCountOfPage);
	sig_ChangeLable(m_nCurPageNum, m_nPageCounts, m_nMonFrameCount);
}

void DDrawWidget::onClicked_3X3()
{
    LayOutUI(3, 3);
    m_eShowCountOfPage = EShowCountOfPage_3X3;
	m_nPageCounts = int((m_nMonFrameCount / m_nShowCountOfPage) + 0.5);

	ShowBoxsOfCurPage(m_eShowCountOfPage, m_nCurPageNum, m_nShowCountOfPage);
	sig_ChangeLable(m_nCurPageNum, m_nPageCounts, m_nMonFrameCount);
}

void DDrawWidget::onClicked_7X7()
{
    LayOutUI(7, 7);
    m_eShowCountOfPage = EShowCountOfPage_7X7;

	m_nPageCounts = int((m_nMonFrameCount / m_nShowCountOfPage) + 0.5);

	ShowBoxsOfCurPage(m_eShowCountOfPage, m_nCurPageNum, m_nShowCountOfPage);
	sig_ChangeLable(m_nCurPageNum, m_nPageCounts, m_nMonFrameCount);
}

void DDrawWidget::onClicked_NextPage()
{
	if (m_nCurPageNum == m_nPageCounts)
	{
		return;
	}
	m_nCurPageNum++;
	ShowBoxsOfCurPage(m_eShowCountOfPage, m_nCurPageNum, m_nShowCountOfPage);
	sig_ChangeLable(m_nCurPageNum, m_nPageCounts, m_nMonFrameCount);
	
}

void DDrawWidget::onClicked_PrePage()
{
	if (0 == m_nCurPageNum)
	{
		return;
	}
	m_nCurPageNum--;
	ShowBoxsOfCurPage(m_eShowCountOfPage, m_nCurPageNum, m_nShowCountOfPage);
	sig_ChangeLable(m_nCurPageNum, m_nPageCounts, m_nMonFrameCount);
}

void DDrawWidget::ShowBoxsOfCurPage(EShowCountOfPage eShowCountOfPage, int nCurPageNum, int nCount)
{
	int nFrameIndex = nCurPageNum * nCount;
	const vector<sMonFrame> &vecMonFrame = m_sMonitorStation.m_vecMonFrame;

	for (int nRow = 0; nRow < m_nPreRow; nRow ++)
	{
		for (int nCol = 0; nCol < m_nPreCol; nCol++)
		{
			DDlgItem* pItem = m_vecItems[nRow][nCol];

			pItem->SetEmptyMonFrame();
			if (nFrameIndex < vecMonFrame.size())
			{
				const sMonFrame& m0 = vecMonFrame.at(nFrameIndex);
				pItem->SetMonFrame(m0);
				nFrameIndex++;
			}
		}
	}
	if (!m_ptrTimer)
	{
		m_ptrTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(m_io, boost::posix_time::seconds(2)));
		m_ptrTimer->async_wait(boost::bind(&DDrawWidget::handle_timer, this, boost::asio::placeholders::error, m_ptrTimer.get()));
	}
}


void DDrawWidget::WorkThread()
{
	m_work.reset(new boost::asio::io_service::work(m_io));
	m_io.run();
}

void DDrawWidget::slot_LogoInFinish()
{
	m_nPageCounts = int((m_nMonFrameCount / m_nShowCountOfPage) + 0.5);
	m_nCurPageNum = 0;

	DBoxManager::Instance()->Init(m_sMonitorStation);
	
	ShowBoxsOfCurPage(m_eShowCountOfPage, m_nCurPageNum, m_nShowCountOfPage);
	sig_ChangeLable(m_nCurPageNum, m_nPageCounts, m_nMonFrameCount);
	showEvent(NULL);

	//m_ptrTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(m_io, boost::posix_time::seconds(2)));
	//m_ptrTimer->async_wait(boost::bind(&DDrawWidget::handle_timer, this, boost::asio::placeholders::error, m_ptrTimer.get()));
}

void DDrawWidget::handle_timer(const boost::system::error_code& e, boost::asio::deadline_timer* t)
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
    //
	for (size_t i = 0; i < m_vecItems.size(); i++)
	{
		QVector<DDlgItem*>& vecRow = m_vecItems[i];
		for (size_t j = 0; j < vecRow.size(); j++)
		{
			DDlgItem* pItem = vecRow[j];
			if (pItem)
			{
				pItem->timeOut();
			}
		}
	}
	//
	t->expires_at(t->expires_at() + boost::posix_time::millisec(100));
	t->async_wait(boost::bind(&DDrawWidget::handle_timer, this, boost::asio::placeholders::error, t));
}