#ifndef TPOINT_H
#define TPOINT_H

#include "../../base/io.h"

#include <QPoint>
#include <QDataStream>

class TPoint : public QPoint, TIO
{
public:
    TPoint();

    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

private:
};

#endif // TPOINT_H
