#include "wall.h"
#include "../../base/tr.h"

#include <QRect>

TWall::TWall(QObject *parent) :
    TObject(TObject::WALL, parent)
{
    initPropertySheet();
}

TWall::TWall(const QRect &rect, QObject *parent) :
    TObject(TObject::DAREA, parent)
{
    initPropertySheet();
    setRect(rect);
}

void TWall::saveToStream(QDataStream &stream) const
{
    stream << mPropertySheet->getValue(PID_OBJECT_RECT).toRect();
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
