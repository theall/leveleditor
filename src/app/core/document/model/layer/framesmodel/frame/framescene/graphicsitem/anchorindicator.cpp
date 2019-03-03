#include "anchorindicator.h"

static const QRectF g_boundingRect(QPointF(-9,-9), QPointF(9,9));
static const QLine g_drawingLines[] = {
    QLine(-4,0, 4,0),
    QLine(0,-4, 0,4),
};

TAnchorIndicator::TAnchorIndicator(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemSendsGeometryChanges
             | QGraphicsItem::ItemIgnoresParentOpacity);

    setZValue(10000 + 1);
    //setOpacity(0.5);
    setVisible(false);
}

TAnchorIndicator::~TAnchorIndicator()
{

}

QRectF TAnchorIndicator::boundingRect() const
{
    return g_boundingRect;
}

void TAnchorIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter->drawLines(g_drawingLines, sizeof(g_drawingLines) / sizeof(g_drawingLines[0]));
}

QVariant TAnchorIndicator::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change==QGraphicsItem::ItemPositionHasChanged)
    {
        emit itemMoved(value.toPointF());
    }
    return QGraphicsItem::itemChange(change, value);
}
