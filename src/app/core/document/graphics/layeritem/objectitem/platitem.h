#ifndef TPLATITEM_H
#define TPLATITEM_H

#include "rectobjectitem.h"
#include "../../../model/entity/plat.h"

class TPlatItem : public TRectObjectItem
{
    Q_OBJECT

public:
    explicit TPlatItem(TPlat *plat, QGraphicsItem *parent = Q_NULLPTR);
    ~TPlatItem();

    TPlat *plat() const;

private:
    TPlat *mPlat;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};
typedef QList<TPlatItem*> TPlatItemList;

#endif // TPLATITEM_H
