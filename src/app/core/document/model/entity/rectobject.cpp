#include "rectobject.h"
#include "../../base/tr.h"

static const QString P_RECT = T("Rect");

TRectObject::TRectObject(TObject::Type type, QObject *parent) :
    TObject(type, parent)
{
    initPropertySheet();
}

TRectObject::TRectObject(const QRect &rect, TObject::Type type, QObject *parent) :
    TObject(type, parent)
{
    initPropertySheet();
    setRect(rect);
}

TRectObject::~TRectObject()
{

}

QSize TRectObject::size() const
{
    return getRect().size().toSize();
}

void TRectObject::setSize(const QSize &size)
{
    QRectF rect = getRect();
    rect.setSize(size);
    mRectPropertyItem->setValue(rect);
}

QRectF TRectObject::getRect() const
{
    return mRectPropertyItem->value().toRectF();
}

void TRectObject::setRect(const QRectF &rect)
{
    mRectPropertyItem->setValue(rect);
}

void TRectObject::setRect(int x, int y, int w, int h)
{
    setRect(QRectF(x,y,w,h));
}

QPointF TRectObject::getPos() const
{
    return mRectPropertyItem->value().toRectF().topLeft();
}

void TRectObject::setPos(const QPointF &pos)
{
    QRectF currentRect = mRectPropertyItem->value().toRectF();
    currentRect.moveTo(pos);
    mRectPropertyItem->setValue(currentRect);
}

void TRectObject::adjust(const QMarginsF &margins)
{
    if(margins.isNull())
        return;

    QRectF currentRect = getRect();
    currentRect += margins;
    setRect(currentRect);
}

void TRectObject::move(const QPointF &offset)
{
    if(offset.isNull())
        return;

    QRectF currentRect = getRect();
    currentRect.translate(offset);
    mRectPropertyItem->setValue(currentRect);
}

void TRectObject::initPropertySheet()
{
    mRectPropertyItem = mPropertySheet->addProperty(PT_RECTF, P_RECT, PID_OBJECT_RECT);
}

void TRectObject::saveToStream(QDataStream &) const
{

}

void TRectObject::readFromStream(QDataStream &)
{

}

QByteArray TRectObject::toByteArray(TObject *object) const
{

}

void TRectObject::loadFromByteArray(const QByteArray &byteArray)
{

}
