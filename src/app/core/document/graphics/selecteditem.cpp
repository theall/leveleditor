#include "selecteditem.h"

#include <QPen>
#include <QPainter>
#include <QTimerEvent>
#include <QGraphicsScene>
#include <utils/utils.h>

TSelectedItem::TSelectedItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    mUpdateTimer = startTimer(100);
}

void TSelectedItem::setObjectItem(TObjectItem *objectItem)
{
    if(mObjectItem) {
        mObjectItem->disconnect(this);
    }

    mObjectItem = objectItem;

    if(mObjectItem) {
        mBoundingRect = mObjectItem->boundingRect();
        if(!isVisible())
            setVisible(true);
    } else {
        mBoundingRect = QRectF();
        if(isVisible())
            setVisible(false);
    }
}

QRectF TSelectedItem::boundingRect() const
{
    return mBoundingRect;
}

void TSelectedItem::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *,
                          QWidget *)
{
    const QLineF lines[4] = {
        QLineF(mBoundingRect.topLeft(), mBoundingRect.topRight()),
        QLineF(mBoundingRect.bottomLeft(), mBoundingRect.bottomRight()),
        QLineF(mBoundingRect.topLeft(), mBoundingRect.bottomLeft()),
        QLineF(mBoundingRect.topRight(), mBoundingRect.bottomRight())
    };

    // Draw solid white lines
    QPen pen(Qt::white, 1.0, Qt::SolidLine);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawLines(lines, 4);

    const qreal devicePixelRatio = painter->device()->devicePixelRatioF();
    const qreal dashLength = std::ceil(Utils::dpiScaled(3) * devicePixelRatio);

    // Draw black dashed lines above the white line
    pen.setColor(Qt::black);
    pen.setCapStyle(Qt::FlatCap);
    pen.setDashPattern({dashLength, dashLength});
    pen.setDashOffset(mOffset);
    painter->setPen(pen);
    painter->drawLines(lines, 4);
}

void TSelectedItem::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == mUpdateTimer) {
        // Update offset used in drawing black dashed line
        mOffset--;
        scene()->update();
    } else {
        QGraphicsObject::timerEvent(event);
    }
}
