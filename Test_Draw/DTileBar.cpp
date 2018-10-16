#include "DTileBar.h"


#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QPainter>

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

DTileBar::DTileBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(30);

    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    m_pIconLabel->setFixedSize(30, 30);
    m_pIconLabel->setScaledContents(true);

    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_pMinimizeButton->setFixedSize(30, 30);
    m_pMaximizeButton->setFixedSize(30, 30);
    m_pCloseButton->setFixedSize(30, 30);


    m_pMinimizeButton->setIcon(QIcon("..\\..\\image\\min.png"));
    m_pMaximizeButton->setIcon(QIcon("..\\..\\image\\max1.png"));
    m_pCloseButton->setIcon(QIcon("..\\..\\image\\exit.png"));

    m_pMinimizeButton->setStyleSheet("QPushButton{background-color:black;\
       color: white;   border - radius: 0px;  border: 0px groove gray; \
        border - style: outset;}"
        "QPushButton:hover{background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(25, 134, 199, 0), stop:1 #5CACEE);}"
        "QPushButton:pressed{background-color:rgb(85, 170, 255);\
border - style: inset; }"
);

    m_pMaximizeButton->setStyleSheet("QPushButton{background-color:black;\
       color: white;   border - radius: 0px;  border: 0px groove gray; \
        border - style: outset;}"
        "QPushButton:hover{background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(25, 134, 199, 0), stop:1 #5CACEE);}"
        "QPushButton:pressed{background-color:rgb(85, 170, 255);\
border - style: inset; }"
);

    m_pCloseButton->setStyleSheet("QPushButton{background-color:black;\
       color: white;   border - radius: 0px;  border: 0px groove gray; \
        border - style: outset;}"
        "QPushButton:hover{background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(238, 0, 0, 128), stop:1 rgba(238, 44, 44, 255));}"
        "QPushButton:pressed{background-color:rgb(85, 170, 255);\
border - style: inset; }"
);


    m_pTitleLabel->setObjectName("whiteLabel");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pMaximizeButton->setObjectName("maximizeButton");
    m_pCloseButton->setObjectName("closeButton");

    m_pMinimizeButton->setToolTip("Minimize");
    m_pMaximizeButton->setToolTip("Maximize");
    m_pCloseButton->setToolTip("Close");

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);

    pLayout->addWidget(m_pIconLabel);
    pLayout->addStretch();
    //pLayout->addWidget(m_pTitleLabel);
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addWidget(m_pMaximizeButton);
    pLayout->addWidget(m_pCloseButton);


    setLayout(pLayout);

    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

    //setPalette(QPalette(Qt::black));
    //setAutoFillBackground(true);
}

DTileBar::~DTileBar()
{

}

void DTileBar::paintEvent(QPaintEvent *)
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

void DTileBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit m_pMaximizeButton->clicked();
}

void DTileBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pMaximizeButton)
        {
            if (pWindow->isMaximized())
            {
                pWindow->showNormal();
                m_pMaximizeButton->setIcon(QIcon("..\\..\\image\\max2.png"));
                m_pMaximizeButton->setToolTip(QStringLiteral("还原"));
            }
            else
            {
                pWindow->showMaximized();
                m_pMaximizeButton->setIcon(QIcon("..\\..\\image\\max1.png"));
                m_pMaximizeButton->setToolTip(QStringLiteral("最大化"));
            }
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
    }
}
