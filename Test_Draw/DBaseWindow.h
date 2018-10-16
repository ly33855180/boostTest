#ifndef DBASEWINDOW_H
#define DBASEWINDOW_H

#include <QWidget>
class DTileBar;
class DStateBar;
class DDrawWidget;
class DToolBar;
class DBaseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DBaseWindow(QWidget *parent = 0);
    ~DBaseWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    QSize sizeHint() const;
private:
    //Ui::MainWindow *ui;

    //标题拖动、双击最大化
    bool mDrag;
    QPoint mDragPos;
    bool mIsMax;
    QRect mLocation;
    QFont mIconFont;

    //与缩放相关的变量
    int mZoom;
    QRect mZoomLocation;
    QPoint mZoomPos;
    
private:
    DTileBar* m_pTileBar;
    DStateBar* m_pStateBar;
    DToolBar* m_pToolBar;
    DDrawWidget* m_pDrawWidget;
};

#endif // DBASEWINDOW_H
