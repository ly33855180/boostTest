#include "DTestListWidget.h"


#include <QtDebug>
#include <QMessageBox>
#include <QListWidgetItem>      //列表框空间头文件
#include <QFileDialog>          //文件对话框控件
#include <QStringList>          //字符串容器
#include <QDir>                 //目录类头文件
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPushButton>
DTestListWidget::DTestListWidget(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	pwidget = new QListWidget(this);
	pwidget->setIconSize(QSize(200, 200));

	pwidget->setSpacing(10);
	//设置自动适应布局调整（Adjust适应，Fixed不适应），默认不适应
	pwidget->setResizeMode(QListWidget::Adjust);
	//设置不能移动
	pwidget->setMovement(QListWidget::Static);



	QVBoxLayout* playout = new QVBoxLayout(this);

	pwidget->setViewMode(QListView::IconMode);   //设置显示模式为图标模式

	playout->addWidget(pwidget);
	setLayout(playout);

	{
		QHBoxLayout* ph = new QHBoxLayout(this);

		QPushButton* padd = new QPushButton("add",this);
		padd->setFixedSize(100, 40);
		ph->addWidget(padd);

		QPushButton* pdel = new QPushButton("del", this);
		pdel->setFixedSize(100, 40);
		ph->addWidget(pdel);

		QPushButton* pclear = new QPushButton("clear", this);
		pclear->setFixedSize(100, 40);
		ph->addWidget(pclear);

		playout->addLayout(ph);

		QObject::connect(padd, SIGNAL(clicked()), this, SLOT(slotpadd()));
		QObject::connect(pdel, SIGNAL(clicked()), this, SLOT(slotpdel()));
		QObject::connect(pclear, SIGNAL(clicked()), this, SLOT(slotpclear()));
	}
}

DTestListWidget::~DTestListWidget()
{
}

void DTestListWidget::slotpadd()
{
	//QString str = "123";
	//QListWidgetItem *item = new QListWidgetItem; 
	//item->setText(str);                     //设置列表项的文本
	//pwidget->addItem(item);          //加载列表项到列表框


	QPixmap pix1(QString("F:\\test\\Test_Draw\\pic\\2.jpg"));
	QPixmap pix2(":/list/image/2.jpg");
	QListWidgetItem *item1 = new QListWidgetItem(QIcon(pix1.scaled(QSize(200, 200))), "rain");
	item1->setTextAlignment(Qt::AlignLeft);
	pwidget->addItem(item1);


}

void DTestListWidget::slotpclear()
{

}

void DTestListWidget::slotpdel()
{

}
