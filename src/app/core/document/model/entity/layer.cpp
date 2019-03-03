#include "layer.h"
#include "../../document.h"

static const char *P_NAME = "Name";
static const char *P_OFFSET = "Offset";

TLayer::TLayer(const QString &name=QString(), QObject *parent) :
    TPropertyObject(parent)
  , mName(name)
  , mDocument(nullptr)
{
    setObjectName("Layer");

    QObject *obj = parent;
    while (obj) {
        mDocument = qobject_cast<TDocument*>(obj);
        if(mDocument)
            break;
        obj = obj->parent();
    }
    if(!mDocument)
        throw QString("File:%1, Line:%2: Parent must be document.").arg(__FILE__).arg(__LINE__);

    initPropertySheet();
}

TLayer::~TLayer()
{

}

void TLayer::readFromStream(const QDataStream &stream, void *context)
{
    TDocument *document = static_cast<TDocument*>(context);
    if(!document)
        return;

}

QString TLayer::name() const
{
    return (*mPropertySheet)[P_NAME]->value().toString();
}

void TLayer::setName(const QString &name)
{
    (*mPropertySheet)[P_NAME]->setNewValue(name);
}

QPointF TLayer::offset() const
{
    return (*mPropertySheet)[P_OFFSET]->value().toPointF();
}

void TLayer::setOffset(const QPointF &offset)
{
    (*mPropertySheet)[P_OFFSET]->setNewValue(offset);
}

void TLayer::slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &value)
{
    if(!item)
        return;

    PropertyID command = item->propertyId();
    switch (command) {
    default:
        break;
    }
}

TPropertySheet *TLayer::propertySheet() const
{
    return mPropertySheet;
}

void TLayer::initPropertySheet()
{
    connect(mPropertySheet,
            SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant)));

}

void TLayer::saveToStream(QDataStream &stream) const
{

}

void TLayer::readFromStream(QDataStream &stream)
{

}
