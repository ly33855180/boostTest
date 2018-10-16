#include "test_draw.h"
#include "ddrawwidget.h"
#include "QAction"
#include "QMenu"
#include <QTimer>

#include "dtesttable.h"
#include <QDesktopWidget>
#include "DParseData.h"


Test_Draw::Test_Draw(QWidget *parent)
    : QMainWindow(parent)
{
    //
    pwidget = new DDrawWidget(this);
    setCentralWidget(pwidget);

    m_openAction11 = new QAction(tr("1*1"), this);  //初始化动作  
    m_openAction22 = new QAction(tr("2*2"), this);  //初始化动作  
    m_openAction23 = new QAction(tr("2*3"), this);  //初始化动作  
    m_openAction33 = new QAction(tr("3*3"), this);  //初始化动作 
    m_openAction77 = new QAction(tr("7*7"), this);  //初始化动作  
    m_openAction99 = new QAction(tr("9*9"), this);  //初始化动作  

    m_fileMenu = new QMenu;  //创建一个菜单  
    m_fileMenu = menuBar()->addMenu(tr("n*m"));  //将菜单添加到菜单栏上  
    m_fileMenu->addAction(m_openAction11);  //将动作添加到菜单上
    m_fileMenu->addAction(m_openAction22);  //将动作添加到菜单上
    m_fileMenu->addAction(m_openAction23);  //将动作添加到菜单上
    m_fileMenu->addAction(m_openAction33);  //将动作添加到菜单上
    m_fileMenu->addAction(m_openAction77);  //将动作添加到菜单上
    m_fileMenu->addAction(m_openAction99);  //将动作添加到菜单上

    connect(m_openAction11, SIGNAL(triggered()), this, SLOT(slotOpenFile11()));
    connect(m_openAction22, SIGNAL(triggered()), this, SLOT(slotOpenFile22()));
    connect(m_openAction23, SIGNAL(triggered()), this, SLOT(slotOpenFile23()));
    connect(m_openAction33, SIGNAL(triggered()), this, SLOT(slotOpenFile33()));
    connect(m_openAction77, SIGNAL(triggered()), this, SLOT(slotOpenFile77()));
    connect(m_openAction99, SIGNAL(triggered()), this, SLOT(slotOpenFile99()));

    m_openAction_testtable = new QAction(tr("test_table"), this);  //初始化动作 
    m_fileMenu = menuBar()->addMenu(tr("test"));  //将菜单添加到菜单栏上
    m_fileMenu->addAction(m_openAction_testtable);  //将动作添加到菜单上
    connect(m_openAction_testtable, SIGNAL(triggered()), this, SLOT(slot_testtable()));

    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //timer->start(1000);
    pwidget->LayOutUI(1, 1);



    int desktop_width = QApplication::desktop()->width();
    int desktop_high = QApplication::desktop()->height();
    pwidget->setMaximumSize(desktop_width, desktop_high);
}

Test_Draw::~Test_Draw()
{

}

void Test_Draw::slotOpenFile11()
{
    int a = 10;
    pwidget->LayOutUI(1, 1);

}

void Test_Draw::slotOpenFile22()
{
    int a = 10;
    pwidget->LayOutUI(2, 2);

}

void Test_Draw::slotOpenFile23()
{
    int a = 10;    
    pwidget->LayOutUI(2, 3);

}

void Test_Draw::slotOpenFile33()
{
    int a = 10;
    pwidget->LayOutUI(3, 3);
}

void Test_Draw::slotOpenFile77()
{
    int a = 10;
    pwidget->LayOutUI(7, 7);
}

void Test_Draw::slotOpenFile99()
{
    int a = 10;
    pwidget->LayOutUI(9, 9);
}
#include "DBoxSocket.h"
#include "DOptDB.h"
boost::shared_ptr<DBoxSocket> g_pb;


void showData(const vector<int>& vecData)
{
    for (int i = 0; i < vecData.size(); i++)
    {
        std::cout << vecData.at(i) << " ,";
    }
    std::cout << endl;
}
void fun_test()
{
    //vector<int> vecData;
    //for (int i = 0 ; i < 10; i++)
    //{
    //    vecData.push_back(i);
    //}
    //showData(vecData);
    //std::cout <<"11111111111111"<< endl;
    //vector<int> vecTemp;
    //vecTemp.assign(vecData.begin(), vecData.begin() + 5);
    //vecData.erase(vecData.begin(), vecData.begin() + 5);
    //showData(vecTemp);
    //std::cout << "222222222222" << endl;
    //showData(vecData);
    //std::vector<unsigned char> m_vecRecvBufTemp(2064);

    //while (true)
    //{
    //    int  nsize = g_pb->m_vecRecvBuf.size();
    //    if (g_pb->m_vecRecvBuf.size() >= 2064)
    //    {
    //        DParseData d;
    //        d.StartParse(g_pb->m_vecRecvBuf);

    //        m_vecRecvBufTemp.assign(m_vecRecvBufTemp.begin(), m_vecRecvBufTemp.begin() + 2064);
    //        m_vecRecvBufTemp.erase(m_vecRecvBufTemp.begin(), m_vecRecvBufTemp.begin() + 2064);


    //    }
    //    DOptDB::Instance()->addData(m_vecRecvBufTemp);
    //    Sleep(1000);
    //}


    //while (true)
    //{
    //    std::vector<unsigned char> vecData;
    //    DOptDB::Instance()->queryData(vecData);
    //    Sleep(1000);
    //}


}


void Test_Draw::slot_testtable()
{
    //g_pb = boost::shared_ptr<DBoxSocket>(new DBoxSocket("127.0.0.1", 4004));
    //g_pb->StartGetMdData();

    boost::thread thrd(&fun_test);
  //  thrd.join();

    

    //DTestTable* table = new DTestTable();
    //table->resize(800, 800);
    //table->show();
}

void Test_Draw::update()
{
    static int nStep = 0;
    switch (nStep % 4)
    {
    case 0: pwidget->LayOutUI(2, 2);
        break;

    case 1: pwidget->LayOutUI(2, 3);
        break;

    case 2: pwidget->LayOutUI(3, 3);
        break;

    case 3: pwidget->LayOutUI(7, 7);
        break;

    default:
        break;
    }
    nStep++;
}
