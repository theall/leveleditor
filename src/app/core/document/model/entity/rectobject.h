#ifndef TRECTOBJECT_H
#define TRECTOBJECT_H

#include "pointobject.h"

class TRectObject : public TPointObject
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

private:
    TPropertyItem *mSizePropertyItem;

    void initPropertySheet();
    void internalSetRect(const QRectF &rect);

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const;
    void readFromStream(QDataStream &stream);
};

#endif // TRECTOBJECT_H
