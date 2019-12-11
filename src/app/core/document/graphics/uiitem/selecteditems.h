#ifndef TSELECTEDITEMS
#define TSELECTEDITEMS

#include "selecteditem.h"

#include "../../model/entity/rectobject.h"

#include "../layeritem/objectitem/objectitem.h"
#include "../layeritem/objectitem/tileitem.h"

#include <QMap>

class TSelectedItems : public QGraphicsObject
{
public:
    TSelectedItems(QGraphicsItem *parent = nullptr);
    ~TSelectedItems();

    void setObjectItemList(const TObjectItemList &objectItemList);
    void setObjectItem(TObjectItem *objectItem);

    int addObjectItem(TObjectItem *objectItem);
    int addObjectItems(const TObjectItemList &objectItemList);
    int removeObjectItem(TObjectItem *objectItem);
    bool containsObjectItem(TObjectItem *objectItem) const;
    TObjectItemList getSelectedObjectItemList() const;
    TTileItemList getSelectedTileItemList() const;
    TObjectList getSelectedObjectList() const;
    TRectObjectList getSelectedRectObjectList() const;

    void clear();
    bool isEmpty() const;

    void move(const QPointF &offset);

    /**
     * @brief Retrieve object's type if all objects are congeneric.
     * @return TObject::Type
     */
    TObject::Type getObjectType() const;

    bool startResizing();
    void endResizing();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    // Marching ants effect
    int mUpdateTimer;
    QRectF mBoundingRect;
    QMap<TObjectItem*, TSelectedItem*> mObjectItemMap;
    QMap<TObject*, TSelectedItem*> mObjectMap;

    void updateBoundingRect();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // TSELECTEDITEMS
