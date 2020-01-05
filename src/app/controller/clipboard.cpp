#include "clipboard.h"

IMPL_SINGLE_INSTANCE(TClipboard)
TClipboard::TClipboard(QObject *parent) :
    QObject(parent)
{

}

TClipboard::~TClipboard()
{
    
}

void TClipboard::setRectF(const QRectF &rectF)
{
    mRectF = rectF;
}

QList<QPointF> TClipboard::getPointFList() const
{
    QPointF pos = mRectF.center();
    QList<QPointF> pointFList;
    for(QPointF Pos : mPointFList)
        pointFList.append(Pos-pos);

    return pointFList;
}

void TClipboard::setPointFList(const QList<QPointF> &pointFList)
{
    mPointFList = pointFList;
}

TObject::Type TClipboard::getType() const
{
    return mType;
}

void TClipboard::setData(const TObject::Type &type, const TObjectList &objectList)
{
    mType = type;
    mDataList.clear();

    for(TObject *object : objectList) {
        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
        object->saveToStream(stream);
        mDataList.append(byteArray);
    }
}

bool TClipboard::whetherObject(const TObject::Type &type) const
{
    if(mType != type)
        return false;
    return true;
}

bool TClipboard::isEmpty()
{
    return mDataList.isEmpty();
}

TObjectList TClipboard::getObjectList() const
{
    TObjectList objectList;
    switch (mType) {
    case TObject::ANIMATION :
        for(QByteArray byteArray : mDataList)
        {
            TAnimation *animation = new TAnimation();
            QDataStream stream(&byteArray, QIODevice::ReadWrite);
            animation->readFromStream(stream);
            objectList.append(animation);
        }
        break;
    case TObject::AREA :
        for(QByteArray byteArray : mDataList)
        {
            TArea *area = new TArea();
            QDataStream stream(&byteArray, QIODevice::ReadWrite);
            area->readFromStream(stream);
            objectList.append(area);
        }
        break;
    case TObject::BOX :
        for(QByteArray byteArray : mDataList)
        {
            TBox *box = new TBox();
            QDataStream stream(&byteArray, QIODevice::ReadWrite);
            box->readFromStream(stream);
            objectList.append(box);
        }
        break;
    case TObject::DAREA :
        for(QByteArray byteArray : mDataList)
        {
            TDArea *darea = new TDArea();
            QDataStream stream(&byteArray, QIODevice::ReadWrite);
            darea->readFromStream(stream);
            objectList.append(darea);
        }
        break;
    case TObject::ENEMY :
        for(QByteArray byteArray : mDataList)
        {
            TEnemy *enemy = new TEnemy();
            QDataStream stream(&byteArray, QIODevice::ReadWrite);
            enemy->readFromStream(stream);
            objectList.append(enemy);
        }
        break;
    case TObject::FRAME :
        for(QByteArray byteArray : mDataList)
        {
            TFrame *frame = new TFrame();
            QDataStream stream(&byteArray, QIODevice::ReadWrite);
            frame->readFromStream(stream);
            objectList.append(frame);
        }
        break;
    case TObject::TRIGGER :
        for(QByteArray byteArray : mDataList)
        {
            TTrigger *trigger = new TTrigger();
            QDataStream stream(&byteArray, QIODevice::ReadWrite);
            trigger->readFromStream(stream);
            objectList.append(trigger);
        }
        break;
    case TObject::PLAT :
        for(QByteArray byteArray : mDataList)
        {
            TPlat *plat = new TPlat();
            QDataStream stream(&byteArray, QIODevice::ReadWrite);
            plat->readFromStream(stream);
            objectList.append(plat);
        }
        break;
    case TObject::TILE :
        for(QByteArray byteArray : mDataList)
        {
            TTile *tile = new TTile();
            QDataStream stream(&byteArray, QIODevice::ReadWrite);
            tile->readFromStream(stream);
            objectList.append(tile);
        }
        break;
     default :
        break;
    }
    return objectList;

}
