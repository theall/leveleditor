#include "object.h"
#include "../../base/tr.h"

static const QString P_POS = T("Position");
static const QString P_SIZE = T("Size");

TObject::TObject(Type type, QObject *parent) :
    TPropertyObject(parent)
  , mType(type)
{
    initPropertySheet();
}

TObject::Type TObject::type() const
{
    return mType;
}

QPointF TObject::pos() const
{
    return mPropertySheet->getValue(PID_OBJECT_POS).toPointF();
}

void TObject::setPos(const QPointF &pos)
{
    QPointF currentPos = mPropertySheet->getValue(PID_OBJECT_POS).toPointF();
    if(currentPos == pos)
        return;

    mPropertySheet->setValue(PID_OBJECT_POS, pos);
}

QSize TObject::size() const
{
    return mPropertySheet->getValue(PID_OBJECT_SIZE).toSize();
}

void TObject::setSize(const QSize &size)
{
    QSizeF currentSize = mPropertySheet->getValue(PID_OBJECT_SIZE).toSizeF();
    if(currentSize == size)
        return;

    mPropertySheet->setValue(PID_OBJECT_SIZE, size);
}

QRectF TObject::rect() const
{
    QPointF pos = mPropertySheet->getValue(PID_OBJECT_POS).toPointF();
    QSizeF size = mPropertySheet->getValue(PID_OBJECT_SIZE).toSizeF();
    return QRectF(pos, size);
}

void TObject::move(const QPointF &offset)
{
    if(offset.isNull())
        return;

    QPointF pos = mPropertySheet->getValue(PID_OBJECT_POS).toPointF();
    pos += offset;
    mPropertySheet->setValue(PID_OBJECT_POS, pos);
}

void TObject::initPropertySheet()
{
    mPropertySheet->addProperty(PT_VECTORF, P_POS, PID_OBJECT_POS);
    mPropertySheet->addProperty(PT_SIZE, P_POS, PID_OBJECT_SIZE);
}
