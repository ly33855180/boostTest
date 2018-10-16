#include "dtoolbarsignal.h"
#include <QPainter>
#include <qDebug>
DToolBarSignal::DToolBarSignal(QWidget *parent)
    : QWidget(parent)
{

}

DToolBarSignal::~DToolBarSignal()
{

}

void DToolBarSignal::paintEvent(QPaintEvent *)
{
    int nMargin = 2;

    QPainter p(this);
    //p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::yellow);
    //QRect re = rect() + QMargins(0, 0, -1, -1);
    //p.drawRect(re);

    {
        QRect re = rect() + QMargins(-nMargin, -nMargin, -nMargin, -nMargin);
        //p.drawRect(re);

        int nSpaceX = re.width() / 6;
        int sSpaceY = re.height() / 2 / 4;

        //1
            QPoint pt0(re.left(), re.top());
            QPoint pt1(pt0.x() + 2 * nSpaceX, pt0.y());
            QPoint pt2(pt0.x() + nSpaceX, pt0.y() + 2 * sSpaceY);

            p.drawLine(pt0, pt1);
            p.drawLine(pt0, pt2);
            p.drawLine(pt1, pt2);

            p.drawLine(pt2, QPoint(pt2.x(), re.top() + re.height()));
        
         //2
        QPoint ptS(pt1.x(), pt1.y() + re.height());
        QPoint ptE(ptS.x(), ptS.y() - re.height() / 2);
        for (int i = 0; i < 5; i++)
        {
            p.drawLine(ptS, ptE);
            ptS.rx() += nSpaceX;

            ptE.rx() += nSpaceX;
            ptE.ry() -= sSpaceY;

        }
    }
}
