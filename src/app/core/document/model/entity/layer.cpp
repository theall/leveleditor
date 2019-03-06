#include "layer.h"
#include "../../document.h"

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

}

void TLayer::readFromStream(QDataStream &stream)
{
    int tileAmount = 0;
    stream >> tileAmount;
    mTileList.clear();

    for(int i=0;i<tileAmount;i++) {
        TTile *tile = new TTile(this);
        tile->readFromStream(stream);
        mTileList.append(tile);
    }
}
