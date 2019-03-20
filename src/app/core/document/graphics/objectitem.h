#ifndef TOBJECTITEM_H
#define TOBJECTITEM_H

#include <QList>
#include <QGraphicsObject>
#include "../model/entity/object.h"

class TObjectItem : public QGraphicsObject
{
    Q_OBJECT

public:
    enum { Type = UserType + 1 };
    TObjectItem(TObject *object, QGraphicsItem *parent = nullptr);

    int type() const;

    TObject *object() const;
    TObject::Type objectType() const;

private:
    TObject *mObject;
};

typedef QList<TObjectItem*> TObjectItemList;
#endif // TOBJECTITEM_H
