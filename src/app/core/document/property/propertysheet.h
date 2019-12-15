#ifndef PROPERTYSHEET_H
#define PROPERTYSHEET_H

#include "propertyitem.h"

class TPropertySheet : public QObject
{
    Q_OBJECT

public:
    TPropertySheet(QObject *parent = nullptr);
    ~TPropertySheet();

    TPropertyItems propertyList() const;
    void addProperty(
            TPropertyItem *propertyItem,
            TPropertyItem *parent = nullptr,
            TPropertyItem *beforeProperty = nullptr);
    void addProperty(
            const TPropertyItems &propertyItemList,
            TPropertyItem *parent = nullptr,
            TPropertyItem *beforeProperty = nullptr);
    TPropertyItem *addProperty(
            PropertyType type,
            const QString &name,
            PropertyID undoCommand,
            const QVariant &value=QVariant(),
            TPropertyItem *parent = nullptr,
            TPropertyItem *beforeProperty = nullptr);
    TPropertyItem *addGroupProperty(
            const QString &name,
            TPropertyItem *parent = nullptr,
            TPropertyItem *beforeProperty = nullptr);

    void removeProperty(TPropertyItem *propertyItem);
    void removeProperty(const TPropertyItems &propertyItemList);

    QVariant getValue(const QString &name) const;
    void setValue(const QString &name, const QVariant &value, bool emitSignal = true);
    TPropertyItem *operator [](const QString &name) const;
    TPropertyItem *get(const QString &name) const;
    QVariant getValue(const PropertyID &pid) const;
    void setValue(const PropertyID &pid, const QVariant &value, bool emitSignal = true);
    TPropertyItem *operator [](const PropertyID &pid) const;
    TPropertyItem *get(const PropertyID &pid) const;
    void setNewValue(const PropertyID &pid, const QVariant &value);

    void clear();

    QString getContextName();
    void setContextName(const QString &contextName);

    QStringList names() const;

signals:
    void propertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue);
    void propertyItemsAdded(const TPropertyItems &propertyItemList, TPropertyItem *parent);
    void propertyItemsRemoved(const TPropertyItems &propertyItemList);

private:
    QString mContextName;
    QMap<QString, TPropertyItem*> mPropertyMap;
    QMap<PropertyID, TPropertyItem*> mPropertyIdMap;

    void internalAddProperty(TPropertyItem *propertyItem, TPropertyItem *parent, TPropertyItem *beforeProperty = nullptr);

private slots:
    void slotPropertyItemValueChanged(const QVariant &oldValue, const QVariant &newValue);

};

#endif // PROPERTYSHEET_H
