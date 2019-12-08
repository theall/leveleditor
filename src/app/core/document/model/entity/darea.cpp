#include "darea.h"
#include "../../base/tr.h"

#include <QRect>

static const QString P_FLEE_DIR = T("Flee Direction");
static const QString P_TYPE = T("Type");
static const QString P_TARGET = T("Target");
static const QString P_MOVE_BY = T("Move By");

TDArea::TDArea(QObject *parent) :
    TRectObject(TObject::DAREA, parent)
{
    initPropertySheet();
}

TDArea::TDArea(const QRect &rect, QObject *parent) :
    TRectObject(rect, TObject::DAREA, parent)
{
    initPropertySheet();
}

void TDArea::saveToStream(QDataStream &stream) const
{
    QRect r = getRect().toRect();
    stream << r.left();
    stream << r.top();
    stream << r.width();
    stream << r.height();
    stream << mPropertySheet->getValue(PID_DAREA_FLEE_DIR).toInt();
    stream << mPropertySheet->getValue(PID_DAREA_TYPE).toInt();
    stream << mPropertySheet->getValue(PID_DAREA_TARGET).toInt();
    stream << mPropertySheet->getValue(PID_DAREA_MOVE_BY).toInt();
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
    setRect(x, y, w, h);
    mPropertySheet->setValue(PID_DAREA_FLEE_DIR, fleeDir);
    mPropertySheet->setValue(PID_DAREA_TYPE, type);
    mPropertySheet->setValue(PID_DAREA_TARGET, target);
    mPropertySheet->setValue(PID_DAREA_MOVE_BY, moveBy);
}

void TDArea::initPropertySheet()
{
    mPropertySheet->addProperty(PT_INT, P_FLEE_DIR, PID_DAREA_FLEE_DIR);
    mPropertySheet->addProperty(PT_INT, P_TYPE, PID_DAREA_TYPE);
    mPropertySheet->addProperty(PT_INT, P_TARGET, PID_DAREA_TARGET);
    mPropertySheet->addProperty(PT_INT, P_MOVE_BY, PID_DAREA_MOVE_BY);
}

QString TDArea::typeString() const
{
    return T("Danger Area");
}

bool TDArea::isCongener(TObject *object) const
{
    return static_cast<TDArea*>(object);
}
