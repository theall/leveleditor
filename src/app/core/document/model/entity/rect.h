#ifndef TRECT_H
#define TRECT_H

#include "../../base/io.h"

#include <QList>
#include <QRect>
#include <QDataStream>

class TRect : public QRect, TIO
{
    // TIO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

private:
};

typedef QList<TRect*> TRectList;

#endif // TRECT_H
