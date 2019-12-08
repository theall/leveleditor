#include "rectobject.h"
#include "../../base/tr.h"

static const QString P_SIZE = T("Size");

TRectObject::TRectObject(TObject::Type type, QObject *parent) :
    TPointObject(type, parent)
{
    initPropertySheet();
}

TRectObject::TRectObject(const QRect &rect, TObject::Type type, QObject *parent) :
    TPointObject(type, parent)
{
    initPropertySheet();
    setRect(rect);
}

TRectObject::~TRectObject()
{

}

QSize TRectObject::size() const
{
    return mSizePropertyItem->value().toSize();
}

void TRectObject::setSize(const QSize &size)
{
    mSizePropertyItem->setValue(size);
}

QRectF TRectObject::getRect() const
{
    return QRectF(pos(), size());
}

void TRectObject::setRect(const QRectF &rect)
{
    setPos(rect.topLeft());
    setSize(rect.size().toSize());
}

void TRectObject::setRect(int x, int y, int w, int h)
{
    setRect(QRectF(x,y,w,h));
}

void TRectObject::initPropertySheet()
{
    mSizePropertyItem = mPropertySheet->addProperty(PT_SIZE, P_SIZE, PID_OBJECT_SIZE);
}

void TRectObject::saveToStream(QDataStream &) const
{

}

void TRectObject::readFromStream(QDataStream &)
{

}
