#include "selecteditems.h"

#include <QTimerEvent>
#include <QGraphicsScene>

TSelectedItems::TSelectedItems(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    mUpdateTimer = startTimer(100);
}

TSelectedItems::~TSelectedItems()
{

}

void TSelectedItems::setObjectItemList(const TObjectItemList &objectItemList)
{
    QGraphicsScene *graphicsScene = scene();
    if(!graphicsScene)
        throw tr("Null graphics scene set!");

    for(TSelectedItem *selectedItem : mObjectItemMap.values()) {
        delete selectedItem;
    }
    mObjectItemMap.clear();

    for(TObjectItem *objectItem : objectItemList) {
        TSelectedItem *selectedItem = new TSelectedItem(this);
        selectedItem->setObjectItem(objectItem);
        mObjectItemMap.insert(objectItem, selectedItem);
    }
    updateBoundingRect();
}

void TSelectedItems::setObjectItem(TObjectItem *objectItem)
{
    if(!objectItem)
        return;

    TObjectItemList objectItemList;
    objectItemList.append(objectItem);
    setObjectItemList(objectItemList);
}

int TSelectedItems::addObjectItem(TObjectItem *objectItem)
{
    if(!objectItem)
        return -1;

    TSelectedItem *selectedItem = new TSelectedItem(this);
    selectedItem->setObjectItem(objectItem);
    mObjectItemMap.insert(objectItem, selectedItem);
    updateBoundingRect();
    return 0;
}

int TSelectedItems::removeObjectItem(TObjectItem *objectItem)
{
    TSelectedItem *selectedItem = mObjectItemMap.value(objectItem);
    if(!selectedItem)
        return -1;

    mObjectItemMap.remove(objectItem);
    delete selectedItem;
    updateBoundingRect();
    return 0;
}

bool TSelectedItems::containsObjectItem(TObjectItem *objectItem) const
{
    return mObjectItemMap.contains(objectItem);
}

TObjectItemList TSelectedItems::getSelectedObjectItemList() const
{
    return mObjectItemMap.keys();
}

TObjectList TSelectedItems::getSelectedObjectList() const
{
    TObjectList objectList;
    for(TObjectItem *objectItem : mObjectItemMap.keys()) {
        objectList.append(objectItem->object());
    }
    return objectList;
}

void TSelectedItems::updateBoundingRect()
{
    mBoundingRect = QRectF();
    for(TSelectedItem *selectedItem : mObjectItemMap.values()) {
        mBoundingRect.united(selectedItem->boundingRect());
    }
}

QRectF TSelectedItems::boundingRect() const
{
    return mBoundingRect;
}

void TSelectedItems::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{

}

void TSelectedItems::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == mUpdateTimer) {
        // Update offset used in drawing black dashed line
        for(TSelectedItem *selectedItem : mObjectItemMap.values()) {
            selectedItem->step();
        }
        scene()->update(mBoundingRect);
    } else {
        QGraphicsObject::timerEvent(event);
    }
}
