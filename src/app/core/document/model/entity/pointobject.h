#ifndef TPOINTOBJECT_H
#define TPOINTOBJECT_H

#include "object.h"
#include "../../base/io.h"

class TPointObject : public TObject, TIO
{
public:
    TPointObject(QObject *parent = Q_NULLPTR);
    TPointObject(TObject::Type type, QObject *parent = Q_NULLPTR);

    virtual QPointF pos() const;
    virtual void setPos(const QPointF &pos);

    virtual void move(const QPointF &offset);
    void setTypeString(const QString &typeString);

    TPropertyItem *posPropertyItem() const;

private:
    QString mTypeString;
    TPropertyItem *mPosPropertyItem;

    // TObject interface
public:
    QString typeString() const;
    bool isCongener(TObject *object) const;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const;
    void readFromStream(QDataStream &stream);
};

#endif // TPOINTOBJECT_H
