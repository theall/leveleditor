#include "vectoritem.h"
#include "../../../../../base/docutil.h"
#include "../../../../../../../../../../../utils/model/character/vectoritem.h"

static const char *P_TYPE = "Type";
static const char *P_VECTOR = "Vector";

TVectorItem::TVectorItem(QObject *parent) :
    TDocObject(parent)
{
    connect(mPropertySheet,
            SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant)));

    TPropertyItem *propertyItem = mPropertySheet->addProperty(PT_ENUM, P_TYPE, PID_VECTOR_ITEM_TYPE, VT_RELATIVE);
    ADD_ENUM_NAMES(propertyItem,VT_COUNT,VectorType);
    mPropertySheet->addProperty(PT_VECTOR, P_VECTOR, PID_VECTOR_ITEM_VECTOR);
}

void TVectorItem::loadFromModel(const Model::TVectorItem &vectorItemModel, void *context)
{
    Q_UNUSED(context);
    (*mPropertySheet)[P_TYPE]->setValue(vectorItemModel.vectorType());
    (*mPropertySheet)[P_VECTOR]->setValue(DocUtil::toPointF(vectorItemModel.vector()));
}

TVectorItem::~TVectorItem()
{

}

Model::TVectorItem *TVectorItem::toModel() const
{
    Model::TVectorItem *vectorItemModel = new Model::TVectorItem;
    vectorItemModel->setVectorType((VectorType)(*mPropertySheet)[P_TYPE]->value().toInt());
    vectorItemModel->setVector(DocUtil::toVector2(mPropertySheet->getValue(P_VECTOR).toPointF()));
    return vectorItemModel;
}

void TVectorItem::slotPropertyItemValueChanged(TPropertyItem *propertyItem, const QVariant &value)
{
    emit propertyChanged(propertyItem, value);
}

QPointF TVectorItem::vector() const
{
    return mPropertySheet->getValue(P_VECTOR).toPointF();
}

void TVectorItem::setVector(const QPointF &vector)
{
    (*mPropertySheet)[P_VECTOR]->setValue(vector);
}

VectorType TVectorItem::vectorType() const
{
    return (VectorType)mPropertySheet->getValue(P_TYPE).toInt();
}

void TVectorItem::setVectorType(const VectorType &vectorType)
{
    (*mPropertySheet)[P_TYPE]->setValue(vectorType);
}

QDataStream &operator<<(QDataStream &out, const TVectorItem &vectorItem)
{
    out << (int)vectorItem.vectorType();
    out << vectorItem.vector();
    return out;
}

QDataStream &operator>>(QDataStream &in, TVectorItem &vectorItem)
{
    int vectorType;
    QPointF vector;
    in >> vectorType;
    in >> vector;
    vectorItem.setVectorType((VectorType)vectorType);
    vectorItem.setVector(vector);
    return in;
}
