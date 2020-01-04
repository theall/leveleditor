#include "wall.h"
#include "../../base/tr.h"

#include <QRect>

TWall::TWall(QObject *parent) :
    TRectObject(TObject::WALL, parent)
{
    initPropertySheet();
}

TWall::TWall(const QRect &rect, QObject *parent) :
    TRectObject(rect, TObject::DAREA, parent)
{
    initPropertySheet();
}

void TWall::saveToStream(QDataStream &stream) const
{
    QRect rect = getRect().toRect();
    stream << rect.left();
    stream << rect.top();
    stream << rect.width();
    stream << rect.height();
}

void TWall::readFromStream(QDataStream &stream)
{
    int x,y,w,h;
    stream >> x;
    stream >> y;
    stream >> w;
    stream >> h;
    setRect(x, y, w, h);
}

QByteArray TWall::toByteArray(TObject *object) const
{

}

void TWall::loadFromByteArray(const QByteArray &byteArray)
{

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
