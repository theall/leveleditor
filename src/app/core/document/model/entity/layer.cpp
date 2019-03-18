#include "layer.h"
#include "../../document.h"
#include "../../base/findobj.h"
#include <utils/macro.h>

TLayer::TLayer(QObject *parent, const QString &name) :
    TPropertyObject(parent)
  , mName(name)
  , mDocument(nullptr)
{
    FIND_OBJECT;

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
}

TTileList TLayer::tileList() const
{
    return mTileList;
}
