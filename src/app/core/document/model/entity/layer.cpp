#include "layer.h"
#include "../../document.h"
#include "../../base/finddoc.h"
#include <utils/macro.h>

TLayer::TLayer(QObject *parent, const QString &name) :
    TPropertyObject(parent)
  , mType(Background)
  , mName(name)
  , mDocument(nullptr)
{
    FIND_DOCUMENT;

    setObjectName("Layer");   
}

TLayer::~TLayer()
{
    FREE_CONTAINER(mTileList);
}

QString TLayer::name() const
{
    return mName;
}

void TLayer::setName(const QString &name)
{
    mName = name;
}

void TLayer::saveToStream(QDataStream &stream) const
{
    foreach (TTile *tile, mTileList) {
        tile->saveToStream(stream);
    }
}

void TLayer::readFromStream(QDataStream &stream)
{
    int tileAmount = 0;
    FREE_CONTAINER(mTileList);
    stream >> tileAmount;
    for(int i=0;i<tileAmount;i++) {
        TTile *tile = new TTile(this);
        tile->readFromStream(stream);
        mTileList.append(tile);
    }

    // Process tile target
    for(TTile *tile : mTileList) {
        int tileTarget = tile->targetNumber();
        if(tileTarget>=0 && tileTarget<mTileList.size()) {
            tile->setTarget(mTileList.at(tileTarget));
        }
    }
}

TTileList TLayer::tileList() const
{
    return mTileList;
}

TLayer::Type TLayer::type() const
{
    return mType;
}

void TLayer::setType(const Type &type)
{
    mType = type;
}

int TLayer::tileSize() const
{
    return mTileList.size();
}

void TLayer::insertTile(TTile *tile, int index)
{
    if(!tile)
        return;

    TTileList tileList;
    QList<int> indexList;
    tileList.append(tile);
    indexList.append(index);
    insertTile(tileList, indexList);
}

void TLayer::insertTile(const TTileList &tileList, const QList<int> &indexList)
{
    TTileList tileInsertedList;
    QList<int> insertedIndexList;
    QList<int> indexListClone = indexList;
    int tileListSize = tileList.size();
    if(tileListSize != indexListClone.size()) {
        indexListClone.clear();
    }
    if(indexListClone.isEmpty()) {
        for(int i=0;i<tileListSize;i++) {
            indexListClone.append(-1);
        }
    }
    for(int i=0;i<tileListSize;i++) {
        TTile *tile = tileList.at(i);
        if(!tile)
            continue;

        int tileCount = mTileList.size();
        int index = indexListClone.at(i);
        if(index<0 || index>=tileCount) {
            index = tileCount;
            mTileList.append(tile);
        } else {
            mTileList.insert(index, tile);
        }
        tileInsertedList.append(tile);
        insertedIndexList.append(index);
    }
    emit tileInserted(tileInsertedList, insertedIndexList);
}

int TLayer::removeTile(int index)
{
    QList<int> indexList;
    indexList.append(index);

    QList<int> indexRemovedList = removeTile(indexList);
    index = -1;
    if(!indexRemovedList.isEmpty())
        index = indexRemovedList.at(0);
    return index;
}

int TLayer::removeTile(TTile *tile)
{
    TTileList tileList;
    tileList.append(tile);

    QList<int> indexRemovedList = removeTile(tileList);
    int index = -1;
    if(!indexRemovedList.isEmpty())
        index = indexRemovedList.at(0);
    return index;
}

QList<int> TLayer::removeTile(const QList<int> &indexList)
{
    TTileList tileList;
    QList<int> indexRemoved;
    for(int i=0;i<indexList.size();i++) {
        int index = indexList.at(i);
        TTile *tile = mTileList.at(index);
        mTileList.removeAt(index);
        tileList.append(tile);
        indexRemoved.append(index);
    }
    if(!indexRemoved.isEmpty())
        emit tileRemoved(tileList, indexRemoved);
    return indexRemoved;
}

QList<int> TLayer::removeTile(const TTileList &tileList)
{
    QList<int> indexRemoved;
    for(TTile *tile : tileList) {
        int index = mTileList.indexOf(tile);
        mTileList.removeAt(index);
        indexRemoved.append(index);
    }
    if(!indexRemoved.isEmpty())
        emit tileRemoved(tileList, indexRemoved);
    return indexRemoved;
}

TTile *TLayer::createTile(TTileId *tileId, const QPointF &pos)
{
    TTile *tile = new TTile(this);
    tile->setTileId(tileId);
    tile->setPos(pos);
    return tile;
}
