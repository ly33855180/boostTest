#ifndef QITEMTOOLBARDLG_H
#define QITEMTOOLBARDLG_H

#include <QWidget>
#include "ui_qitemtoolbardlg.h"

class DToolBarBtn;
class DToolBarLable;
class DToolBarSignal;
class DToolBarBattery;
class QLabel;

class QItemToolBarDlg : public QWidget
{
    Q_OBJECT

public:
    QItemToolBarDlg(QWidget *parent = 0);
    ~QItemToolBarDlg();
    void setInfo();
	void setLable(QString qsLable);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);

private:
    Ui::QItemToolBarDlg ui;

    DToolBarBtn* m_pBtn;
    DToolBarLable* m_pLable_PatientInfo;
    DToolBarLable* m_pLable_DrawInfo;
    DToolBarBattery* m_pLable_Battery;
    DToolBarSignal* m_pLable_Signal;

private slots:
    void slotBtnClicked(bool);
};

#endif // QITEMTOOLBARDLG_H
