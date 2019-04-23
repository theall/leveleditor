#include "object.h"
#include "../../base/tr.h"

static const QString P_POS = T("Position");
static const QString P_SIZE = T("Size");

TObject::TObject(Type type, QObject *parent, bool createPosProperty) :
    TPropertyObject(parent)
  , mType(type)
{
    if(createPosProperty)
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
    QSize currentSize = mPropertySheet->getValue(PID_OBJECT_SIZE).toSize();
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

void TObject::setRect(const QRectF &rect)
{
    if(rect.isEmpty())
        return;

    mPropertySheet->setValue(PID_OBJECT_POS, rect.topLeft());
    mPropertySheet->setValue(PID_OBJECT_SIZE, rect.size());
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
    mPropertySheet->addProperty(PT_SIZE, P_SIZE, PID_OBJECT_SIZE);
}
