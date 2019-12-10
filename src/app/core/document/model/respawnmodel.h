#ifndef TRESPAWNSMODEL_H
#define TRESPAWNSMODEL_H

#include "basemodel.h"
#include "entity/respawn.h"
#include "objectgeneric.hpp"

#include <QList>
#include <QPoint>

#include "basemodel.h"

class TRespawnModel : public TBaseModel
{
    Q_OBJECT

public:
    TRespawnModel(QObject *parent = Q_NULLPTR);

    void clear();
    TRespawnList respawnList() const;

    // TIO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

private:
    TRespawnList mRespawnList;

public:
    DECL_GENERIC_FUNCTIONS(Respawn);

signals:
    DECL_GENERIC_SIGNALS(Respawn);
};

#endif // TRESPAWNSMODEL_H
