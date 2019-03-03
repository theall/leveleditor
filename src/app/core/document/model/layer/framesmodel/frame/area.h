#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QList>
#include <QGraphicsItem>

#include "shapeobject.h"

class TArea : public TShapeObject
{
    Q_OBJECT

public:
    enum Type
    {
        Collide,
        Attack,
        Undertake,
        Terrain,
        TypeCount
    };

    TArea(Type type, QObject *parent = nullptr);
    TArea(const QRectF &rect, Type type, QObject *parent = nullptr);
    TArea(qreal x, qreal y, qreal width, qreal height, Type type, QObject *parent = nullptr);

    Type type() const;
    void setType(const Type &type);

private slots:

private:
    Type mType;
    void initPropertySheet();
};
typedef QList<TArea*> TAreaList;

class TAreaManager : public QObject
{
    Q_OBJECT

public:
    TAreaManager(const TArea::Type &areaType, QObject *parent = nullptr);
    ~TAreaManager();

    QJsonArray toJson();
    QList<QRectF> toRectList() const;

    void add(qreal x, qreal y, qreal width, qreal height);
    void add(TArea *area);
    void add(const TAreaList &areaList);
    void remove(int index);
    void remove(TArea *area);
    TAreaList remove(const TAreaList &areaList);
    void move(const TAreaList &areaList, const QPointF &distance);

    bool isEmpty() const;
    void clear();

    void setRectList(const QList<QRectF> &rects);

    TAreaList areaList() const;

    TArea::Type areaType() const;
    QString areaTypeString() const;

signals:
    void areasAdded(const TAreaList &areaList);
    void areasRemoved(const TAreaList &areaList);
    void areasChanged();

private:
    TAreaList mAreaList;
    TArea::Type mAreaType;
};
typedef QList<TAreaManager*> TAreaManagers;

QDataStream &operator<<(QDataStream& out, const TAreaManager &areaManager);
QDataStream &operator>>(QDataStream& in, TAreaManager &areaManager);

#endif // AREA_H
