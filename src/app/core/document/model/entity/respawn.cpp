#include "respawn.h"
#include "../../base/tr.h"

#include <QPointF>

static const QString P_START = T("Start Point");
static const QString P_RESPAWN = T("Respawn Point");

TRespawn::TRespawn(QObject *parent) :
    TPropertyObject(parent)
{
    initPropertySheet();
}

void TRespawn::saveToStream(QDataStream &stream) const
{
    stream << mPropertySheet->getValue(P_START).toPoint();
    stream << mPropertySheet->getValue(P_RESPAWN).toPoint();
}

void TRespawn::readFromStream(QDataStream &stream)
{
    QPoint start, respawn;
    stream >> start;
    stream >> respawn;
    mPropertySheet->setValue(P_START, start);
    mPropertySheet->setValue(P_RESPAWN, respawn);
}

void TRespawn::initPropertySheet()
{
    mPropertySheet->addProperty(PT_POINT, P_START, PID_SPAWN_START);
    mPropertySheet->addProperty(PT_POINT, P_RESPAWN, PID_SPAWN_RESPAWN);
}
