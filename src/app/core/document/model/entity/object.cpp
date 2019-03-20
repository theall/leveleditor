#include "object.h"
#include "../../base/tr.h"

static const QString P_POS = T("Position");
static const QString P_SIZE = T("Size");

TObject::TObject(Type type, QObject *parent) :
    TPropertyObject(parent)
  , mType(type)
{

}

TObject::Type TObject::type() const
{
    return mType;
}

QPointF TObject::pos() const
{
    return mPos;
}

void TObject::setPos(const QPointF &pos)
{
    mPos = pos;
}

QSize TObject::size() const
{
    return mSize;
}

void TObject::setSize(const QSize &size)
{
    mSize = size;
}

QRectF TObject::rect() const
{
    return QRectF(mPos, mSize);
}

void TObject::move(const QPointF &offset)
{
    mPos += offset;
}

void TObject::initPropertySheet()
{
    mPropertySheet->addProperty(PT_VECTORF, P_POS, PID_OBJECT_POS);
    mPropertySheet->addProperty(PT_SIZE, P_POS, PID_OBJECT_SIZE);
}
