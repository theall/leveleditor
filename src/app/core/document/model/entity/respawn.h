#ifndef TRESPAWN_H
#define TRESPAWN_H

#include <QList>

#include "object.h"
#include "../../base/io.h"

class TRespawn : public TObject, TIO
{
    Q_OBJECT

public:
    explicit TRespawn(QObject *parent = nullptr);

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    void initPropertySheet();
};

typedef QList<TRespawn*> TRespawnList;

#endif // TRESPAWN_H
