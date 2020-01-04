#ifndef TOBJECT_H
#define TOBJECT_H

#include <QList>
#include <QSize>
#include <QRectF>
#include <QPointF>

#include "../../property/propertyobject.h"
#include "../../base/io.h"

class TDocument;

class TObject : public TPropertyObject, TIO
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

    virtual QByteArray toByteArray(TObject *object) const;
    virtual void loadFromByteArray(const QByteArray &byteArray);
    virtual void setPos(const QPointF &pos);

protected:
    virtual void initPropertySheet();

private:
    Type mType;
    bool mVisible;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const;
    void readFromStream(QDataStream &stream);
};
typedef QList<TObject*> TObjectList;

#endif // TOBJECT_H
