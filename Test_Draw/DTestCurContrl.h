#pragma once

#include <QWidget>
#include "ui_DTestCurContrl.h"
#include <QMap>
class QLabel;
class QHBoxLayout;
struct sPatientInfoData
{
	QString m_qsTitel;
	struct sLable2Data
	{
		QString m_qsKey;
		QString m_qsValue;
	};
	QVector<sLable2Data> m_vecsLable2Data;

	void addData(QString qsKey, QString qsValue)
	{
		sPatientInfoData::sLable2Data data;
		data.m_qsKey = qsKey;
		data.m_qsValue = qsValue;
		m_vecsLable2Data.push_back(data);
	}
};
class DPatientInfoItem: public QWidget
{
	Q_OBJECT

public:
	DPatientInfoItem(sPatientInfoData data, QWidget *parent = Q_NULLPTR);
	~DPatientInfoItem();
	void setDataByKey(QString qsKey, QString qsValue);

	void paintEvent(QPaintEvent *event);
protected:
	QHBoxLayout* createTitle();
	void createUI();
	sPatientInfoData m_sPatientInfoData;

	QLabel* m_pLableTitel;
	QMap<QString, QLabel*> m_mapName2Lable;

};

class DPatientInfoItem_PatientInfo : public DPatientInfoItem
{
	Q_OBJECT

public:
	DPatientInfoItem_PatientInfo(sPatientInfoData data, QWidget *parent = Q_NULLPTR);
	~DPatientInfoItem_PatientInfo();
};

class DPatientInfoItem_ContactInfo : public DPatientInfoItem
{
	Q_OBJECT

public:
	DPatientInfoItem_ContactInfo(sPatientInfoData data, QWidget *parent = Q_NULLPTR);
	~DPatientInfoItem_ContactInfo();
};

class DPatientInfoItem_RR : public DPatientInfoItem
{
	Q_OBJECT

public:
	DPatientInfoItem_RR(sPatientInfoData data, QWidget *parent = Q_NULLPTR);
	~DPatientInfoItem_RR();
};

class DPatientInfoItem_ST : public DPatientInfoItem
{
	Q_OBJECT

public:
	DPatientInfoItem_ST(sPatientInfoData data, QWidget *parent = Q_NULLPTR);
	~DPatientInfoItem_ST();
};

class DPatientInfoItem_ST_0 : public DPatientInfoItem
{
	Q_OBJECT

public:
	DPatientInfoItem_ST_0(sPatientInfoData data, QWidget *parent = Q_NULLPTR);
	~DPatientInfoItem_ST_0();
	void createUI();
};

class DPatientInfoItem_RealtimeHeartRate : public DPatientInfoItem
{
	Q_OBJECT

public:
	DPatientInfoItem_RealtimeHeartRate(sPatientInfoData data, QWidget *parent = Q_NULLPTR);
	~DPatientInfoItem_RealtimeHeartRate();
	void createUI();
};

class DPatientInfoDlg : public QWidget
{
	Q_OBJECT

public:
	DPatientInfoDlg(QWidget *parent = Q_NULLPTR);
	~DPatientInfoDlg();
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
private:

};


class DTestCurContrl : public QWidget
{
	Q_OBJECT

public:
	DTestCurContrl(QWidget *parent = Q_NULLPTR);
	~DTestCurContrl();

private:
	Ui::DTestCurContrl ui;
	void paintEvent(QPaintEvent *event);
};
