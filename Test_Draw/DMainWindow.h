#ifndef DMAINWINDOW_H
#define DMAINWINDOW_H

#include <QWidget>
#include "ui_DMainWindow.h"

class DMainWindow : public QWidget
{
    Q_OBJECT

public:
    DMainWindow(QWidget *parent = 0);
    ~DMainWindow();

private:
    Ui::DMainWindow ui;
};

#endif // DMAINWINDOW_H
