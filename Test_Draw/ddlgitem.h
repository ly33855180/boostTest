#ifndef DDLGITEM_H
#define DDLGITEM_H

#include <QWidget>
#include "ui_ddlgitem.h"
#include <vector>
using namespace std;
#include "QPointF"
#include <QGridLayout>
#include "DLeadDatas.h"


#include <boost/asio/placeholders.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>

#include "qitemtoolbardlg.h"
#include "DBoxSocket.h"
#include "DData.h"
class DDlgItem : public QWidget
{
    Q_OBJECT

public:
    DDlgItem(QWidget *parent = 0);
    ~DDlgItem();
    void LoadData(const DLeadDatas & data);

    void setRowAndCol(int nRow, int nCol);
    int m_nRow;
    int m_nCol;
    DLeadDatas m_leadData;

    int m_nStep;

	void SetMonFrame(const sMonFrame & m0);
	void SetEmptyMonFrame();
	bool m_bClearDraw;
	sMonFrame m_sMonFrame;
private:
    Ui::DDlgItem ui;
    int m_nShowLeadNum;
    int m_nGain;
    QVector<double> m_vecData;

    //÷ÿ…œµπœ¬ 0,1,2,3;
    QPointF m_arrLeadStartPt[12];
    QPointF m_arrLeadCurPt[12];

    QItemToolBarDlg* m_toolBar;
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);

	void showEvent(QShowEvent *event);
	void show();

    bool m_bUpadataBK;
    QPixmap m_pix;
    QPixmap m_pixLeadData;
    void mousePressEvent(QMouseEvent *event);

    void drawBkGrid(QPainter *painter, QRect &rect);
    void showLeadName(QPainter *painter, QRect &rect, int box);

    QVector<qreal> CalLeadsY(QRect rect);
    inline qreal MMToPixel(qreal mm)
    {
        return mm / 25.4 * logicalDpiX();
    }

    QTimer *timer;
    bool m_bFocus;
public slots:
    void _update();
	void slotGetLeadDataCallBack(const sPackageData& leadData, int nTag);

public:

    void handle_timer(const boost::system::error_code&, boost::asio::deadline_timer* t);
	void timeOut()
	{
		emit sigTimeOut();
	}

signals:
    void sigTimeOut();
	void sigGetLeadDataCallBack(const sPackageData& leadData, int nTag);
private:
    void GetLeadDataCallBack(const sPackageData& leadData, int nTag);

	void createUI();
};

#endif // DDLGITEM_H
