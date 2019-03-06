#ifndef TRESPAWN_H
#define TRESPAWN_H

#include <QList>

#include "../../base/io.h"
#include "../../base/propertyobject.h"

class TRespawn : public TPropertyObject, TIO
{
    Q_OBJECT

public:
    TRespawn(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    void initPropertySheet();
};

typedef QList<TRespawn*> TRespawnList;

#endif // TRESPAWN_H
