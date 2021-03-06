#include "selecteditems.h"

#include <QTimerEvent>
#include <QGraphicsScene>

TSelectedItems::TSelectedItems(QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mCurrentSelectedItem(nullptr)
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
    mObjectItemList.clear();
    mObjectItemMap.clear();
    mObjectMap.clear();

    for(TObjectItem *objectItem : objectItemList) {
        if(!objectItem)
            continue;

        TSelectedItem *selectedItem = new TSelectedItem(this);
        selectedItem->setObjectItem(objectItem);
        mObjectItemList.append(objectItem);
        mObjectItemMap.insert(objectItem, selectedItem);
        mObjectMap.insert(objectItem->object(), selectedItem);

        mCurrentSelectedItem = selectedItem;
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
    mObjectItemList.append(objectItem);
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
        mObjectItemList.append(objectItem);
        mObjectItemMap.insert(objectItem, selectedItem);
        mObjectMap.insert(objectItem->object(), selectedItem);
        itemsAdded++;
    }
    if(itemsAdded > 0)
        updateBoundingRect();

    return itemsAdded;
}

TObjectItem *TSelectedItems::removeObjectItem(TObjectItem *objectItem)
{
    TSelectedItem *selectedItem = mObjectItemMap.value(objectItem);
    if(!selectedItem)
        return nullptr;

    mObjectItemList.removeOne(objectItem);
    mObjectMap.remove(objectItem->object());
    mObjectItemMap.remove(objectItem);
    delete selectedItem;
    updateBoundingRect();

    if(mObjectItemList.isEmpty())
        return nullptr;
    return mObjectItemList.last();
}

bool TSelectedItems::containsObjectItem(TObjectItem *objectItem) const
{
    return mObjectItemMap.contains(objectItem);
}

TObjectItemList TSelectedItems::getSelectedObjectItemList() const
{
    return mObjectItemList;
}

TTileItemList TSelectedItems::getSelectedTileItemList() const
{
    TTileItemList tileItemList;
    for(TObjectItem *objectItem : mObjectItemMap.keys()) {
        tileItemList.append((TTileItem*)objectItem);
    }
    return tileItemList;
}

TObjectList TSelectedItems::getSelectedObjectList() const
{
    return mObjectMap.keys();
}

TRectObjectList TSelectedItems::getSelectedRectObjectList() const
{
    TRectObjectList objectList;
    for(TObject *object : mObjectMap.keys()) {
        objectList.append((TRectObject*)object);
    }
    return objectList;
}

void TSelectedItems::clear()
{
    setObjectItemList(TObjectItemList());
}

bool TSelectedItems::isEmpty() const
{
    return mObjectItemMap.isEmpty();
}

void TSelectedItems::move(const QPointF &offset)
{
    if(offset.isNull())
        return;

    for(TSelectedItem *selectedItem : mObjectItemMap.values()) {
        selectedItem->move(offset);
    }
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

bool TSelectedItems::startResizing()
{
    return false;
}

void TSelectedItems::endResizing()
{

}

TSelectedItem *TSelectedItems::currentSelectedItem() const
{
    return mCurrentSelectedItem;
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
