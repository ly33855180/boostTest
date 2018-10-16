#include "DMainWindow.h"
#include "DTileBar.h"
#include <QVBoxLayout>
DMainWindow::DMainWindow(QWidget *parent)
    : QWidget(parent)
{
    //ui.setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | windowFlags());

    DTileBar *pTitleBar = new DTileBar(this);
    installEventFilter(pTitleBar);

    resize(400, 300);
    setWindowTitle("Custom Window");
    setWindowIcon(QIcon(":/Images/logo"));

    //QPalette pal(palette());
    //pal.setColor(QPalette::Background, QColor(50, 50, 50));
    //setAutoFillBackground(true);
    //setPalette(pal);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pTitleBar);
    pLayout->addStretch();
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(pLayout);
}

DMainWindow::~DMainWindow()
{

}
