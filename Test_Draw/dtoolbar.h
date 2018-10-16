#ifndef DTOOLBAR_H
#define DTOOLBAR_H

#include <QWidget>
class  QPushButton;
class  QLabel;
class DToolBar : public QWidget
{
    Q_OBJECT

public:
    DToolBar(QWidget *parent);
    ~DToolBar();

public:
    QPushButton* m_pBtn_Next;
    QPushButton* m_pBtn_Pre;
    QLabel* m_pLable_CurPage;

    QPushButton* m_pBtn_2X2;
    QPushButton* m_pBtn_2X3;
    QPushButton* m_pBtn_3X3;
    QPushButton* m_pBtn_7X7;

public slots:
	void slot_ChangeLable(int nCurPage, int nPageCount, int nMonFrameCounts);
};

#endif // DTOOLBAR_H
