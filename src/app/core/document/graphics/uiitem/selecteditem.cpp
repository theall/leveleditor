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
    connect(mResizeItem, SIGNAL(requestAdjustRect(QMarginsF)), this, SLOT(slotRequestAdjustRect(QMarginsF)));
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
        bool isRectItem = dynamic_cast<TRectObjectItem*>(mObjectItem)!=nullptr;
        mResizeItem->setVisible(isRectItem);
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

bool TSelectedItem::startResizing()
{
    return mResizeItem->startResizing();
}

void TSelectedItem::endResizing()
{
    mResizeItem->endResizing();
}

QMarginsF TSelectedItem::getMarginsF() const
{
    QRectF objectRect = mObjectItem->boundingRect();
    return QMarginsF(objectRect.left()-mBoundingRect.left(),
                     objectRect.top()-mBoundingRect.top(),
                     mBoundingRect.right()-objectRect.right(),
                     mBoundingRect.bottom()-objectRect.bottom());
}

void TSelectedItem::slotRequestAdjustRect(const QMarginsF &margins)
{
    if(!mObjectItem)
        return;

    setBoundingRect(mBoundingRect + margins);
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
    mBoundingRect = rect;
    mResizeItem->setRect(rect);
}
