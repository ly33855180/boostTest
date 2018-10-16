#include "DStateBar.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QPainter>
#include <QPixmap>
DStateBar::DStateBar(QWidget *parent)
    : QWidget(parent), m_pDragLabel(NULL)
{
    int nW = 16;
    setFixedHeight(nW);

    m_pDragLabel = new QLabel(this);
    m_pDragLabel->setFixedSize(nW, nW);
    QPixmap pixmap(QString("..\\..\\image\\WndZoom.png"));

    QPixmap fitpixmap = pixmap.scaled(nW, nW, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_pDragLabel->setPixmap(fitpixmap);

    QHBoxLayout* pHLayout = new QHBoxLayout(this);
    pHLayout->setMargin(0);
    pHLayout->addStretch();
    pHLayout->addWidget(m_pDragLabel);

    //setPalette(QPalette(Qt::black));
    //setAutoFillBackground(true);

    m_pDragLabel->setCursor(Qt::SizeFDiagCursor);
}

DStateBar::~DStateBar()
{

}

void DStateBar::paintEvent(QPaintEvent *)
{
    //QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing, true);
    //QPen pen;
    //pen.setWidth(1);
    //pen.setStyle(Qt::SolidLine);
    //pen.setColor(Qt::red);
    //painter.setPen(pen);
    //QRect rect0 = rect();
    //painter.drawRect(rect0);
}
