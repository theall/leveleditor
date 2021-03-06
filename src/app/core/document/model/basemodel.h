#ifndef TBASEMODEL_H
#define TBASEMODEL_H

#include <QList>
#include <QIcon>
#include <QModelIndex>
#include <QAbstractItemModel>

#include "../base/io.h"
#include "entity/object.h"

class TBaseModel : public QAbstractItemModel, TIO
{
    Q_OBJECT

public:
    enum Type {
        TILE,
        AREA,
        DAREA,
        PLAT,
        WALL,
        BOX,
        EVENT,
        ENEMY_FACTORY,
        TRIGGER,
        RESPAWN,
        ANIMATION,
        FRAME,
        SCENE,
        INVALID = -1,
    };
    explicit TBaseModel(Type type, QObject *parent = Q_NULLPTR);
    virtual ~TBaseModel();

    QString name() const;
    void setName(const QString &name);

    bool visible() const;
    void setVisibility(bool visible);

    QIcon icon() const;
    void setIcon(const QIcon &icon);

    bool locked() const;
    void setLocked(bool locked);

    Type type() const;

    bool currentObjectWhetherCurrentModel(TObject::Type type);

    bool isTile() const;

    float transparency() const;
    void setTransparency(float transparency);

    virtual void insertObjects(const TObjectList &objectList, const QList<int> &indexList);
    virtual QList<int> removeObjects(const TObjectList &objectList);
    virtual QList<int> moveObjects(const TObjectList &objectList, const QList<int> &indexList);

protected:
    virtual void onObjectInserted(const TObjectList &objectList, const QList<int> &indexList);
    virtual void onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList);
    virtual void onObjectMove(const TObjectList &objectList, const QList<int> &posList);

signals:
    void visibilityChanged(bool visible);
    void lockChanged(bool locked);

private:
    QIcon mIcon;
    QString mName;
    bool mVisible;
    bool mLocked;
    Type mType;
    float mTransparency;

    // QAbstractItemModel interface
public:
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const;
    void readFromStream(QDataStream &stream);
};
typedef QList<TBaseModel*> TBaseModelList;
#endif // TBASEMODEL_H
