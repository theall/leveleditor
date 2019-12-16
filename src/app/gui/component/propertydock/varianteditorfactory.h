#ifndef VARIANTEDITORFACTORY_H
#define VARIANTEDITORFACTORY_H

#include "qtpropertybrowser/include/QtVariantEditorFactory"

class TVariantEditorFactoryPrivate;

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
    explicit TVariantEditorFactory(QObject *parent = nullptr);
    ~TVariantEditorFactory();

protected:
    void connectPropertyManager(QtVariantPropertyManager *manager) override;
    QWidget *createEditor(QtVariantPropertyManager *manager,
                          QtProperty *property,
                          QWidget *parent) override;
    void disconnectPropertyManager(QtVariantPropertyManager *manager) override;

private:
    TVariantEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(TVariantEditorFactory)
    Q_DISABLE_COPY(TVariantEditorFactory)
};

#endif // VARIANTEDITORFACTORY_H
