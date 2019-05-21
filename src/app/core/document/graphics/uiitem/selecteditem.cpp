#include "selecteditem.h"

#include <QPen>
#include <QPainter>
#include <utils/utils.h>

TSelectedItem::TSelectedItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mOffset(0)
  , mObjectItem(nullptr)
{

}

TSelectedItem::~TSelectedItem()
{

}

void TSelectedItem::setObjectItem(TObjectItem *objectItem)
{
    if(mObjectItem == objectItem)
        return;

    if(mObjectItem) {
        mObjectItem->disconnect(this);
    }

    mObjectItem = objectItem;

    if(mObjectItem) {
        setBoundingRect(mObjectItem->boundingRect());
        connect(mObjectItem,
                SIGNAL(boundingRectChanged()),
                this,
                SLOT(slotObjectBoundingRectChanged()));
        connect(mObjectItem,
                SIGNAL(destroyed(QObject*)),
                this,
                SLOT(slotOnObjectDestroyed(QObject*)));
        if(!isVisible())
            setVisible(true);
    } else {
        setBoundingRect();
        if(isVisible())
            setVisible(false);
    }
}

void TSelectedItem::step()
{
    mOffset--;
}

QRectF TSelectedItem::boundingRect() const
{
    return mBoundingRect;
}

void TSelectedItem::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *,
                          QWidget *)
{
    if(!mObjectItem)
        return;

    const QLineF lines[4] = {
        QLineF(mBoundingRect.topLeft(), mBoundingRect.topRight()),
        QLineF(mBoundingRect.topRight(), mBoundingRect.bottomRight()),
        QLineF(mBoundingRect.bottomRight(), mBoundingRect.bottomLeft()),
        QLineF(mBoundingRect.bottomLeft(), mBoundingRect.topLeft())
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

void TSelectedItem::slotObjectBoundingRectChanged()
{
    if(mObjectItem)
        setBoundingRect(mObjectItem->boundingRect());
}

void TSelectedItem::slotOnObjectDestroyed(QObject *)
{
    mObjectItem = nullptr;
    if(isVisible())
        setVisible(false);
    setBoundingRect();
}

void TSelectedItem::setBoundingRect(const QRectF &rect)
{
    prepareGeometryChange();
    mBoundingRect = rect;
}
