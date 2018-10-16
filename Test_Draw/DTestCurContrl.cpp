#include "DTestCurContrl.h"
#include <QSplitter>
#include <QLabel>
#include <QTextEdit>
#include <QFont>
#include <QHBoxLayout>
#include "ddlgitem.h"

#include <QScrollArea>
DTestCurContrl::DTestCurContrl(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);


	QFont font("ZYSong18030", 12);//指定显示字体
	//a.setFont(font);
	QHBoxLayout* ph = new QHBoxLayout(this);
	QSplitter *splitterMain;
	QTextEdit *textleft;
	QSplitter *splitterRight;
	QTextEdit *textUp;
	QTextEdit *textBottom;
	splitterMain = new QSplitter(Qt::Horizontal, this);                   //Horizontal:水平的
	//textleft = new QTextEdit(QObject::tr("Left Widget"), splitterMain);
	//textleft->setAlignment(Qt::AlignCenter);
	//右部分分割窗口
	//splitterRight = new QSplitter(Qt::Vertical, splitterMain);        //Vertical：垂直的
	//splitterRight->setOpaqueResize(false);                                    //Opaque：不透明的
	//textUp = new QTextEdit(QObject::tr("Top Widget"), splitterRight);
	//textUp->setAlignment(Qt::AlignCenter);
	//textBottom = new QTextEdit(QObject::tr("Bottom Widget"), splitterMain);
	//textBottom->setAlignment(Qt::AlignCenter);
	DDlgItem* pitem = new DDlgItem();
	splitterMain->addWidget(pitem);
	DPatientInfoDlg *pdlg = new DPatientInfoDlg();
	QList<int> l;

	QScrollArea *scrollArea = new QScrollArea(this);
	scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setWidgetResizable(true);
	//scrollArea->setBackgroundRole(QPalette::Dark);  // 背景色
													//scrollArea->setWidget(imageLabel);
	scrollArea->setWidget(pdlg);

	splitterMain->addWidget(scrollArea);
	l.push_back(100);
	l.push_back(100);
	splitterMain->setSizes(l);
	splitterMain->setStretchFactor(0, 1);                                      //Stretch Factor:拉伸系数
	splitterMain->setStretchFactor(1, 1);                                      //Stretch Factor:拉伸系数
	splitterMain->setWindowTitle(QObject::tr("Splitter"));

	
	//splitterMain->show();
	ph->addWidget(splitterMain);
	setLayout(ph);
}

DTestCurContrl::~DTestCurContrl()
{
}
#include <QPainter>
void DTestCurContrl::paintEvent(QPaintEvent *event)
{
 //   QFont font("Arial", 20, QFont::Bold, true);//设置字体的类型，大小，加粗，斜体

	//font.setUnderline(true);//设置下划线

	//font.setOverline(true);//设置上划线

	//font.setCapitalization(QFont::SmallCaps);//设置大小写

	//font.setLetterSpacing(QFont::AbsoluteSpacing, 5);//设置间距
	//QFont font;
	//QPainter painter(this);

	//QRect rect0 = rect();
	//rect0 = rect0.adjusted(10, 10, -10, -10);
	//QRectF ff(100, 100, 300, 200);

	//font.setPixelSize(rect0.height());
	//painter.setFont(font);//添加字体


	//painter.drawRect(rect0);

	//painter.setPen(QColor(Qt::red));

	//painter.drawText(rect0, Qt::AlignCenter, QStringLiteral("棒"));
}


