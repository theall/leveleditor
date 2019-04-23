#include "startpointitem.h"
#include "dooritem.h"
#include "../../../../model/entity/tile.h"

TStartPointItem::TStartPointItem(TDoorItem *doorItem) :
    TObjectItem(doorItem->startPoint(), doorItem)
  , mStartPoint(doorItem->startPoint())
{
    Q_ASSERT(mStartPoint);

    updateBoundingRect();
}

TStartPointItem::~TStartPointItem()
{

}

void TStartPointItem::updateBoundingRect()
{
    QPointF _pos = mStartPoint->getValue(PID_OBJECT_RECT).toRectF().topLeft();
    mBoundingRect.setSize(QSize(20,30));
    mBoundingRect.moveTop(_pos.y()-mBoundingRect.height());
    mBoundingRect.moveLeft(_pos.x()-mBoundingRect.width()/2);
}

void TStartPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    const qreal lineWidth = 1.0;
    const qreal shadowDist = lineWidth;
    const QPointF shadowOffset = QPointF(shadowDist * 0.5,
                                         shadowDist * 0.5);

    QPen linePen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    linePen.setCosmetic(true);
    QPen shadowPen(linePen);
    shadowPen.setColor(Qt::black);

    QColor brushColor = Qt::gray;
    brushColor.setAlpha(50);
    const QBrush fillBrush(brushColor);
    painter->setPen(Qt::NoPen);
    painter->setBrush(fillBrush);

    QPainterPath path;
    painter->translate(mBoundingRect.topLeft());
    const qreal radius = 10.0;
    const qreal sweep = 235.0;
    const qreal startAngle = 90.0 - sweep / 2;
    QRectF rectangle(0, 0, radius*2, radius*2);
    path.moveTo(radius+radius*cos(startAngle*M_PI/180.0), radius-radius*sin(startAngle*M_PI/180.0));
    path.arcTo(rectangle, startAngle, sweep);
    path.lineTo(radius, 3*radius);
    path.closeSubpath();

    painter->setPen(shadowPen);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path.translated(shadowOffset));
    painter->setPen(linePen);
    painter->setBrush(fillBrush);
    painter->drawPath(path);

    const QBrush opaqueBrush(Qt::gray);
    painter->setBrush(opaqueBrush);
    const qreal smallRadius = radius / 4.0;
    painter->drawEllipse(radius-smallRadius, radius-smallRadius, smallRadius * 2, smallRadius * 2);
}

void TStartPointItem::propertyValueChanged(PropertyID pid)
{
    if(pid == PID_OBJECT_RECT)
        updateBoundingRect();
}
