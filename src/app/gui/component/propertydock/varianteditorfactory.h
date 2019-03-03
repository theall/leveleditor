#ifndef VARIANTEDITORFACTORY_H
#define VARIANTEDITORFACTORY_H

#include <qtpropertybrowser/QtVariantEditorFactory>

class QMediaContent;
class TPixmapEdit;
class TSoundSetEdit;
class TSoundItemEdit;
class TSoundItemSourceEdit;

/**
 * Extension of the QtVariantEditorFactory that adds support for pixmap and sound edit,
 * used for editing frame.
 *
 * It also adds support for a "suggestions" attribute for string values.
 */
class TVariantEditorFactory : public QtVariantEditorFactory
{
    Q_OBJECT

public:
    explicit TVariantEditorFactory(QObject *parent = nullptr)
        : QtVariantEditorFactory(parent)
    {}

    ~TVariantEditorFactory();

signals:
    void getSelectedImage(QString &text, QPixmap &pixmap);
    void getSelectedSound(QString &text, QMediaContent* &pixmap);
    void requestAddSoundItem();
    void requestRemoveSoundItemProperty(void*);

protected:
    void connectPropertyManager(QtVariantPropertyManager *manager) override;
    QWidget *createEditor(QtVariantPropertyManager *manager,
                          QtProperty *property,
                          QWidget *parent) override;
    void disconnectPropertyManager(QtVariantPropertyManager *manager) override;

private slots:
    void slotPropertyChanged(QtProperty *property, const QVariant &value);
    void slotPropertyAttributeChanged(QtProperty *property,
                                      const QString &attribute,
                                      const QVariant &value);

    void slotPixmapEditChanged(const QString &text, const QPixmap &pixmap);
    void slotSoundSourceChanged(const QString &newFile, const QMediaContent *newMediaContent);
    void slotEditorDestroyed(QObject *object);

private:
    QMap<TPixmapEdit*, QtProperty*> mPixmapEditPropertyMap;
    QMap<TSoundSetEdit*, QtProperty*> mSoundSetEditPropertyMap;
    QMap<QtProperty*, TSoundSetEdit*> mPropertySoundSetEditMap;
    QMap<TSoundItemEdit*, QtProperty*> mSoundItemEditPropertyMap;
    QMap<TSoundItemSourceEdit*, QtProperty*> mSoundItemSourceEditPropertyMap;
};

#endif // VARIANTEDITORFACTORY_H
