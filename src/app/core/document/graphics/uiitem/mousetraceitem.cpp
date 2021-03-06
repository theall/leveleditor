#include "mousetraceitem.h"

#include <QWidget>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

TMouseTraceItem::TMouseTraceItem(QGraphicsItem *parent) :
    QGraphicsTextItem(parent)
{
    setDefaultTextColor(QColor(0,0,250));
}

TMouseTraceItem::~TMouseTraceItem()
{

}

void TMouseTraceItem::setPos(const QPointF &pos, const QPointF &orginPos)
{
    qreal posX = pos.x();
    qreal posY = pos.y();
    setPlainText(QString("%1 %2").arg(posX-orginPos.x()).arg(orginPos.y()-posY));

    QPointF newPos = pos;
    newPos.setX(posX-boundingRect().width()/2);
    newPos.setY(posY-boundingRect().height()-2);
    QGraphicsTextItem::setPos(newPos);
}
