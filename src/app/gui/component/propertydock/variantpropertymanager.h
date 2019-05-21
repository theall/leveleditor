#ifndef VARIANTPROPERTYMANAGER_H
#define VARIANTPROPERTYMANAGER_H

#include "qtpropertybrowser/include/QtVariantPropertyManager"

#include <QFileIconProvider>

/**
 * Extension of the QtVariantPropertyManager that adds support for a filePath
 * data type.
 */
class TVariantPropertyManager : public QtVariantPropertyManager
{
    Q_OBJECT

public:
    explicit TVariantPropertyManager(QObject *parent = nullptr);

    QVariant context(const QtProperty *property) const;
    QVariant value(const QtProperty *property) const override;
    QString valueText(const QtProperty *property) const override;
    QIcon valueIcon(const QtProperty *property) const override;
    void setValue(QtProperty *property, const QVariant &val, const QVariant &context);

    int valueType(int propertyType) const override;
    bool isPropertyTypeSupported(int propertyType) const override;

    QStringList attributes(int propertyType) const override;
    int attributeType(int propertyType, const QString &attribute) const override;
    QVariant attributeValue(const QtProperty *property,
                            const QString &attribute) const override;

    static int enumTypeId();
    static int flagTypeId();
    static int groupTypeId();
    static int stringExTypeId();
    static int pixmapTypeId();
    static int soundSetTypeId();
    static int soundItemTypeId();
    static int soundItemSourceTypeId();

public slots:
    void setValue(QtProperty *property, const QVariant &val) override;
    void setAttribute(QtProperty *property,
                      const QString &attribute,
                      const QVariant &value) override;

protected:
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;

private:
    struct Data {
        QVariant text;
        QVariant context;
    };
    QMap<const QtProperty *, Data> mValues;
    QMap<const QtProperty *, QStringList> mSuggestions;

    const QString mSuggestionsAttribute;
    QIcon mImageMissingIcon;
};

#endif // VARIANTPROPERTYMANAGER_H
