#include "selecteditem.h"

#include <QPen>
#include <QPainter>

#include <utils/utils.h>

#include "resizeitem.h"
#include "../layeritem/objectitem/objectitem.h"
#include "../layeritem/objectitem/rectobjectitem.h"

#define HANDLE_WIDTH 5
#define MARGIN ((HANDLE_WIDTH-1)/2)

TSelectedItem::TSelectedItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mOffset(0)
  , mObjectItem(nullptr)
  , mResizeItem(new TResizeItem(this))
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
                SIGNAL(boundingRectChanged(QRectF)),
                this,
                SLOT(slotObjectBoundingRectChanged(QRectF)));
        connect(mObjectItem,
                SIGNAL(destroyed(QObject*)),
                this,
                SLOT(slotOnObjectDestroyed(QObject*)));
        if(!isVisible())
            setVisible(true);

        mResizeItem->setVisible(qgraphicsitem_cast<TRectObjectItem*>(mObjectItem));
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

void TSelectedItem::move(const QPointF &offset)
{
    if(offset.isNull())
        return;

    if(mObjectItem) {
        mObjectItem->move(offset);
        setBoundingRect(mObjectItem->boundingRect());
    }
}

void TSelectedItem::slotObjectBoundingRectChanged(const QRectF &)
{
    if(!mObjectItem)
        return;

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
    mResizeItem->setRect(rect);
}