DPatientInfoDlg::DPatientInfoDlg(QWidget *parent /*= Q_NULLPTR*/)
{
	this->setWindowFlags(Qt::FramelessWindowHint);


	QVBoxLayout* pLayOutV = new QVBoxLayout;
	this->setLayout(pLayOutV);


	{//患者信息
		sPatientInfoData data;
		data.m_qsTitel = QStringLiteral("患者信息");
		data.addData(QStringLiteral("患者姓名:"), QStringLiteral("AAAA"));
		data.addData(QStringLiteral("性别:"), QStringLiteral("男"));
		data.addData(QStringLiteral("年龄:"), QStringLiteral("30岁"));
		data.addData(QStringLiteral("联系方式:"), QStringLiteral("123456789"));

		DPatientInfoItem_PatientInfo * pPatientInfoItem_PatientInfo = new DPatientInfoItem_PatientInfo(data);
		pPatientInfoItem_PatientInfo->setDataByKey(QStringLiteral("患者姓名:"), QStringLiteral("BBBBB"));
		pLayOutV->addWidget(pPatientInfoItem_PatientInfo);
	}
	{//联系信息
		sPatientInfoData data;
		data.m_qsTitel = QStringLiteral("联系信息");
		data.addData(QStringLiteral("科室联系人:"), QStringLiteral("BBBB"));
		data.addData(QStringLiteral("联系人电话:"), QStringLiteral("123456789"));
		data.addData(QStringLiteral("科室:"), QStringLiteral("内科"));
		data.addData(QStringLiteral("病房:"), QStringLiteral("123"));
		data.addData(QStringLiteral("病床:"), QStringLiteral("456"));

		DPatientInfoItem_ContactInfo * pPatientInfoItem_ContactInfo = new DPatientInfoItem_ContactInfo(data);
		pLayOutV->addWidget(pPatientInfoItem_ContactInfo);
	}
	{//RR
		sPatientInfoData data;
		data.m_qsTitel = QStringLiteral("RR");
		data.addData(QStringLiteral("间期(ms):"), QStringLiteral("888"));

		DPatientInfoItem_RR * pPatientInfoItem_RR = new DPatientInfoItem_RR(data);
		pLayOutV->addWidget(pPatientInfoItem_RR);
	}
	{//ST
		sPatientInfoData data;
		data.m_qsTitel = QStringLiteral("S-T段");
		data.addData(QStringLiteral("aFV(mV):"), QStringLiteral("111"));
		data.addData(QStringLiteral("V1(mV):"), QStringLiteral("222"));
		data.addData(QStringLiteral("V5(mV):"), QStringLiteral("333"));
		DPatientInfoItem_ST * pPatientInfoItem_ST = new DPatientInfoItem_ST(data);
		pLayOutV->addWidget(pPatientInfoItem_ST);
	}
	{//ST_0
		sPatientInfoData data;
		data.m_qsTitel = QStringLiteral("S-T段");
		data.addData(QStringLiteral("V2:"), QStringLiteral("0"));
		data.addData(QStringLiteral("V6:"), QStringLiteral("1"));
		data.addData(QStringLiteral("I:"), QStringLiteral("2"));

		data.addData(QStringLiteral("V3:"), QStringLiteral("3"));
		data.addData(QStringLiteral("aVR:"), QStringLiteral("4"));
		data.addData(QStringLiteral("II:"), QStringLiteral("5"));

		data.addData(QStringLiteral("V4:"), QStringLiteral("6"));
		data.addData(QStringLiteral("aVL:"), QStringLiteral("7"));

		DPatientInfoItem_ST_0 * pPatientInfoItem_ST_0 = new DPatientInfoItem_ST_0(data);
		pLayOutV->addWidget(pPatientInfoItem_ST_0);
	}
	{//实时心率;
		sPatientInfoData data;
		data.m_qsTitel = QStringLiteral("实时心率");
		data.addData(QStringLiteral("心率(bpm):"), QStringLiteral("123"));
		data.addData(QStringLiteral("事件:"), QStringLiteral("心率过缓"));

		DPatientInfoItem_RealtimeHeartRate * pPatientInfoItem_RealtimeHeartRate = new DPatientInfoItem_RealtimeHeartRate(data);
		pLayOutV->addWidget(pPatientInfoItem_RealtimeHeartRate);
	}
	pLayOutV->addStretch();
}

