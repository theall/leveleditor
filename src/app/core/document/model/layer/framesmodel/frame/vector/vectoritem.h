#ifndef VECTORITEM_H
#define VECTORITEM_H

#include <QString>
#include <QPointF>
#include "../../../../../base/docobject.h"
#include "../../../../../../../../../../../utils/base/variable.h"

namespace Model {
class TVectorItem;
}

class TVectorItem : public TDocObject
{
    Q_OBJECT

public:
    TVectorItem(QObject *parent = nullptr);
    virtual ~TVectorItem();

    void loadFromModel(const Model::TVectorItem &vectorItemModel, void *context = nullptr);
    Model::TVectorItem *toModel() const;

    VectorType vectorType() const;
    void setVectorType(const VectorType &vectorType);

    QPointF vector() const;
    void setVector(const QPointF &vector);

signals:
    void propertyChanged(TPropertyItem *propertyItem, const QVariant &value);

private slots:
    void slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &value);

private:
};
typedef QList<TVectorItem *> TVectorItemList;

QDataStream &operator<<(QDataStream& out, const TVectorItem& vectorItem);
QDataStream &operator>>(QDataStream& in, TVectorItem& vectorItem);

#endif // VECTORITEM_H
