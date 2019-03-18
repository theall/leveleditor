#include "darea.h"
#include "../../base/tr.h"

#include <QRect>

static const QString P_RECT = T("Area");
static const QString P_FLEE_DIR = T("Flee Direction");
static const QString P_TYPE = T("Type");
static const QString P_TARGET = T("Target");
static const QString P_MOVE_BY = T("Move By");

TDArea::TDArea(QObject *parent) :
    TObject(TObject::DAREA, parent)
{
    initPropertySheet();
}

void TDArea::saveToStream(QDataStream &stream) const
{

}

void TDArea::readFromStream(QDataStream &stream)
{
    int x,y,w,h,fleeDir,type,target,moveBy;
    stream >> x;
    stream >> y;
    stream >> w;
    stream >> h;
    stream >> fleeDir;
    stream >> type;
    stream >> target;
    stream >> moveBy;
    mPropertySheet->setValue(P_RECT, QRect(x,y,w,h));
    mPropertySheet->setValue(P_FLEE_DIR, fleeDir);
    mPropertySheet->setValue(P_TYPE, type);
    mPropertySheet->setValue(P_TARGET, target);
    mPropertySheet->setValue(P_MOVE_BY, moveBy);
}

void TDArea::initPropertySheet()
{
    mPropertySheet->addProperty(PT_RECT, P_RECT, PID_AREA_RECT);
    mPropertySheet->addProperty(PT_INT, P_FLEE_DIR, PID_AREA_FLEE_DIR);
    mPropertySheet->addProperty(PT_INT, P_TYPE, PID_AREA_DANGER_AREA);
    mPropertySheet->addProperty(PT_INT, P_TARGET, PID_AREA_EDGES);
    mPropertySheet->addProperty(PT_INT, P_MOVE_BY, PID_AREA_MOVE_BY);
}
