#ifndef TSELECTEDITEMS
#define TSELECTEDITEMS

#include "selecteditem.h"
#include <QMap>

class TSelectedItems : public QGraphicsObject
{
public:
    TSelectedItems(QGraphicsItem *parent = nullptr);
    ~TSelectedItems();

    void setObjectItemList(const TObjectItemList &objectItemList);
    void setObjectItem(TObjectItem *objectItem);

    int addObjectItem(TObjectItem *objectItem);
    int removeObjectItem(TObjectItem *objectItem);
    bool containsObjectItem(TObjectItem *objectItem) const;
    TObjectItemList getSelectedObjectItemList() const;
    TObjectList getSelectedObjectList() const;

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    // Marching ants effect
    int mUpdateTimer;
    QRectF mBoundingRect;
    QMap<TObjectItem*, TSelectedItem*> mObjectItemMap;

    void updateBoundingRect();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // TSELECTEDITEMS
