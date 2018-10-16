#ifndef DTOOLBARBATTERY_H
#define DTOOLBARBATTERY_H

#include <QWidget>

class DToolBarBattery : public QWidget
{
    Q_OBJECT

public:
    DToolBarBattery(QWidget *parent = 0);
    ~DToolBarBattery();

protected:
    void paintEvent(QPaintEvent *);
};

#endif // DTOOLBARBATTERY_H
