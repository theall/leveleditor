#include "object.h"
#include "../../base/tr.h"

static const QString P_RECT = T("Rect");

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

QRectF TObject::rect() const
{
    return mPropertySheet->getValue(PID_OBJECT_RECT).toRectF();
}

QPointF TObject::pos() const
{
    return mPropertySheet->getValue(PID_OBJECT_RECT).toRectF().topLeft();
}

void TObject::setPos(const QPointF &pos)
{
    QRectF currentRect = mPropertySheet->getValue(PID_OBJECT_RECT).toRectF();
    QPointF currentPos = currentRect.topLeft();
    if(currentPos == pos)
        return;

    currentRect.moveTo(pos);
    mPropertySheet->setValue(PID_OBJECT_RECT, currentRect);
}

QSize TObject::size() const
{
    return mPropertySheet->getValue(PID_OBJECT_RECT).toRectF().size().toSize();
}

void TObject::setSize(const QSize &size)
{
    QRectF currentRect = mPropertySheet->getValue(PID_OBJECT_RECT).toRectF();
    QSize currentSize = currentRect.size().toSize();
    if(currentSize == size)
        return;

    currentRect.setSize(currentSize);
    mPropertySheet->setValue(PID_OBJECT_RECT, currentRect);
}

void TObject::setRect(const QRectF &rect)
{
    QRectF currentRect = mPropertySheet->getValue(PID_OBJECT_RECT).toRectF();
    if(currentRect == rect)
        return;

    mPropertySheet->setValue(PID_OBJECT_RECT, rect);
}

void TObject::move(const QPointF &offset)
{
    if(offset.isNull())
        return;

    QRectF currentRect = mPropertySheet->getValue(PID_OBJECT_RECT).toRectF();
    currentRect.moveTopLeft(currentRect.topLeft()+offset);
    mPropertySheet->setValue(PID_OBJECT_RECT, currentRect);
}

void TObject::initPropertySheet()
{
    mPropertySheet->addProperty(PT_VECTORF, P_RECT, PID_OBJECT_RECT);
}

bool TObject::visible() const
{
    return mVisible;
}

void TObject::setVisible(bool visible)
{
    mVisible = visible;
}
