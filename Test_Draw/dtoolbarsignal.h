#ifndef DTOOLBARSIGNAL_H
#define DTOOLBARSIGNAL_H

#include <QWidget>


class DToolBarSignal : public QWidget
{
    Q_OBJECT

public:
    DToolBarSignal(QWidget *parent = 0);
    ~DToolBarSignal();
protected:
    void paintEvent(QPaintEvent *);

};

#endif // DTOOLBARSIGNAL_H
