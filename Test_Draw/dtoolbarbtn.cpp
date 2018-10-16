#include "dtoolbarbtn.h"
#include <QPainter>
DToolBarBtn::DToolBarBtn(QWidget *parent)
    : QPushButton(parent)
{
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //setFlat(true);//就是这句实现按钮透明的效果。  

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

DToolBarBtn::~DToolBarBtn()
{

}
/**/
void DToolBarBtn::paintEvent(QPaintEvent *)
{

    int nMargin = 2;
    QPainter p(this);
    //p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::yellow);
    QRect re = rect() + QMargins(-nMargin, -nMargin, -nMargin, -nMargin);
    //p.drawRect(re);
    {
        p.drawEllipse(re);//画圆
        //p.drawArc(re, 0, 16*360);

        QPointF ptCenter = re.center();
        int nSpace = re.height() / 2;

        QPointF ptH0(ptCenter.x() - nSpace, ptCenter.y());
        QPointF ptH1(ptCenter.x() + nSpace, ptCenter.y());

        QPointF ptV0(ptCenter.x(), ptCenter.y() - nSpace);
        QPointF ptV1(ptCenter.x(), ptCenter.y() + nSpace);

        p.drawLine(ptH0, ptH1);
        p.drawLine(ptV0, ptV1);
    }
}