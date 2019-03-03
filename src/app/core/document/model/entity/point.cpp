#include "point.h"

TPoint::TPoint() :
    QPoint()
{

}

void TPoint::readFromStream(QDataStream &stream)
{
    stream >> rx();
    stream >> ry();
}

void TPoint::saveToStream(QDataStream &stream) const
{
    stream << x();
    stream << y();
}
