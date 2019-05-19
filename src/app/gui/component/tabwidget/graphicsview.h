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

private:
    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // GRAPHICSVIEW_H
