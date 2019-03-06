#include "rect.h"

void TRect::readFromStream(QDataStream &stream)
{
    int x,y,w,h;
    stream >> x;
    stream >> y;
    stream >> w;
    stream >> h;
    setRect(x, y, w, h);
}

void TRect::saveToStream(QDataStream &stream) const
{
    stream << x();
    stream << y();
    stream << width();
    stream << height();
}
