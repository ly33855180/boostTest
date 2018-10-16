#ifndef DTOOLBARBTN_H
#define DTOOLBARBTN_H

#include <QPushButton>

class DToolBarBtn : public QPushButton
{
    Q_OBJECT

public:
    DToolBarBtn(QWidget *parent = 0);
    ~DToolBarBtn();

private:
protected:
    void paintEvent(QPaintEvent *);

};

#endif // DTOOLBARBTN_H
