#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QMenu>
#include <QGraphicsView>
#include <QContextMenuEvent>

class TGraphicsViewContextMenu;

class TGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit TGraphicsView(QWidget *parent = Q_NULLPTR);
    ~TGraphicsView();

    qreal scale() const;
    void setScale(const qreal &scale);
    void forceCenterOn(const QPointF &pos);

    TGraphicsViewContextMenu *graphicsViewContextMenu() const;

signals:
    void resized();
//    void requestPopupContextMenu(const QPointF &po);
    void pressDownPaste(const QPointF &pos);
    void requestPopupContextMenu();
    void onMouseMoved(const QPointF &pos);

private slots:
    void slotPressDownPaste();

private:
    qreal mScale;
    bool mLeftButtonDown;
    QPoint mLastMousePos;
    QPointF mCurrentMousePos;
    TGraphicsViewContextMenu *mGraphicsViewContextMenu;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // GRAPHICSVIEW_H
