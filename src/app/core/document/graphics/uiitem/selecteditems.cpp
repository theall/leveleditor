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
    mObjectMap.clear();

    for(TObjectItem *objectItem : objectItemList) {
        if(!objectItem)
            continue;

        TSelectedItem *selectedItem = new TSelectedItem(this);
        selectedItem->setObjectItem(objectItem);
        mObjectItemMap.insert(objectItem, selectedItem);
        mObjectMap.insert(objectItem->object(), selectedItem);
    }
    updateBoundingRect();
}

void TSelectedItems::setObjectItem(TObjectItem *objectItem)
{
    TObjectItemList objectItemList;
    objectItemList.append(objectItem);
    setObjectItemList(objectItemList);
}

int TSelectedItems::addObjectItem(TObjectItem *objectItem)
{
    if(!objectItem || mObjectItemMap.contains(objectItem))
        return -1;

    TSelectedItem *selectedItem = new TSelectedItem(this);
    selectedItem->setObjectItem(objectItem);
    mObjectItemMap.insert(objectItem, selectedItem);
    mObjectMap.insert(objectItem->object(), selectedItem);
    updateBoundingRect();
    return 0;
}

int TSelectedItems::addObjectItems(const TObjectItemList &objectItemList)
{
    int itemsAdded = 0;
    for(TObjectItem *objectItem : objectItemList) {
        if(!objectItem || mObjectItemMap.contains(objectItem))
            continue;

        TSelectedItem *selectedItem = new TSelectedItem(this);
        selectedItem->setObjectItem(objectItem);
        mObjectItemMap.insert(objectItem, selectedItem);
        mObjectMap.insert(objectItem->object(), selectedItem);
        itemsAdded++;
    }
    if(itemsAdded > 0)
        updateBoundingRect();

    return itemsAdded;
}

int TSelectedItems::removeObjectItem(TObjectItem *objectItem)
{
    TSelectedItem *selectedItem = mObjectItemMap.value(objectItem);
    if(!selectedItem)
        return -1;

    mObjectMap.remove(objectItem->object());
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
    return mObjectMap.keys();
}

void TSelectedItems::clear()
{
    setObjectItemList(TObjectItemList());
}

bool TSelectedItems::isEmpty() const
{
    return mObjectItemMap.isEmpty();
}

TObject::Type TSelectedItems::getObjectType() const
{
    TObjectItemList objectItemList = mObjectItemMap.keys();
    if(objectItemList.size() < 1)
        return TObject::INVALID;

    TObject::Type t = objectItemList.at(0)->objectType();
    for(TObjectItem *objectItem : objectItemList) {
        if(objectItem->objectType() != t)
            return TObject::INVALID;
    }
    return t;
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
