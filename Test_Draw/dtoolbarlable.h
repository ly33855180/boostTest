#ifndef DTOOLBARLABLE_H
#define DTOOLBARLABLE_H

#include <QWidget>


class DToolBarLable : public QWidget
{
    Q_OBJECT

public:
    DToolBarLable(QWidget *parent = 0);
    ~DToolBarLable();
    int m_nWide;
    void setLable(QString qsText, int nHeight);
protected:
    void paintEvent(QPaintEvent *);
private:
    QString m_qsText;

};

#endif // DTOOLBARLABLE_H
