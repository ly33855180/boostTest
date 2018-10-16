#include "DTestListWidget.h"


#include <QtDebug>
#include <QMessageBox>
#include <QListWidgetItem>      //�б��ռ�ͷ�ļ�
#include <QFileDialog>          //�ļ��Ի���ؼ�
#include <QStringList>          //�ַ�������
#include <QDir>                 //Ŀ¼��ͷ�ļ�
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
	//�����Զ���Ӧ���ֵ�����Adjust��Ӧ��Fixed����Ӧ����Ĭ�ϲ���Ӧ
	pwidget->setResizeMode(QListWidget::Adjust);
	//���ò����ƶ�
	pwidget->setMovement(QListWidget::Static);



	QVBoxLayout* playout = new QVBoxLayout(this);

	pwidget->setViewMode(QListView::IconMode);   //������ʾģʽΪͼ��ģʽ

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
	//item->setText(str);                     //�����б�����ı�
	//pwidget->addItem(item);          //�����б���б��


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
