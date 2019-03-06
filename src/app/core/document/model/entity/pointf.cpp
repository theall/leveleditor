#include "pointf.h"

TPointF::TPointF() :
    QPointF()
{

}

void TPointF::readFromStream(QDataStream &stream)
{
    float x, y;
    stream >> x;
    stream >> y;
    setX(x);
    setY(y);
}

void TPointF::saveToStream(QDataStream &stream) const
{
    stream << (float)x();
    stream << (float)y();
}
