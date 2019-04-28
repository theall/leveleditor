#ifndef TENEMIESMODEL_H
#define TENEMIESMODEL_H

#include "../base/io.h"
#include "entity/enemy.h"

#include <QAbstractTableModel>

class TEnemiesModel : public QAbstractTableModel, TIO
{
    Q_OBJECT

public:
    explicit TEnemiesModel(QObject *parent = Q_NULLPTR);
    ~TEnemiesModel();

    void clear();

    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    TEnemyList enemyList() const;

    void setEnemyList(const TEnemyList &enemyList);

private:
    TEnemyList mEnemyList;
};
#endif // TENEMIESMODEL_H
