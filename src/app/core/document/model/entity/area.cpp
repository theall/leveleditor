#include "area.h"
#include "../../base/tr.h"

#include <QRect>

static const QString P_FLEE_DIR = T("Flee Direction");
static const QString P_DANGER_AREA = T("Danger Area");
static const QString P_EDGES = T("Edges");
static const QString P_MOVE_BY = T("Move By Plat");

int fleeDirToEnumIndex(int value)
{
    int index = 0;
    if(value == 2)
        index = 1;
    else if(value == 4)
        index = 2;
    return index;
}

int enumIndexToFleeDirValue(int index)
{
    int value = 0;
    if(index == 1)
        value = 2;
    else if(index == 2)
        value = 4;
    return value;
}

TArea::TArea(QObject *parent) :
    TRectObject(TObject::AREA, parent)
{
    initPropertySheet();
}

TArea::TArea(const QRect &rect, QObject *parent) :
    TRectObject(rect, TObject::AREA, parent)
{
    initPropertySheet();
}

void TArea::setPlatNameList(const QStringList &platNames)
{
    mPropertySheet->get(PID_AREA_MOVE_BY)->setAttribute(PA_ENUM_NAMES, platNames);
}

void TArea::saveToStream(QDataStream &stream) const
{
    QRect r = getRect().toRect();
    stream << r.left();
    stream << r.top();
    stream << r.width();
    stream << r.height();
    stream << enumIndexToFleeDirValue(mPropertySheet->getValue(PID_AREA_FLEE_DIR).toInt());
    stream << (int)mPropertySheet->getValue(PID_AREA_DANGER_AREA).toBool();
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
    setRect(x, y, w, h);
    mPropertySheet->setValue(PID_AREA_FLEE_DIR, fleeDirToEnumIndex(fleeDir));
    mPropertySheet->setValue(PID_AREA_DANGER_AREA, (bool)dangerArea);
    mPropertySheet->setValue(PID_AREA_EDGES, edges);
    mPropertySheet->setValue(PID_AREA_MOVE_BY, moveBy);
}

void TArea::initPropertySheet()
{
    mPropertySheet->addProperty(PT_ENUM, P_FLEE_DIR, PID_AREA_FLEE_DIR)->addDirectionAttribute();
    mPropertySheet->addProperty(PT_BOOL, P_DANGER_AREA, PID_AREA_DANGER_AREA);
    mPropertySheet->addProperty(PT_INT, P_EDGES, PID_AREA_EDGES);
    mPropertySheet->addProperty(PA_ENUM_NAMES, P_MOVE_BY, PID_AREA_MOVE_BY);
}

QString TArea::typeString() const
{
    return T("Area");
}

bool TArea::isCongener(TObject *object) const
{
    return static_cast<TArea*>(object);
}
