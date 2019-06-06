#ifndef PROPERTYCONTROLLER_H
#define PROPERTYCONTROLLER_H

#include "abstractcontroller.h"

#include <QMap>
#include <QPixmap>
#include <QMediaContent>
#include "gui/component/propertydock/qtpropertybrowser/include/QtVariantPropertyManager"

class TPropertyBrowser;
class TSoundResourceDialog;
class TVariantPropertyManager;

class TPropertyController : public TAbstractController
{
    Q_OBJECT

public:
    TPropertyController(QObject *parent = 0);
    ~TPropertyController();

    virtual bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    virtual void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;
    virtual void setPropertySheet(TPropertySheet *propertySheet);
    void setPropertyBrowser(TPropertyBrowser *propertyBrowser);

    TPropertySheet *propertySheet() const;

signals:
    // To parent controller
    void propertyItemValueChanged(TPropertyItem *propertyItem, const QVariant &newValue);
    void propertyItemActived(TPropertyItem *propertyItem);

private:
    bool mIsRendering;
    TVariantPropertyManager *mPropertyManager;
    TPropertyBrowser *mPropertyBrowser;
    TPropertySheet *mPropertySheet;
    TSoundResourceDialog *mSoundResourceDialog;
    QMap<TPropertyItem*, QtVariantProperty*> mItemPropertyMap;
    QMap<QtVariantProperty*, TPropertyItem*> mPropertyItemMap;

    TPropertyItem *findPropertyItem(QtBrowserItem *browserItem);
    QtBrowserItem *findBrowserItem(TPropertyItem *propertyItem);
    QtBrowserItem *findBrowserItem(PropertyID propertyId);
    QtVariantProperty *createProperty(TPropertyItem *propertyItem);

private slots:
    void slotPropertyValueChanged(QtProperty *property, const QVariant &val);
    void slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue);
    void slotCurrentItemChanged(QtBrowserItem * browserItem);
    void slotGetSelectedImage(QString &text, QPixmap &pixmap);
    void slotGetSelectedSound(QString &text, QMediaContent *&mediaContent);
    void slotPropertyAttributeChanged(const QString &attr, const QVariant &value);

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // PROPERTYCONTROLLER_H
