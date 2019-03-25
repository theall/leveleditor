#ifndef TOBJECTITEM_H
#define TOBJECTITEM_H

#include <QList>
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>

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
    bool isCongener(TObjectItem *objectItem) const;

    virtual void propertyValueChanged(PropertyID pid) = 0;

    bool autonomy() const;
    void setAutonomy(bool autonomy);

    virtual void mousePressed(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoved(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleased(QGraphicsSceneMouseEvent *event);

    bool needGrabMouse() const;
    void setNeedGrabMouse(bool needGrabMouse);

signals:
    void boundingRectChanged();

private slots:
    void slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue);

private:
    TObject *mObject;
    bool mAutonomy;
    bool mNeedGrabMouse;
};

typedef QList<TObjectItem*> TObjectItemList;
#endif // TOBJECTITEM_H
