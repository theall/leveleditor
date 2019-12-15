#ifndef PROPERTYITEM_H
#define PROPERTYITEM_H

#include <QMap>
#include <QObject>
#include <QString>
#include <QVariant>

#include "property.h"

enum PropertyType
{
    PT_INT = 0,
    PT_BOOL,
    PT_STRING,
    PT_DOUBLE,
    PT_VECTOR,
    PT_VECTORF,
    PT_POINT,
    PT_POINTF,
    PT_SIZE,
    PT_SIZEF,
    PT_RECT,
    PT_RECTF,
    PT_COLOR,
    PT_ENUM,
    PT_FLAG,
    PT_GROUP,
    PT_STRING_EX,
    PT_PIXMAP,
    PT_SOUND_SET,
    PT_SOUND_ITEM,
    PT_SOUND_ITEM_SOURCE,
    PT_COUNT
};

enum PropertyAttribute
{
    PA_CONSTRAINT,
    PA_SINGLE_STEP,
    PA_DECIMALS,
    PA_ENUM_ICONS,
    PA_ENUM_NAMES,
    PA_FLAGNAMES,
    PA_MAXIMUM,
    PA_MINIMUM,
    PA_REGEXP,
    PA_ECHO_MODE,
    PA_READ_ONLY,
    PA_TEXT_VISIBLE,
    PA_COUNT
};

class TDocument;
class TPropertyItem : public QObject
{
    Q_OBJECT

public:
    TPropertyItem(
            PropertyType type,
            const QString &name,
            QObject *parent=nullptr);
    TPropertyItem(
            PropertyType type,
            const QString &name,
            PropertyID propertyId,
            QObject *parent=nullptr);
    ~TPropertyItem();

    int type() const;
    void setType(int type);

    QString name() const;
    void setName(const QString &name);

    QMap<QString, QVariant> attributes() const;
    void setAttributes(const QMap<QString, QVariant> &attributes);
    void setAttributes(const QMap<PropertyAttribute, QVariant> &attributes);

    void setAttribute(const QString &name, const QVariant &value);
    void setAttribute(const PropertyAttribute &attribute, const QVariant &value);
    void setRange(int max = 0x7fffffff, int min = 1, int step = 1);

    void addAttribute(const QString &name, const QVariant &value);
    void addAttribute(const PropertyAttribute &attribute, const QVariant &value);
    void addDirectionAttribute();

    void setReadOnly(bool readOnly = true);

    QVariant value() const;
    void setValue(const QVariant &value, bool emitSignal = true);

    // This function will set the value of undocommand.After that, it will find
    // the TDocument object, then push mUndoCommand to undostack
    void setNewValue(const QVariant &value);

    PropertyID propertyId() const;

    QList<TPropertyItem *> subPropertyItems() const;
    void setSubPropertyItems(const QList<TPropertyItem *> &subPropertyItems);
    void addSubPropertyItems(const QList<TPropertyItem *> &subPropertyItems);
    void addSubPropertyItem(TPropertyItem *propertyItem);

    QString toolTip() const;
    void setToolTip(const QString &toolTip);

    QString statusTip() const;
    void setStatusTip(const QString &statusTip);

signals:
    void valueChanged(const QVariant &oldValue, const QVariant &newValue);
    void attributeChanged(const QString &name, const QVariant &value);

private:
    int mType;
    QString mName;
    QVariant mValue;
    QString mToolTip;
    QString mStatusTip;
    QMap<QString, QVariant> mAttributes;

    PropertyID mPropertyId;
    TDocument *mDocument;
    QList<TPropertyItem*> mSubPropertyItems;
};
typedef QList<TPropertyItem*> TPropertyItems;

#define ADD_ENUM_NAMES(propertyItem,size,Type) \
QStringList sl; \
for(int i=0;i<size;i++) \
{ \
    sl.append(QString::fromStdString(Type##ToString((Type)i))); \
} \
propertyItem->addAttribute(PA_ENUM_NAMES, sl)

#endif // PROPERTYITEM_H
