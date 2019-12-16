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

    QVariant value(const QtProperty *property) const override;
    QString valueText(const QtProperty *property) const override;
    QIcon valueIcon(const QtProperty *property) const override;

    int valueType(int propertyType) const override;
    bool isPropertyTypeSupported(int propertyType) const override;

    QStringList attributes(int propertyType) const override;
    int attributeType(int propertyType, const QString &attribute) const override;
    QVariant attributeValue(const QtProperty *property,
                            const QString &attribute) const override;

    static int stringExTypeId();
    static int pixmapTypeId();
    static int soundSetTypeId();
    static int soundItemTypeId();
    static int soundItemSourceTypeId();
    static int dirTypeId();

public slots:
    void setValue(QtProperty *property, const QVariant &val) override;
    void setAttribute(QtProperty *property,
                      const QString &attribute,
                      const QVariant &value) override;

protected:
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;

private:
    bool isCustomizedPropertyType(int propertyType) const;
    bool isCustomizedProperty(const QtProperty *property) const;

private slots:
    void slotValueChanged(QtProperty *property, int value);
};

#endif // VARIANTPROPERTYMANAGER_H