DPatientInfoDlg::~DPatientInfoDlg()
{

}
void DPatientInfoDlg::paintEvent(QPaintEvent *event)
{
	QFont f;
	f.setPixelSize(100);
	QPainter painter(this);
	painter.setFont(f);
	// 设置画笔颜色
	painter.setPen(QColor(0, 160, 230));

	QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
	painter.drawText(QPoint(0,100), QStringLiteral("青春不老，奋斗不止！-纯正开源之美，有趣、好玩、靠谱。。。"));
}

void DPatientInfoDlg::resizeEvent(QResizeEvent *event)
{
	QSize s0 = size();
	int a = 10;
}

DPatientInfoItem::DPatientInfoItem(sPatientInfoData data, QWidget *parent /*= Q_NULLPTR*/):
	m_pLableTitel(NULL)
{
	this->setWindowFlags(Qt::FramelessWindowHint);
}

DPatientInfoItem::~DPatientInfoItem()
{

}


void DPatientInfoItem::setDataByKey(QString qsKey, QString qsValue)
{
	if (m_mapName2Lable.contains(qsKey))
	{
		m_mapName2Lable[qsKey]->setText(qsValue);
	}
}

void DPatientInfoItem::paintEvent(QPaintEvent *event)
{
    QPainter	painter(this);
	QPen pen;
	pen.setWidth(4);
	pen.setColor(Qt::gray);
	painter.setPen(pen);

	painter.drawRect(rect());

}

QHBoxLayout* DPatientInfoItem::createTitle()
{
	if (m_sPatientInfoData.m_qsTitel.isEmpty())
	{
		return NULL;
	}

	QHBoxLayout* pHLayout = new QHBoxLayout();

	QLabel* pLableLine0 = new QLabel;
	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(Qt::blue));
	pLableLine0->setPalette(palette);
	pLableLine0->setAutoFillBackground(true);

	//pLableLine0->setFixedSize(100, 1);
	pHLayout->addWidget(pLableLine0);


	QLabel* pLableLine1 = new QLabel(m_sPatientInfoData.m_qsTitel);
	pLableLine1->setAlignment(Qt::AlignCenter);
	pHLayout->addWidget(pLableLine1);

	m_pLableTitel = pLableLine1;

	QLabel* pLableLine2 = new QLabel;

	pLableLine2->setPalette(palette);
	pLableLine2->setAutoFillBackground(true);
	pHLayout->addWidget(pLableLine2);

	pLableLine0->setFixedHeight(1);
	pLableLine2->setFixedHeight(1);
	pHLayout->setStretchFactor(pLableLine0, 1);
	pHLayout->setStretchFactor(pLableLine1, 1);
	pHLayout->setStretchFactor(pLableLine2, 1000);

	return pHLayout;
}

void DPatientInfoItem::createUI()
{
	QVBoxLayout* pLayOutV = new QVBoxLayout;
	this->setLayout(pLayOutV);
	{
		QHBoxLayout* pHLayout = createTitle();
		if (pHLayout)
		{
			pLayOutV->addLayout(pHLayout);
		}


		QGridLayout *pGrid = new QGridLayout();

		for (size_t i = 0; i < m_sPatientInfoData.m_vecsLable2Data.size(); i++)
		{
			const sPatientInfoData::sLable2Data&  curData = m_sPatientInfoData.m_vecsLable2Data.at(i);

			QLabel* pLable_Key = new QLabel(curData.m_qsKey);
			pLable_Key->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			QLabel* pLable_Value = new QLabel(curData.m_qsValue);
			pLable_Value->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

			pGrid->addWidget(pLable_Key, i, 0);
			pGrid->addWidget(pLable_Value, i, 1);
			m_mapName2Lable.insert(curData.m_qsKey, pLable_Value);
		}
		pGrid->setColumnStretch(0, 1);
		pGrid->setColumnStretch(1, 1000);
		pLayOutV->addLayout(pGrid);
	}
}

