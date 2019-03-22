#ifndef TOBJECT_H
#define TOBJECT_H

#include <QList>
#include <QSize>
#include <QRectF>
#include <QPointF>

#include "../../property/propertyobject.h"

class TObject : public TPropertyObject
{
public:
    enum Type {
        AREA,
        DAREA,
        BOX,
        PLAT,
        TILE,
        WALL,
        INVALID
    };

    TObject(Type type, QObject *parent = nullptr);

    Type type() const;
    virtual QString typeString() const = 0;

    QPointF pos() const;
    void setPos(const QPointF &pos);

    QSize size() const;
    void setSize(const QSize &size);

    QRectF rect() const;

    void move(const QPointF &offset);

    virtual bool isCongener(TObject *object) const = 0;

protected:
    virtual void initPropertySheet();

private:
    Type mType;
};

typedef QList<TObject*> TObjectList;
#endif // TOBJECT_H
