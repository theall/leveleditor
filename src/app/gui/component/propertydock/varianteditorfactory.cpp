#include "varianteditorfactory.h"
#include "variantpropertymanager.h"
#include "widget/pixmapedit.h"
#include "widget/soundsetedit.h"
#include "widget/sounditemedit.h"
#include "widget/sounditemsourceedit.h"

TVariantEditorFactory::~TVariantEditorFactory()
{

}

void TVariantEditorFactory::connectPropertyManager(QtVariantPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty*,QVariant)),
            this, SLOT(slotPropertyChanged(QtProperty*,QVariant)));
    connect(manager, SIGNAL(attributeChanged(QtProperty*,QString,QVariant)),
            this, SLOT(slotPropertyAttributeChanged(QtProperty*,QString,QVariant)));
    QtVariantEditorFactory::connectPropertyManager(manager);
}

QWidget *TVariantEditorFactory::createEditor(QtVariantPropertyManager *manager,
                                            QtProperty *property,
                                            QWidget *parent)
{
    TVariantPropertyManager *myManager = static_cast<TVariantPropertyManager*>(manager);
    if(myManager)
    {
        const int type = myManager->propertyType(property);
        if (type == TVariantPropertyManager::pixmapTypeId()) {
            TPixmapEdit *editor = new TPixmapEdit(parent);
            editor->setText(myManager->valueText(property));
            editor->setPixmap(myManager->valueIcon(property).pixmap(QSize(64,64)));
            mPixmapEditPropertyMap[editor] = property;

            connect(editor,
                    SIGNAL(getSelectedPixmap(QString&, QPixmap&)),
                    this,
                    SIGNAL(getSelectedImage(QString&, QPixmap&)));
            connect(editor,
                    SIGNAL(pixmapChanged(QString, QPixmap)),
                    this,
                    SLOT(slotPixmapEditChanged(QString, QPixmap)));
            connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
            return editor;
        } else if(type == TVariantPropertyManager::soundSetTypeId()) {
            TSoundSetEdit *editor = new TSoundSetEdit(parent);
            editor->setText(myManager->valueText(property));
            mSoundSetEditPropertyMap[editor] = property;
            mPropertySoundSetEditMap[property] = editor;
            connect(editor,
                    SIGNAL(requestAddSoundItem()),
                    this,
                    SIGNAL(requestAddSoundItem()));
            connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
            return editor;
        } else if(type == TVariantPropertyManager::soundItemTypeId()) {
            TSoundItemEdit *editor = new TSoundItemEdit(parent);
            editor->setText(myManager->valueText(property));
            editor->setContext(property);
            mSoundItemEditPropertyMap[editor] = property;
            connect(editor,
                    SIGNAL(requestRemoveProperty(void*)),
                    this,
                    SIGNAL(requestRemoveSoundItemProperty(void*)));
            connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
            return editor;
        } else if(type == TVariantPropertyManager::soundItemSourceTypeId()) {
            TSoundItemSourceEdit *editor = new TSoundItemSourceEdit(parent);
            editor->setText(myManager->valueText(property));
            editor->setMediaContent((QMediaContent*)myManager->context(property).value<void*>());
            mSoundItemSourceEditPropertyMap[editor] = property;
            connect(editor,
                    SIGNAL(getSelectedSound(QString&,QMediaContent*&)),
                    this,
                    SIGNAL(getSelectedSound(QString&,QMediaContent*&)));
            connect(editor,
                    SIGNAL(soundSourceChanged(QString,const QMediaContent*)),
                    this,
                    SLOT(slotSoundSourceChanged(QString,const QMediaContent*)));
            connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
            return editor;
        }
    }

    return QtVariantEditorFactory::createEditor(manager, property, parent);
}

void TVariantEditorFactory::disconnectPropertyManager(QtVariantPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty*,QVariant)),
               this, SLOT(slotPropertyChanged(QtProperty*,QVariant)));
    disconnect(manager, SIGNAL(attributeChanged(QtProperty*,QString,QVariant)),
               this, SLOT(slotPropertyAttributeChanged(QtProperty*,QString,QVariant)));
    QtVariantEditorFactory::disconnectPropertyManager(manager);
}

void TVariantEditorFactory::slotPropertyChanged(QtProperty *property,
                                               const QVariant &value)
{
    if(TSoundSetEdit *soundSetEdit = mPropertySoundSetEditMap.value(property, 0))
    {
        soundSetEdit->setText(value.toString());
    }
}

void TVariantEditorFactory::slotPropertyAttributeChanged(QtProperty *property,
                                                        const QString &attribute,
                                                        const QVariant &value)
{
    Q_UNUSED(property);
    Q_UNUSED(attribute);
    Q_UNUSED(value);
}

void TVariantEditorFactory::slotPixmapEditChanged(const QString &text, const QPixmap &pixmap)
{
    TPixmapEdit *pixmapEdit = qobject_cast<TPixmapEdit*>(sender());
    if(!pixmapEdit)
        return;

    if (QtProperty *property = mPixmapEditPropertyMap.value(pixmapEdit)) {
        TVariantPropertyManager *manager = static_cast<TVariantPropertyManager*>(propertyManager(property));
        if (!manager)
            return;
        manager->setValue(property, text, pixmap);
    }
}

void TVariantEditorFactory::slotSoundSourceChanged(const QString &newFile, const QMediaContent *newMediaContent)
{
    TSoundItemSourceEdit *soundItemSourceEdit = qobject_cast<TSoundItemSourceEdit*>(sender());
    if(!soundItemSourceEdit)
        return;

    if (QtProperty *property = mSoundItemSourceEditPropertyMap.value(soundItemSourceEdit)) {
        TVariantPropertyManager *manager = static_cast<TVariantPropertyManager*>(propertyManager(property));
        if (!manager)
            return;
        manager->setValue(property, newFile, QVariant::fromValue((void*)newMediaContent));
    }
}

void TVariantEditorFactory::slotEditorDestroyed(QObject *object)
{
    if(!object)
        return;

    object->disconnect(this);
    // Check if it was a TPixmapEdit
    if(TPixmapEdit *edit = static_cast<TPixmapEdit*>(object)) {
        edit->disconnect(this);
        mPixmapEditPropertyMap.remove(edit);
    } else if(TSoundSetEdit *edit = static_cast<TSoundSetEdit*>(object)) {
        edit->disconnect(this);
        mSoundSetEditPropertyMap.remove(edit);
    } else if(TSoundItemEdit *edit = static_cast<TSoundItemEdit*>(object)) {
        edit->disconnect(this);
        mSoundItemEditPropertyMap.remove(edit);
    } else if(TSoundItemSourceEdit *edit = static_cast<TSoundItemSourceEdit*>(object)) {
        edit->disconnect(this);
        mSoundItemSourceEditPropertyMap.remove(edit);
    }
}
