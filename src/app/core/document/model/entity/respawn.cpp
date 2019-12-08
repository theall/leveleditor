#include "respawn.h"
#include "../../base/tr.h"

#include <QPointF>

static const QString P_START = T("Start Point");
static const QString P_RESPAWN = T("Respawn Point");

TRespawn::TRespawn(QObject *parent) :
    TObject(TObject::POINT, parent)
  , mStartPointObject(new TPointObject(parent))
  , mRespownPointObject(new TPointObject(parent))
{
    initPropertySheet();
}

void TRespawn::saveToStream(QDataStream &stream) const
{
    mStartPointObject->saveToStream(stream);
    mRespownPointObject->saveToStream(stream);
}

void TRespawn::readFromStream(QDataStream &stream)
{
    mStartPointObject->readFromStream(stream);
    mRespownPointObject->readFromStream(stream);
}

TPointObject *TRespawn::respownPointObject() const
{
    return mRespownPointObject;
}

TPointObject *TRespawn::startPointObject() const
{
    return mStartPointObject;
}

void TRespawn::initPropertySheet()
{
    TPropertyItem *propertyItem = mStartPointObject->posPropertyItem();
    propertyItem->setName(P_START);
    mPropertySheet->addProperty(propertyItem);

    propertyItem = mRespownPointObject->posPropertyItem();
    propertyItem->setName(P_RESPAWN);
    mPropertySheet->addProperty(propertyItem);
}

QString TRespawn::typeString() const
{
    return tr("Respawn");
}

bool TRespawn::isCongener(TObject *) const
{
    return false;
}
