#include "dtoolbarbattery.h"
#include <QPainter>
#include <qDebug>
DToolBarBattery::DToolBarBattery(QWidget *parent)
    : QWidget(parent)
{
    //ui.setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

DToolBarBattery::~DToolBarBattery()
{

}

void DToolBarBattery::paintEvent(QPaintEvent *)
{
    int nMargin = 2;
    QPainter p(this);
    p.setPen(Qt::yellow);
    //QRect re = rect() + QMargins(0, 0, -1, -1);
    //p.drawRect(re);

    {
        QRect re = rect() + QMargins(-nMargin, -nMargin, -nMargin, -nMargin);
        //p.drawRect(re);

        int nSpaceY = re.height() / 3;
        int nSpaceX = nSpaceY;
        

        QPoint pt0(re.left(), re.top() + nSpaceY);
        QPoint pt1(pt0.x() + nSpaceX, pt0.y());
        QPoint pt2(pt1.x(), pt1.y() - nSpaceY);
        QPoint pt3(pt2.x() + re.width() - nSpaceX, pt2.y());
        QPoint pt4(pt3.x(), pt3.y() + re.height());
        QPoint pt5(pt1.x(), pt4.y());
        QPoint pt6(pt1.x(), pt5.y() - nSpaceY);
        QPoint pt7(pt0.x(), pt6.y());

        p.drawLine(pt0, pt1);
        p.drawLine(pt1, pt2);
        p.drawLine(pt2, pt3);
        p.drawLine(pt3, pt4);
        p.drawLine(pt4, pt5);
        p.drawLine(pt5, pt6);
        p.drawLine(pt6, pt7);
        p.drawLine(pt7, pt0);

        //draw "+" and "-"
        {
            QRect rectAdd;
            rectAdd.setTopLeft(pt0);
            rectAdd.setBottomRight(pt6);

            rectAdd.moveLeft(pt1.x());

            QFont font;
            font.setFamily("ËÎÌו");
            font.setPixelSize(rectAdd.height());

            p.setFont(font);
            p.drawText(rectAdd, Qt::AlignHCenter | Qt::AlignVCenter, "+");


            QRect rectSub(rectAdd);
            rectSub.moveLeft(re.width() - nSpaceX);
            p.drawText(rectSub, Qt::AlignHCenter | Qt::AlignVCenter, "-");
        }
        //draw text
        {
            QRect rectText;
            rectText.setTopLeft(pt2);
            rectText.setBottomRight(pt4);
            p.setPen(QColor(Qt::red));

            QFont font;
            font.setFamily("ËÎÌו");
            font.setPixelSize(rectText.height());
            p.setFont(font);
            p.drawText(rectText, Qt::AlignHCenter | Qt::AlignVCenter, "88");

        }

    }
}
