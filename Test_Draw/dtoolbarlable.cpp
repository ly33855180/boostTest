#include "dtoolbarlable.h"
#include <QPainter>
#include <qDebug>
#include "DCodeHelper.h"
#include <QTextCodec>

DToolBarLable::DToolBarLable(QWidget *parent)
    : QWidget(parent), m_qsText("..."), m_nWide(100)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

DToolBarLable::~DToolBarLable()
{

}

void DToolBarLable::setLable( QString  qsText, int nHeight)
{
    if (m_qsText != qsText)
    {
        m_qsText = qsText;
        QFont font;
        font.setFamily("ËÎÌו");
        int nMargin = 2;
        font.setPixelSize(nHeight - 2 * nMargin);
        
        QFontMetrics fm(font);
        QRect rec = fm.boundingRect(m_qsText);
        m_nWide = rec.width();
        
        update();
    }
}

void DToolBarLable::paintEvent(QPaintEvent *)
{
    //qDebug() << "********DToolBarLable****paintEvent!!!!!";
    int nMargin = 2;
    QPainter p(this);
    p.setPen(Qt::yellow);
	QRect re = rect() + QMargins(0, 0, -1, -1);
	//p.drawRect(re);
    {
        QRect re = rect() + QMargins(-nMargin, -nMargin, -nMargin, -nMargin);

        QFont font;
        font.setFamily("ËÎÌו");
		font.setPixelSize(rect().height() / 4);

        p.setFont(font);
        p.drawText(re, Qt::AlignHCenter  ,m_qsText);
        p.drawRect(re);
    }
}

