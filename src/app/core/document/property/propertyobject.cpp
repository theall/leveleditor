#include "propertyobject.h"

#include <QPoint>
#include <QPointF>
#include <QSize>
#include <QSizeF>
#include <QRect>
#include <QRectF>

TPropertyObject::TPropertyObject(QObject *parent) :
    QObject(parent)
  , mPropertySheet(new TPropertySheet(this))
{
}

TPropertyObject::~TPropertyObject()
{
    delete mPropertySheet;
}

TPropertySheet *TPropertyObject::propertySheet() const
{
    return mPropertySheet;
}

TPropertyItems TPropertyObject::propertyItems() const
{
    return mPropertySheet->propertyList();
}

QVariant TPropertyObject::getValue(const QString &name) const
{
    return mPropertySheet->getValue(name);
}

void TPropertyObject::setValue(const QString &name, const QVariant &value, bool emitSignal)
{
    mPropertySheet->setValue(name, value, emitSignal);
}

TPropertyItem *TPropertyObject::operator [](const QString &name) const
{
    return mPropertySheet->get(name);
}

TPropertyItem *TPropertyObject::get(const QString &name) const
{
    return mPropertySheet->get(name);
}

QVariant TPropertyObject::getValue(const PropertyID &pid) const
{
    return mPropertySheet->getValue(pid);
}

void TPropertyObject::setValue(const PropertyID &pid, const QVariant &value, bool emitSignal)
{
    mPropertySheet->setValue(pid, value, emitSignal);
}

TPropertyItem *TPropertyObject::operator [](const PropertyID &pid) const
{
    return mPropertySheet->get(pid);
}

TPropertyItem *TPropertyObject::get(const PropertyID &pid) const
{
    return mPropertySheet->get(pid);
}

QString TPropertyObject::toString() const
{
    QStringList sl;
    for(TPropertyItem *propertyItem : mPropertySheet->propertyList()) {
        QVariant v = propertyItem->value();
        QString vs;
        switch (v.type()) {
        case QVariant::Int:
            vs = QString::number(v.toInt());
            break;
        case QVariant::Point:
            vs = QString("(%1,%2)").arg(v.toPoint().x()).arg(v.toPoint().y());
            break;
        case QVariant::PointF:
            vs = QString("(%1,%2)").arg(v.toPointF().x()).arg(v.toPointF().y());
            break;
        case QVariant::Size:
            vs = QString("(%1,%2)").arg(v.toSize().width()).arg(v.toSize().height());
            break;
        case QVariant::SizeF:
            vs = QString("(%1,%2)").arg(v.toSizeF().width()).arg(v.toSizeF().height());
            break;
        case QVariant::Rect:
        {
            QRect rect = v.toRect();
            vs = QString("(%1,%2 %3,%4)").arg(rect.x()).arg(rect.y()).arg(rect.width()).arg(rect.height());
            break;
        }
        case QVariant::RectF:
        {
            QRectF rect = v.toRectF();
            vs = QString("(%1,%2 %3,%4)").arg(rect.x()).arg(rect.y()).arg(rect.width()).arg(rect.height());
            break;
        }
        default:
            break;
        }
        QString s = propertyItem->name() + ": " + vs;
        sl.append(s);
    }
    return sl.join("\n");
}
