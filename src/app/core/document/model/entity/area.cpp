#include "area.h"
#include "../../base/tr.h"

#include <QRect>

static const QString P_FLEE_DIR = T("Flee Direction");
static const QString P_DANGER_AREA = T("Danger Area");
static const QString P_EDGES = T("Edges");
static const QString P_MOVE_BY = T("Move By");

TArea::TArea(QObject *parent) :
    TObject(TObject::AREA, parent)
{
    initPropertySheet();
}

TArea::TArea(const QRect &rect, QObject *parent) :
    TObject(TObject::AREA, parent)
{
    initPropertySheet();
    mPropertySheet->setValue(PID_OBJECT_RECT, QRectF(rect));
}

void TArea::saveToStream(QDataStream &stream) const
{
    QRect r = mPropertySheet->getValue(PID_OBJECT_RECT).toRect();
    stream << r.left();
    stream << r.top();
    stream << r.width();
    stream << r.height();
    stream << mPropertySheet->getValue(PID_AREA_FLEE_DIR).toInt();
    stream << mPropertySheet->getValue(PID_AREA_DANGER_AREA).toInt();
    stream << mPropertySheet->getValue(PID_AREA_EDGES).toInt();
    stream << mPropertySheet->getValue(PID_AREA_MOVE_BY).toInt();
}

void TArea::readFromStream(QDataStream &stream)
{
    int x,y,w,h,fleeDir,dangerArea,edges,moveBy;
    stream >> x;
    stream >> y;
    stream >> w;
    stream >> h;
    stream >> fleeDir;
    stream >> dangerArea;
    stream >> edges;
    stream >> moveBy;
    mPropertySheet->setValue(PID_OBJECT_RECT, QRectF(x,y,w,h));
    mPropertySheet->setValue(PID_AREA_FLEE_DIR, fleeDir);
    mPropertySheet->setValue(PID_AREA_DANGER_AREA, dangerArea);
    mPropertySheet->setValue(PID_AREA_EDGES, edges);
    mPropertySheet->setValue(PID_AREA_MOVE_BY, moveBy);
}

void TArea::initPropertySheet()
{
    mPropertySheet->addProperty(PT_INT, P_FLEE_DIR, PID_AREA_FLEE_DIR);
    mPropertySheet->addProperty(PT_INT, P_DANGER_AREA, PID_AREA_DANGER_AREA);
    mPropertySheet->addProperty(PT_INT, P_EDGES, PID_AREA_EDGES);
    mPropertySheet->addProperty(PT_INT, P_MOVE_BY, PID_AREA_MOVE_BY);
}

QString TArea::typeString() const
{
    return T("Area");
}

bool TArea::isCongener(TObject *object) const
{
    return static_cast<TArea*>(object);
}
