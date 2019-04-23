#ifndef TTRACKITEM_H
#define TTRACKITEM_H

#include "../objectitem.h"

class TTrackItem : public QGraphicsItem
{
public:
    TTrackItem(TObjectItem *parent, TObjectItem *child);
    ~TTrackItem();

    TObjectItem *hostObjectItem() const;
    void setHostObjectItem(TObjectItem *hostObjectItem);
    TObjectItem *childObjectItem() const;
    void setChildObjectItem(TObjectItem *childObjectItem);

private:
    TObjectItem *mHostObjectItem;
    TObjectItem *mChildObjectItem;
    QRectF mBoundingRect;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};


#endif // TTRACKITEM_H