DPatientInfoItem_PatientInfo::DPatientInfoItem_PatientInfo(sPatientInfoData data, QWidget *parent /*= Q_NULLPTR*/): DPatientInfoItem(data, parent)
{
	m_sPatientInfoData = data;
	createUI();
}

DPatientInfoItem_PatientInfo::~DPatientInfoItem_PatientInfo()
{

}


DPatientInfoItem_ContactInfo::DPatientInfoItem_ContactInfo(sPatientInfoData data, QWidget *parent /*= Q_NULLPTR*/) : DPatientInfoItem(data, parent)
{
	m_sPatientInfoData = data;
	createUI();
}

DPatientInfoItem_ContactInfo::~DPatientInfoItem_ContactInfo()
{

}

DPatientInfoItem_RR::DPatientInfoItem_RR(sPatientInfoData data, QWidget *parent /*= Q_NULLPTR*/) : DPatientInfoItem(data, parent)
{
	m_sPatientInfoData = data;
	createUI();
}

DPatientInfoItem_RR::~DPatientInfoItem_RR()
{

}

DPatientInfoItem_ST::DPatientInfoItem_ST(sPatientInfoData data, QWidget *parent /*= Q_NULLPTR*/) : DPatientInfoItem(data, parent)
{
	m_sPatientInfoData = data;
	createUI();
}

DPatientInfoItem_ST::~DPatientInfoItem_ST()
{

}

DPatientInfoItem_ST_0::DPatientInfoItem_ST_0(sPatientInfoData data, QWidget *parent /*= Q_NULLPTR*/) : DPatientInfoItem(data, parent)
{
	m_sPatientInfoData = data;
	createUI();
}

DPatientInfoItem_ST_0::~DPatientInfoItem_ST_0()
{

}

void DPatientInfoItem_ST_0::createUI()
{
	QVBoxLayout* pLayOutV = new QVBoxLayout;
	this->setLayout(pLayOutV);
	{
		QHBoxLayout* pHLayout = createTitle();
		if (pHLayout)
		{
			pLayOutV->addLayout(pHLayout);
		}


		QGridLayout *pGrid = new QGridLayout();

		for (size_t i = 0; i < m_sPatientInfoData.m_vecsLable2Data.size(); i++)
		{
			int nRow = i / 3;
			int nCol = i % 3;
			const sPatientInfoData::sLable2Data&  curData = m_sPatientInfoData.m_vecsLable2Data.at(i);

			QLabel* pLable_Key = new QLabel(curData.m_qsKey);
			pLable_Key->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			QLabel* pLable_Value = new QLabel(curData.m_qsValue);
			pLable_Value->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

			QHBoxLayout* pH = new QHBoxLayout;
			pH->addWidget(pLable_Key);
			pH->addWidget(pLable_Value);
			pH->addStretch();
			
			pGrid->addLayout(pH, nRow, nCol);

			m_mapName2Lable.insert(curData.m_qsKey, pLable_Value);
		}

		pLayOutV->addLayout(pGrid);
	}
}

DPatientInfoItem_RealtimeHeartRate::DPatientInfoItem_RealtimeHeartRate(sPatientInfoData data, QWidget *parent /*= Q_NULLPTR*/) : DPatientInfoItem(data, parent)
{
	m_sPatientInfoData = data;
	createUI();
}

DPatientInfoItem_RealtimeHeartRate::~DPatientInfoItem_RealtimeHeartRate()
{

}

void DPatientInfoItem_RealtimeHeartRate::createUI()
{
	DPatientInfoItem::createUI();

	if (m_mapName2Lable.contains(QStringLiteral("心率(bpm):")))
	{
		QFont f;
		f.setPixelSize(40);
		m_mapName2Lable[QStringLiteral("心率(bpm):")]->setFont(f);
	}
}
