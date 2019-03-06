#include "wall.h"
#include "../../base/tr.h"

#include <QRect>

static const QString P_RECT = T("Area");

TWall::TWall(QObject *parent) :
    TPropertyObject(parent)
{
    initPropertySheet();
}

void TWall::saveToStream(QDataStream &stream) const
{

}

void TWall::readFromStream(QDataStream &stream)
{
    int x,y,w,h;
    stream >> x;
    stream >> y;
    stream >> w;
    stream >> h;
    mPropertySheet->setValue(P_RECT, QRect(x,y,w,h));
}

void TWall::initPropertySheet()
{
    mPropertySheet->addProperty(PT_RECT, P_RECT, PID_WALL_RECT);
}
