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
