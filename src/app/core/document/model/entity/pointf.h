#ifndef TPOINTF_H
#define TPOINTF_H

#include "../../base/io.h"

#include <QList>
#include <QPointF>
#include <QDataStream>

class TPointF : public QPointF, TIO
{
public:
    TPointF();

    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

private:
};

typedef QList<TPointF*> TPointFList;

#endif // TPOINTF_H
