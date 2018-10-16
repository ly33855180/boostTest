#ifndef DDRAWWIDGET_H
#define DDRAWWIDGET_H

#include <QWidget>
#include "ui_ddrawwidget.h"
#include <QPixmap>
#include <QVector>

#include "dleaddatas.h"
class QGridLayout;
class DDlgItem;

#include "DLoginServer.h"
#include <DData.h>


#include <boost/asio/placeholders.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_ptr.hpp>

class DDrawWidget : public QWidget
{
	Q_OBJECT

		enum EShowCountOfPage
	{
		EShowCountOfPage_2X2 = 0,
		EShowCountOfPage_2X3,
		EShowCountOfPage_3X3,
		EShowCountOfPage_7X7,
	};
public:
	DDrawWidget(QWidget *parent = 0);
	~DDrawWidget();

	void LayOutUI(int nRow, int nCol);
protected:
	void paintEvent(QPaintEvent *);

private:
	QPixmap pix;
	QPoint lastPoint;
	QPoint endPoint;
	QPixmap tempPix; //临时画布
	bool isDrawing;   //标志是否正在绘图

	qreal MMToPixel(qreal mm);

	QGridLayout *pLayout;

	QVector<QVector<DDlgItem*>> m_vecItems;
	int m_nPreRow;
	int m_nPreCol;
public:
	DLeadDatas m_leadData;
private:
	void LoginServer();

	boost::shared_ptr<DLoginServer> m_ptrLoginServer;

	void LoginHandle(const s_Md& sMDInfo, bool bOk);

	void showEvent(QShowEvent *event);
	boost::thread m_loginThread;

	public slots :
	void onClicked_2X2();
	void onClicked_2X3();
	void onClicked_3X3();
	void onClicked_7X7();

	void onClicked_NextPage();
	void onClicked_PrePage();

	void slot_LogoInFinish();

private:
	sMonitorStation m_sMonitorStation;
	int m_nMonFrameCount;
	int m_nCurPageNum;//index start is 1;
	int m_nPageCounts;
	EShowCountOfPage m_eShowCountOfPage;
	int m_nShowCountOfPage;
	void ShowBoxsOfCurPage(EShowCountOfPage eShowCountOfPage, int nCurPageNum, int nCount);

signals:
	void sig_LogoInFinish();
	void sig_ChangeLable(int nCurPage, int nPageCount, int nMonFrameCounts);

private:
	boost::scoped_ptr<boost::asio::io_service::work> m_work;
	boost::asio::io_service m_io;//定时器io;
	boost::thread m_thread;
	void WorkThread();

	boost::shared_ptr<boost::asio::deadline_timer> m_ptrTimer;//定时器;
	void handle_timer(const boost::system::error_code&, boost::asio::deadline_timer* t);
};
#endif // DDRAWWIDGET_H
