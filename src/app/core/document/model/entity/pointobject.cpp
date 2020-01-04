#include "pointobject.h"
#include "../../base/tr.h"

static const QString P_POS = T("Pos");

TPointObject::TPointObject(QObject *parent) :
    TObject(TObject::POINT, parent)
{
    mPosPropertyItem = mPropertySheet->addProperty(PT_POINTF, P_POS, PID_OBJECT_POS);
}

TPointObject::TPointObject(TObject::Type type, QObject *parent) :
    TObject(type, parent)
{
    mPosPropertyItem = mPropertySheet->addProperty(PT_POINTF, P_POS, PID_OBJECT_POS);
}

QString TPointObject::typeString() const
{
    if(mTypeString.isEmpty())
        return T("PointObject");
    return mTypeString;
}

QPointF TPointObject::pos() const
{
    return mPosPropertyItem->value().toPointF();
}

void TPointObject::setPos(const QPointF &pos)
{
    mPosPropertyItem->setValue(pos);
}

void TPointObject::move(const QPointF &offset)
{
    if(offset.isNull())
            return;

    QPointF currentPos = pos();
    currentPos += offset;
    mPosPropertyItem->setValue(currentPos);
}

void TPointObject::setTypeString(const QString &typeString)
{
    mTypeString = typeString;
}

TPropertyItem *TPointObject::posPropertyItem() const
{
    return mPosPropertyItem;
}

bool TPointObject::isCongener(TObject *object) const
{
    return static_cast<TPointObject*>(object);
}

void TPointObject::saveToStream(QDataStream &stream) const
{
    QPoint point = pos().toPoint();
    stream << point;
}

void TPointObject::readFromStream(QDataStream &stream)
{
    QPoint point;
    stream >> point;
    setPos(point);
}

QByteArray TPointObject::toByteArray(TObject *object) const
{

}

void TPointObject::loadFromByteArray(const QByteArray &byteArray)
{

}
