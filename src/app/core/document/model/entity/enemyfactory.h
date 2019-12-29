#ifndef TENEMYFACTORY_H
#define TENEMYFACTORY_H

#include <QList>

#include "object.h"
#include "enemy.h"
#include "../../base/io.h"

class TEnemyFactory : public TObject, TIO
{
    Q_OBJECT

public:
    explicit TEnemyFactory(QObject *parent = nullptr);
    ~TEnemyFactory();

    TEnemyList enemyList() const;
    TEnemy *getEnemy(int index) const;
    void setEnemyList(const TEnemyList &enemyList);

private:
    TEnemyList mEnemyList;
    void initPropertySheet();

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
};

typedef QList<TEnemyFactory*> TEnemyFactoryList;

#endif // TENEMYFACTORY_H
