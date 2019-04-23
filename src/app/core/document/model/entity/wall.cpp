#include "wall.h"
#include "../../base/tr.h"

#include <QRect>

TWall::TWall(QObject *parent) :
    TObject(TObject::WALL, parent)
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
    mPropertySheet->setValue(PID_OBJECT_RECT, QRectF(x,y,w,h));
}

void TWall::initPropertySheet()
{

}

QString TWall::typeString() const
{
    return T("Wall");
}

bool TWall::isCongener(TObject *object) const
{
    return static_cast<TWall*>(object);
}
