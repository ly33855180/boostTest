#include "test_draw.h"
#include <QtWidgets/QApplication>

#include <vector>
#include <iostream>
#include <queue>
using namespace std;

void show (const std::vector<int> &vecData)
{
    for (int i = 0; i < vecData.size(); i++)
    {
        cout <<vecData[i] << ",";
    }
    cout << "\n";
}
void WorkThread0()
{
	while (true)
	{
		cout << "WorkThread0"<<endl;
	}
}

void WorkThread1()
{
	while (true)
	{
		cout << "WorkThread1" << endl;
	}
}
#include <boost\\thread.hpp>
#include <boost\\shared_ptr.hpp>
class Tea : public boost::enable_shared_from_this<Tea>
{
public:
	Tea();
	~Tea();

private:

};

Tea::Tea()
{
}

Tea::~Tea()
{
	int a = 10;
}
typedef boost::shared_ptr<Tea> ptrTea;
#include <QVector>
#include <QMap>
void test()
{
	//
	QMap<QString, ptrTea> vec;
	for (int i = 0; i < 10; i++)
	{
		QString qsKey = QString::number(i);
		ptrTea p = ptrTea(new Tea);
		vec.insert(qsKey, p);
	}
	vec.clear();
	//boost::thread m_thread = boost::thread(boost::bind(&WorkThread0));
	//	m_thread = boost::thread(boost::bind(&WorkThread1));
    string ss = "111111";
    QString ssss = "333333";
    //int a[3] = { 1,2,3 };
    //vector<int> v;// (a, a + 3);
    //v.insert(v.end(), a, a + 3);
    //int a = 11111111 * 4440000000000;
    //vector<int> vec;
    //for (int i = 0;i < 10;i ++)
    //{
    //    vec.push_back(i);
    //}
    //int arr[10];
    //memcpy(arr, &vec[0], 10 * 4);
    //QString str0 = QString("你好中国");
    //QString str1 = QString::fromLocal8Bit("你好中国");
    //std::vector<int> vecData;
    //
    //for (int i = 0; i < 10; i++)
    //{
    //    vecData.push_back(i);
    //}
    //std::vector<int>::iterator iter = find(vecData.begin(), vecData.end(), 3);
    //vecData.erase(vecData.begin(), iter);
    //show(vecData);
}
#include "DMainWindow.h"
#include "DBaseWindow.h"
#include "DTestListWidget.h"
#include "DOptDB.h"

#include "DTestCurContrl.h"

#include "DUI_test.h"
int main(int argc, char *argv[])
{
	qRegisterMetaType<sPackageData>("sPackageData");
	qRegisterMetaType<sPackageData>("sPackageData&");
    test();
    QApplication a(argc, argv);
    //Test_Draw w;
   //DBaseWindow w;
	//DTestListWidget w;
	//DTestCurContrl w;
	DUI_test w;
	w.showMaximized();
    return a.exec();
}
