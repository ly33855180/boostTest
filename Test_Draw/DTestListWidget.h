#pragma once

#include <QWidget>
#include "ui_DTestListWidget.h"
#include <QListWidget>
class DTestListWidget : public QWidget
{
	Q_OBJECT

public:
	DTestListWidget(QWidget *parent = Q_NULLPTR);
	~DTestListWidget();

private:
	Ui::DTestListWidget ui;
	QListWidget *pwidget;
public slots:
void slotpadd();
void slotpclear();
void slotpdel();

};
