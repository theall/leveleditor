#include "propertycontroller.h"
#include "tabcontroller.h"
#include "../core/assets/sound.h"
#include "../core/assets/pixmap.h"
#include "../gui/component/propertydock/propertybrowser.h"
#include "../gui/component/propertydock/variantpropertymanager.h"
#include "../gui/dialogs/soundresourcedialog.h"

#include <QDebug>
#include <QStandardItem>

const int g_propertyTypeMap[PT_COUNT] = {
    QVariant::Int,//PT_INT
    QVariant::Bool,//PT_BOOL
    QVariant::String,//PT_STRING
    QVariant::Double,//PT_DOUBLE
    QVariant::Point,//PT_VECTOR
    QVariant::PointF,//PT_VECTORF
    QVariant::Point,//PT_POINT
    QVariant::PointF,//PT_POINTF
    QVariant::Size,//PT_SIZE
    QVariant::SizeF,//PT_SIZEF
    QVariant::Rect,//PT_RECT
    QVariant::RectF,//PT_RECTF
    QVariant::Color,//PT_COLOR
    TVariantPropertyManager::enumTypeId(),//PT_ENUM
    TVariantPropertyManager::flagTypeId(),//PT_FLAG
    TVariantPropertyManager::groupTypeId(),//PT_GROUP
    TVariantPropertyManager::stringExTypeId(),//PT_STRING_EX
    TVariantPropertyManager::pixmapTypeId(),//PT_PIXMAP
    TVariantPropertyManager::soundSetTypeId(),//PT_SOUND_SET
    TVariantPropertyManager::soundItemTypeId(),//PT_SOUND_ITEM
    TVariantPropertyManager::soundItemSourceTypeId(),//PT_SOUND_ITEM_SOURCE
    TVariantPropertyManager::dirTypeId()
};

TPropertyController::TPropertyController(QObject *parent) :
    TAbstractController(parent)
  , mIsRendering(false)
  , mPropertyManager(new TVariantPropertyManager(this))
  , mPropertyBrowser(nullptr)
  , mPropertySheet(nullptr)
  , mSoundResourceDialog(nullptr)
{
    connect(mPropertyManager, SIGNAL(valueChanged(QtProperty*,QVariant)),
            SLOT(slotPropertyValueChanged(QtProperty*,QVariant)));
}

TPropertyController::~TPropertyController()
{

}

bool TPropertyController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    return TAbstractController::joint(mainWindow, core);
}

void TPropertyController::setCurrentDocument(TDocument *document)
{
    if(!document)
        setPropertySheet(nullptr);
}

void TPropertyController::setPropertyBrowser(TPropertyBrowser *propertyBrowser)
{
    if(mPropertyBrowser==propertyBrowser || !propertyBrowser)
        return;

    if(mPropertyBrowser)
        mPropertyBrowser->disconnect(this);

    mPropertyBrowser = propertyBrowser;
    mPropertyBrowser->setPropertyManager(mPropertyManager);

    connect(mPropertyBrowser,
            SIGNAL(currentItemChanged(QtBrowserItem*)),
            this,
            SLOT(slotCurrentItemChanged(QtBrowserItem*)));
}

TPropertySheet *TPropertyController::propertySheet() const
{
    return mPropertySheet;
}

void TPropertyController::slotGetSelectedSound(QString &text, QMediaContent *&mediaContent)
{
    if(!mDocument)
        return;

    QString soundFile = mSoundResourceDialog->getSelectedSound();
    TSound *sound = nullptr;
    if(sound)
    {
        text = soundFile;
        mediaContent = sound->mediaContent();
    } else {
        text.clear();
        mediaContent = nullptr;
    }
}

void TPropertyController::slotPropertyAttributeChanged(const QString &attr, const QVariant &value)
{
    TPropertyItem *propertyItem = static_cast<TPropertyItem*>(sender());
    if(!propertyItem)
        return;

    QtVariantProperty *property = mItemPropertyMap[propertyItem];
    if(!property)
        return;

    property->setAttribute(attr, value);
}

void TPropertyController::setPropertySheet(TPropertySheet *propertySheet)
{
    if(mPropertySheet == propertySheet)
        return;

    if(mPropertySheet)
        mPropertySheet->disconnect(this);

    TPropertyItem *currentPropertyItem = findPropertyItem(mPropertyBrowser->currentItem());
    mPropertySheet = propertySheet;
    mPropertyManager->clear();

    if(!propertySheet)
        return;

    mItemPropertyMap.clear();
    mPropertyItemMap.clear();

    connect(propertySheet,
            SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant)));

    for(TPropertyItem *propertyItem : propertySheet->propertyList())
    {
        QtVariantProperty *property = createProperty(propertyItem);
        if(property) {
            mPropertyBrowser->addProperty(property);
        } else {
            throw tr("Null property created from property item name:%1").arg(propertyItem->name());
        }
    }
    if(currentPropertyItem)
    {
        // Try to restore old actived browser item.
        QtBrowserItem *browserItem = findBrowserItem(currentPropertyItem->propertyId());
        if(browserItem)
            mPropertyBrowser->setCurrentItem(browserItem);
    }
}

