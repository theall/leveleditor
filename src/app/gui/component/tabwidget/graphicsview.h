#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QMenu>
#include <QGraphicsView>
#include <QContextMenuEvent>

class TGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit TGraphicsView(QWidget *parent = Q_NULLPTR);
    ~TGraphicsView();

    qreal scale() const;
    void setScale(const qreal &scale);
    void forceCenterOn(const QPointF &pos);

signals:
    void resized();
    void requestPopupContextMenu(const QPointF &po);
    void onMouseMoved(const QPointF &pos);

private:
    qreal mScale;
    bool mLeftButtonDown;
    QPoint mLastMousePos;

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
