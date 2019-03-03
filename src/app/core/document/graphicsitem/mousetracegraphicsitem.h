#ifndef MOVEMODELGRAPHICSITEM_H
#define MOVEMODELGRAPHICSITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsRectItem>

class TMouseTraceGraphicsItem : public QGraphicsTextItem
{
public:
    TMouseTraceGraphicsItem(QGraphicsItem *parent = nullptr);
    ~TMouseTraceGraphicsItem();

    void setPos(const QPointF &pos, const QPointF &orginPos);

};

#endif // MOVEMODELGRAPHICSITEM_H