TPropertyItem *TPropertyController::findPropertyItem(QtBrowserItem *browserItem)
{
    if(!browserItem)
        return nullptr;

    QtVariantProperty *variantProperty = static_cast<QtVariantProperty*>(browserItem->property());
    return mPropertyItemMap.value(variantProperty, nullptr);
}

QtBrowserItem *TPropertyController::findBrowserItem(TPropertyItem *propertyItem)
{
    if(!propertyItem)
        return nullptr;

    QtVariantProperty *property = mItemPropertyMap.value(propertyItem, nullptr);
    if(!property)
        return nullptr;

    QList<QtBrowserItem *> browserItems = mPropertyBrowser->items(mItemPropertyMap.value(propertyItem));
    if(browserItems.size() > 0)
        return browserItems.at(0);

    return nullptr;
}

QtBrowserItem *TPropertyController::findBrowserItem(PropertyID propertyId)
{
    for(TPropertyItem *propertyItem : mItemPropertyMap.keys())
    {
        if(propertyItem->propertyId() == propertyId)
        {
            QList<QtBrowserItem *> browserItems = mPropertyBrowser->items(mItemPropertyMap.value(propertyItem));
            if(browserItems.size() > 0)
                return browserItems.at(0);
            break;
        }
    }
    return nullptr;
}

QtVariantProperty *TPropertyController::createProperty(TPropertyItem *propertyItem)
{
    if(!propertyItem)
        return nullptr;

    PropertyType propertyType = (PropertyType)propertyItem->type();
    QtVariantProperty *p = mPropertyManager->addProperty(g_propertyTypeMap[propertyType], propertyItem->name());
    if(!p) {
        qDebug() << "Failed to create property with property type" << propertyType;
        return nullptr;
    }

    QMap<QString, QVariant> attributes = propertyItem->attributes();
    for(QString attrName : attributes.keys())
    {
        p->setAttribute(attrName, attributes[attrName]);
    }
    if(propertyType == PT_PIXMAP) {
        QVariant fileName = propertyItem->value();
        TPixmap *pixmap = nullptr;
        if(pixmap)
        {
            //mPropertyManager->setValue(p, fileName, pixmap->thumbnail());
        } else {
            p->setValue(fileName);
        }
    } else if(propertyType == PT_SOUND_ITEM_SOURCE) {
        QVariant fileName = propertyItem->value();
        TSound *sound = nullptr;
        if(sound)
        {
            //mPropertyManager->setValue(p, fileName, QVariant::fromValue((void*)sound->mediaContent()));
        } else {
            p->setValue(fileName);
        }
    } else {
        p->setValue(propertyItem->value());
    }
    p->setToolTip(propertyItem->toolTip());
    p->setStatusTip(propertyItem->statusTip());
    mItemPropertyMap[propertyItem] = p;
    mPropertyItemMap[p] = propertyItem;

    for(TPropertyItem *subPropertyItem : propertyItem->subPropertyItems())
    {
        QtVariantProperty *subProperty = createProperty(subPropertyItem);
        p->addSubProperty(subProperty);
    }

    connect(propertyItem, SIGNAL(attributeChanged(QString,QVariant)), this, SLOT(slotPropertyAttributeChanged(QString,QVariant)));
    return p;
}

void TPropertyController::slotPropertyValueChanged(QtProperty *property, const QVariant &newValue)
{
    if(mIsRendering)
        return;

    TPropertyItem *item = mPropertyItemMap[(QtVariantProperty*)property];
    if(item)
    {
        emit propertyItemValueChanged(item, newValue);
    }
}

void TPropertyController::slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue)
{
    Q_UNUSED(oldValue);

    mIsRendering = true;
    QtVariantProperty *property = mItemPropertyMap[item];
    if(property)
    {
        property->setValue(item->value());
    }
    mIsRendering = false;
}

void TPropertyController::slotCurrentItemChanged(QtBrowserItem *browserItem)
{
    if(!browserItem)
        return;

    TPropertyItem *propertyItem = findPropertyItem(browserItem);
    if(!propertyItem)
    {
        propertyItem = findPropertyItem(browserItem->parent());
    }
    emit propertyItemActived(propertyItem);
}

void TPropertyController::slotGetSelectedImage(QString &text, QPixmap &pixmap)
{
    QStandardItem *item = nullptr;
    if(item)
    {
        text = item->text();
        pixmap = item->icon().pixmap(QSize(64,64));
    }
}

void TPropertyController::slotTimerEvent()
{

}
