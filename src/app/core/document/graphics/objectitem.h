#ifndef TOBJECTITEM_H
#define TOBJECTITEM_H

#include <QGraphicsObject>
#include "../model/entity/object.h"

class TObjectItem : public QGraphicsObject
{
    Q_OBJECT

public:
    TObjectItem(TObject *object, QGraphicsItem *parent = nullptr);

    TObject *object() const;
    TObject::Type objectType() const;

private:
    TObject *mObject;
};

#endif // TOBJECTITEM_H
