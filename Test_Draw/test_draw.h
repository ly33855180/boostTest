#ifndef TEST_DRAW_H
#define TEST_DRAW_H

#include <QtWidgets/QMainWindow>
#include "ui_test_draw.h"

class QAction;
class QMenu;
class DDrawWidget;
class Test_Draw : public QMainWindow
{
    Q_OBJECT

public:
    Test_Draw(QWidget *parent = 0);
    ~Test_Draw();

private:
    Ui::Test_DrawClass ui;

private:
    DDrawWidget *pwidget;
    QAction* m_openAction11;
    QAction* m_openAction22;
    QAction* m_openAction23;
    QAction* m_openAction33;
    QAction* m_openAction77;
    QAction* m_openAction99;
    QMenu* m_fileMenu;

    QAction* m_openAction_testtable;

public slots:
    void slotOpenFile11();
    void slotOpenFile22();
    void slotOpenFile23();
    void slotOpenFile33();
    void slotOpenFile77();
    void slotOpenFile99();
    void slot_testtable();
    void update();
};

#endif // TEST_DRAW_H
