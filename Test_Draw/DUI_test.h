#pragma once

#include <QWidget>
#include "ui_DUI_test.h"

class DUI_test : public QWidget
{
	Q_OBJECT

public:
	DUI_test(QWidget *parent = Q_NULLPTR);
	~DUI_test();

private:
	Ui::DUI_test ui;
};
