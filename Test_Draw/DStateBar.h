#ifndef DSTATEBAR_H
#define DSTATEBAR_H

#include <QWidget>
class QLabel;
class DStateBar : public QWidget
{
    Q_OBJECT

public:
    DStateBar(QWidget *parent);
    ~DStateBar();

    inline QLabel* GetDragLable()const
    {
        return m_pDragLabel;
    }

private:
    QLabel* m_pDragLabel;

protected:

    void paintEvent(QPaintEvent *);
};

#endif // DSTATEBAR_H
