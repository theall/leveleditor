#ifndef MOVEMODELGRAPHICSITEM_H
#define MOVEMODELGRAPHICSITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsRectItem>

class TMouseTraceItem : public QGraphicsTextItem
{
public:
    TMouseTraceItem(QGraphicsItem *parent = nullptr);
    ~TMouseTraceItem();

    void setPos(const QPointF &pos, const QPointF &orginPos);

};

#endif // MOVEMODELGRAPHICSITEM_H
