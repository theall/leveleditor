#include "playeritem.h"

#include <QPen>
#include <QPainter>

#define DIAMETER 10
#define TRUNK_WIDTH 4
#define LIMB_WIDTH 2
#define HEIGHT (DIAMETER*2.5)
#define WIDTH (DIAMETER*1.5)

TPlayerItem::TPlayerItem(TPointObject *pointObject, QGraphicsItem *parent) :
    TPointObjectItem(pointObject, parent)
  , mColor(Qt::blue)
{
    Q_ASSERT(pointObject);

    QRectF r = QRectF(-WIDTH/2, -HEIGHT, WIDTH, HEIGHT);
    r.translate(pointObject->pos());
    setBoundingRect(r);
}

TPlayerItem::~TPlayerItem()
{

}

QColor TPlayerItem::getColor() const
{
    return mColor;
}

void TPlayerItem::setColor(const QColor &color)
{
    mColor = color;
}

void TPlayerItem::propertyValueChanged(PropertyID)
{

}

void TPlayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal headInitialX = mBoundingRect.left() + (mBoundingRect.width() - DIAMETER -(WIDTH - DIAMETER) / 2);
    qreal headInitialY = mBoundingRect.top() + 1;

    const qreal trunkInitialX = headInitialX + WIDTH/2 - TRUNK_WIDTH/2 - 0.5;
    const qreal trunkInitialY = mBoundingRect.top() - TRUNK_WIDTH/4 + DIAMETER;
    const QPointF trunkInitialPos = QPointF(trunkInitialX, trunkInitialY);

    const qreal trunkEndX = trunkInitialX;
    const qreal trunkEndY = trunkInitialY + DIAMETER;
    const QPointF trunkEndPos = QPointF(trunkEndX , trunkEndY);

    const qreal handInitialX = trunkInitialX;
    const qreal handInitialY = trunkInitialY + (trunkEndY - trunkInitialY - LIMB_WIDTH)/2;
    const QPointF handInitialPos = QPointF(handInitialX, handInitialY);

    const qreal leftHandEndX = handInitialX - DIAMETER/2 - TRUNK_WIDTH / 2 + 0.5 ;
    const qreal leftHandEndY = handInitialY + DIAMETER/2;
    const QPointF leftHandEndPos = QPointF(leftHandEndX, leftHandEndY);

    const qreal rightHandEndX = handInitialX + DIAMETER/2 + TRUNK_WIDTH/4 + 0.5;
    const qreal rightHandEndY = leftHandEndY;
    const QPointF rightHandEndPos = QPointF(rightHandEndX, rightHandEndY);

    const qreal legInitialX = trunkEndX;
    const qreal legInitialY = trunkEndY;
    const QPointF legInitialPos = QPointF(legInitialX, legInitialY);

    const qreal rightLegEndX = legInitialX - DIAMETER/2;
    const qreal rightLegEndY = legInitialY + DIAMETER/2;
    QPointF rightLegEndPos = QPointF(rightLegEndX, rightLegEndY);

    const qreal leftLegEndX = legInitialX + DIAMETER/2;
    const qreal leftLegEndY = rightLegEndY;
    QPointF leftLegEndPos = QPointF(leftLegEndX, leftLegEndY);

    const QBrush fillBrush(mColor);
    QPen ellipsePen(mColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(ellipsePen);
    painter->setBrush(fillBrush);
    painter->drawEllipse(headInitialX, headInitialY, DIAMETER, DIAMETER);

    QPen linePen(mColor, TRUNK_WIDTH, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(linePen);
    painter->drawLine(trunkInitialPos, trunkEndPos);

    QPen linePen1(mColor, LIMB_WIDTH, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(linePen1);
    painter->drawLine(handInitialPos, rightHandEndPos);
    painter->drawLine(handInitialPos, leftHandEndPos);

    painter->drawLine(legInitialPos, rightLegEndPos);
    painter->drawLine(legInitialPos, leftLegEndPos);
}
