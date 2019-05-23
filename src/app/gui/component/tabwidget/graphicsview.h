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

signals:
    void resized();
    void requestPopupContextMenu(const QPointF &po);

private:
    qreal mScale;
    bool mLeftButtonDown;

private:
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
