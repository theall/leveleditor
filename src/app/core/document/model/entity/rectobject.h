#ifndef TRECTOBJECT_H
#define TRECTOBJECT_H

#include <QList>

#include "object.h"
#include "../../base/io.h"

class TRectObject : public TObject, TIO
{
public:
    TRectObject(TObject::Type type, QObject *parent = Q_NULLPTR);
    TRectObject(const QRect &rect, TObject::Type type, QObject *parent = Q_NULLPTR);
    ~TRectObject();

    QSize size() const;
    void setSize(const QSize &size);

    QRectF getRect() const;
    void setRect(const QRectF &rect);
    void setRect(int x, int y, int w, int h);

    QPointF getPos() const;
    void setPos(const QPointF &pos);

    void adjust(const QMarginsF &marings);
    virtual void move(const QPointF &offset) Q_DECL_OVERRIDE;

private:
    TPropertyItem *mRectPropertyItem;

    void initPropertySheet();
    void internalSetRect(const QRectF &rect);

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const;
    void readFromStream(QDataStream &stream);
};
typedef QList<TRectObject*> TRectObjectList;

#endif // TRECTOBJECT_H
