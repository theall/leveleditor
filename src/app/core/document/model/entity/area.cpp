#include "area.h"
#include <QRect>

static const char *P_RECT = "Area";
static const char *P_FLEE_DIR = "Flee Direction";
static const char *P_DANGER_AREA = "Danger Area";
static const char *P_EDGES = "Edges";
static const char *P_MOVE_BY = "Move By";

TArea::TArea(QObject *parent) :
    TPropertyObject(parent)
{
    initPropertySheet();
}

void TArea::saveToStream(QDataStream &stream) const
{

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
    mPropertySheet->setValue(P_RECT, QRect(x,y,w,h));
    mPropertySheet->setValue(P_FLEE_DIR, fleeDir);
    mPropertySheet->setValue(P_DANGER_AREA, dangerArea);
    mPropertySheet->setValue(P_EDGES, edges);
    mPropertySheet->setValue(P_MOVE_BY, moveBy);
}

void TArea::initPropertySheet()
{
    mPropertySheet->addProperty(PT_RECT, P_RECT, PID_AREA_RECT);
    mPropertySheet->addProperty(PT_INT, P_FLEE_DIR, PID_AREA_FLEE_DIR);
    mPropertySheet->addProperty(PT_INT, P_DANGER_AREA, PID_AREA_DANGER_AREA);
    mPropertySheet->addProperty(PT_INT, P_EDGES, PID_AREA_EDGES);
    mPropertySheet->addProperty(PT_INT, P_MOVE_BY, PID_AREA_MOVE_BY);
}
