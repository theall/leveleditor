#ifndef TOBJECT_H
#define TOBJECT_H

#include <QList>
#include <QSize>
#include <QRectF>
#include <QPointF>

#include "../../property/propertyobject.h"

class TDocument;

class TObject : public TPropertyObject
{
    Q_OBJECT

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
        TRIGGER,
        INVALID
    };

    TObject(Type type, QObject *parent = nullptr);

    Type type() const;
    virtual QString typeString() const = 0;

    virtual void move(const QPointF &offset);

    virtual bool isCongener(TObject *object) const = 0;

    bool visible() const;
    void setVisible(bool visible);

protected:
    TDocument *mDocument;

private:
    Type mType;
    bool mVisible;

    void initPropertySheet();
};
typedef QList<TObject*> TObjectList;

#endif // TOBJECT_H
