#include "layer.h"
#include "../../document.h"
#include <utils/macro.h>

TLayer::TLayer(const QString &name=QString(), QObject *parent) :
    TPropertyObject(parent)
  , mName(name)
  , mDocument(nullptr)
{
    setObjectName("Layer");

    QObject *obj = parent;
    while (obj) {
        mDocument = qobject_cast<TDocument*>(obj);
        if(mDocument)
            break;
        obj = obj->parent();
    }
    if(!mDocument)
        throw QString("File:%1, Line:%2: Parent must be document.").arg(__FILE__).arg(__LINE__);
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

void TLayer::render(QPainter *painter, const QRectF &rect)
{
    foreach (TTile *tile, mTileList) {
        tile->render(painter, rect);
    }
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
