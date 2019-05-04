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
        POINT,
        DOOR,
        FRAME,
        ANIMATION,
        ENEMY,
        INVALID
    };

    TObject(Type type, QObject *parent = nullptr);

    Type type() const;
    virtual QString typeString() const = 0;

    virtual QPointF pos() const;
    virtual void setPos(const QPointF &pos);

    virtual QSize size() const;
    virtual void setSize(const QSize &size);

    virtual QRectF rect() const;
    virtual void setRect(const QRectF &rect);

    virtual void move(const QPointF &offset);

    virtual bool isCongener(TObject *object) const = 0;

    bool visible() const;
    void setVisible(bool visible);

protected:
    virtual void initPropertySheet();

private:
    Type mType;
    bool mVisible;
};

typedef QList<TObject*> TObjectList;
#endif // TOBJECT_H
