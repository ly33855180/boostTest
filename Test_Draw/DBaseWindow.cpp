#include "DBaseWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "DTileBar.h"
#include "DStateBar.h"
#include "dtoolbar.h"
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QApplication>
#include <QDesktopWidget>

#include "DDrawWidget.h"
DBaseWindow::DBaseWindow(QWidget *parent)
    : QWidget(parent)
    , m_pTileBar(NULL)
    , m_pStateBar(NULL)
    , mIsMax(false)
{
    
    setWindowFlags(Qt::FramelessWindowHint);
    QVBoxLayout* pVLayout = new QVBoxLayout(this);
    setLayout(pVLayout);

    pVLayout->setMargin(0);
    pVLayout->setSpacing(0);
    m_pTileBar = new DTileBar(this);

    pVLayout->addWidget(m_pTileBar);
    
    m_pToolBar = new DToolBar(this);
    pVLayout->addWidget(m_pToolBar);

    m_pDrawWidget = new DDrawWidget(this);
    pVLayout->addWidget(m_pDrawWidget);
    m_pStateBar = new DStateBar(this);
    pVLayout->addWidget(m_pStateBar);

    m_pStateBar->GetDragLable()->installEventFilter(this);

    //
    //connect(m_pToolBar->m_pBtn_2X2, &QPushButton::clicked, m_pDrawWidget, [=] 
    //{
    //    m_pDrawWidget->LayOutUI(2, 2);
    //});
	connect(m_pToolBar->m_pBtn_2X2, SIGNAL(clicked(bool)), m_pDrawWidget, SLOT(onClicked_2X2()));
    connect(m_pToolBar->m_pBtn_2X3, SIGNAL(clicked(bool)), m_pDrawWidget, SLOT(onClicked_2X3()));
    connect(m_pToolBar->m_pBtn_3X3, SIGNAL(clicked(bool)), m_pDrawWidget, SLOT(onClicked_3X3()));
    connect(m_pToolBar->m_pBtn_7X7, SIGNAL(clicked(bool)), m_pDrawWidget, SLOT(onClicked_7X7()));

	connect(m_pToolBar->m_pBtn_Next, SIGNAL(clicked(bool)), m_pDrawWidget, SLOT(onClicked_NextPage()));
	connect(m_pToolBar->m_pBtn_Pre, SIGNAL(clicked(bool)), m_pDrawWidget, SLOT(onClicked_PrePage()));

	connect(m_pDrawWidget, SIGNAL(sig_ChangeLable(int, int , int)), m_pToolBar, SLOT(slot_ChangeLable(int, int, int)));
}

DBaseWindow::~DBaseWindow()
{

}
bool DBaseWindow::eventFilter(QObject *obj, QEvent *e)
{
    if (qobject_cast<QLabel*>(obj) == m_pStateBar->GetDragLable())
    {
        //实现拖动右下角缩放窗口
        if (e->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *event = (QMouseEvent *)e;
            if (event->buttons() & Qt::LeftButton)
            {
                if (this->isMaximized())
                {
                    //已最大化，就不让再拖动
                    return true;
                }
                mZoom = true;
                mZoomLocation = geometry();
                mZoomPos = event->globalPos();
                return true;
            }
        }
        else if (e->type() == QEvent::MouseMove)
        {
            QMouseEvent *event = (QMouseEvent *)e;
            if (mZoom && (event->buttons() & Qt::LeftButton))
            {
                int dx = event->globalPos().x() - mZoomPos.x();
                int dy = event->globalPos().y() - mZoomPos.y();
                QRect rc = mZoomLocation;
                rc.setRight(rc.right() + dx);
                rc.setBottom(rc.bottom() + dy);
                setGeometry(rc);
                update();
                return true;
            }
        }
        else if (e->type() == QEvent::MouseButtonRelease)
        {
            mZoom = false;
            return true;
        }
    }
    return QObject::eventFilter(obj, e);
}

void DBaseWindow::mousePressEvent(QMouseEvent *e)//鼠标按下事件
{
    if (e->button() == Qt::LeftButton)
    {
        mDrag = true;
        mDragPos = e->globalPos() - pos();
        e->accept();
    }
}

void DBaseWindow::mouseMoveEvent(QMouseEvent *e)//鼠标移动事件
{
    if (mDrag && (e->buttons() && Qt::LeftButton))
    {
        if (!this->isMaximized())
        {
            move(e->globalPos() - mDragPos);
        }
        e->accept();
    }
}

void DBaseWindow::mouseReleaseEvent(QMouseEvent *e)//鼠标释放事件
{
    mDrag = false;
}

QSize DBaseWindow::sizeHint() const
{
    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect desktopRect = desktopWidget->availableGeometry();
    return (QSize(desktopRect.width(), desktopRect.height()));
}
