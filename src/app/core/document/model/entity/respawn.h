#ifndef TRESPAWN_H
#define TRESPAWN_H

#include <QList>

#include "pointobject.h"
#include "../../base/io.h"

class TRespawn : public TObject, TIO
{
    Q_OBJECT

public:
    explicit TRespawn(QObject *parent = nullptr);

    TPointObject *startPointObject() const;
    TPointObject *respownPointObject() const;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    TPointObject *mStartPointObject;
    TPointObject *mRespownPointObject;

    void initPropertySheet();

    // TObject interface
public:
    QString typeString() const;
    bool isCongener(TObject *object) const;

};

typedef QList<TRespawn*> TRespawnList;

#endif // TRESPAWN_H
