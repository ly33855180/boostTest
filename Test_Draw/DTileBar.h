#ifndef DTILEBAR_H
#define DTILEBAR_H

#include <QWidget>
class QLabel;
class QPushButton;

class DTileBar : public QWidget
{
    Q_OBJECT

public:
	enum ETileBarEvent
	{
		Event_MinBtnClick = 0, 
		Event_MaxBtnClick,
		Event_CloseBtnClick,
	};
    DTileBar(QWidget *parent);
    ~DTileBar();

protected:

    void paintEvent(QPaintEvent *);
    // ˫�����������н�������/��ԭ
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

private slots:

    // ������С�������/��ԭ���رղ���
    void onClicked();

private:
    QLabel *m_pIconLabel;
    QLabel *m_pTitleLabel;
    QPushButton *m_pMinimizeButton;
    QPushButton *m_pMaximizeButton;
    QPushButton *m_pCloseButton;
};

#endif // DTILEBAR_H
