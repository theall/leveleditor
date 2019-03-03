#include "shapeobject.h"

static const char *P_X = "X";
static const char *P_Y = "Y";
static const char *P_RECT = "Rect";
static const char *P_WIDTH = "Width";
static const char *P_HEIGHT = "Height";
static const char *P_SIZE = "Size";
static const char *P_POSITION = "Position";
static const char *P_ROTATION = "Rotation";

TShapeObject::TShapeObject(QObject *parent) :
    TDocObject(parent)
  , mId(0)
  , mShape(Rectangle)
  , mVisible(true)
{
    initPropertySheet(QRectF(0, 0, 20, 20));
}

TShapeObject::TShapeObject(const QRectF &rect, QObject *parent) :
    TDocObject(parent)
  , mId(0)
  , mShape(Rectangle)
  , mVisible(true)
{
    initPropertySheet(rect);
}

TShapeObject::TShapeObject(qreal x, qreal y, qreal w, qreal h, QObject *parent) :
    TDocObject(parent)
  , mId(0)
  , mShape(Rectangle)
  , mVisible(true)
{
    initPropertySheet(QRectF(x,y,w,h));
}

TShapeObject::TShapeObject(const QString &name,
                          const QString &type,
                          const QPointF &pos,
                          const QSizeF &size,
                          QObject *parent) :
    TDocObject(parent)
  , mId(0)
  , mName(name)
  , mType(type)
  , mShape(Rectangle)
  , mVisible(true)
{
    initPropertySheet(QRectF(pos, size));
}

int TShapeObject::id() const
{
    return mId;
}

void TShapeObject::setId(int id)
{
    mId = id;
}

const QString &TShapeObject::name() const
{
    return mName;
}

void TShapeObject::setName(const QString &name)
{
    mName = name;
}

const QString &TShapeObject::type() const
{
    return mType;
}

void TShapeObject::setType(const QString &type)
{
    mType = type;
}

QPointF TShapeObject::position() const
{
    return (*mPropertySheet)[P_RECT]->value().toRectF().topLeft();
}

void TShapeObject::setPosition(const QPointF &pos)
{
    QRectF rect = (*mPropertySheet)[P_RECT]->value().toRectF();
    rect.moveTo(pos);
    (*mPropertySheet)[P_RECT]->setValue(rect);
}

void TShapeObject::cmdSetPosition(const QPointF &pos)
{
    QRectF rect = (*mPropertySheet)[P_RECT]->value().toRectF();
    rect.moveTo(pos);
    (*mPropertySheet)[P_RECT]->setNewValue(rect);
}

qreal TShapeObject::x() const
{
    return (*mPropertySheet)[P_RECT]->value().toRectF().x();
}

void TShapeObject::cmdSetX(qreal x)
{
    TPropertyItem *propertyItem = (*mPropertySheet)[P_RECT];
    if(propertyItem)
    {
        QRectF rect = propertyItem->value().toRectF();
        rect.setX(x);
        propertyItem->setNewValue(rect);
    }
}

qreal TShapeObject::y() const
{
    return (*mPropertySheet)[P_RECT]->value().toRectF().y();
}

void TShapeObject::cmdSetY(qreal y)
{
    TPropertyItem *propertyItem = (*mPropertySheet)[P_RECT];
    if(propertyItem)
    {
        QRectF rect = propertyItem->value().toRectF();
        rect.setY(y);
        propertyItem->setNewValue(rect);
    }
}

QSizeF TShapeObject::size() const
{
    QRectF rect = (*mPropertySheet)[P_RECT]->value().toRectF();
    return QSizeF(rect.width(), rect.height());
}

void TShapeObject::setSize(const QSizeF &size)
{
    QRectF rect = (*mPropertySheet)[P_RECT]->value().toRectF();
    rect.setWidth(size.width());
    rect.setHeight(size.height());
    (*mPropertySheet)[P_RECT]->setValue(rect);
}

void TShapeObject::cmdSetSize(const QSizeF &size)
{
    QRectF rect = (*mPropertySheet)[P_RECT]->value().toRectF();
    rect.setWidth(size.width());
    rect.setHeight(size.height());
    (*mPropertySheet)[P_RECT]->setNewValue(rect);
}

void TShapeObject::setSize(qreal width, qreal height)
{
    setSize(QSizeF(width, height));
}

void TShapeObject::cmdSetSize(qreal width, qreal height)

{
    cmdSetSize(QSizeF(width, height));
}

qreal TShapeObject::width() const
{
    return (*mPropertySheet)[P_RECT]->value().toRectF().width();
}

void TShapeObject::cmdSetWidth(qreal width)
{
    TPropertyItem *propertyItem = (*mPropertySheet)[P_RECT];
    if(propertyItem)
    {
        QRectF rect = propertyItem->value().toRectF();
        rect.setWidth(width);
        propertyItem->setNewValue(rect);
    }
}

qreal TShapeObject::height() const
{
    return (*mPropertySheet)[P_RECT]->value().toRectF().height();
}

void TShapeObject::cmdSetHeight(qreal height)
{
    TPropertyItem *propertyItem = (*mPropertySheet)[P_RECT];
    if(propertyItem)
    {
        QRectF rect = propertyItem->value().toRectF();
        rect.setHeight(height);
        propertyItem->setNewValue(rect);
    }
}

void TShapeObject::setPolygon(const QPolygonF &polygon)
{
    mPolygon = polygon;
}

const QPolygonF &TShapeObject::polygon() const
{
    return mPolygon;
}

void TShapeObject::setShape(TShapeObject::Shape shape)
{
    mShape = shape;
}

TShapeObject::Shape TShapeObject::shape() const
{
    return mShape;
}

QRectF TShapeObject::bounds() const
{
    return QRectF(position(), size());
}

void TShapeObject::setBounds(const QRectF &rect)
{
    (*mPropertySheet)[P_RECT]->setNewValue(rect);
}

qreal TShapeObject::rotation() const
{
    return (*mPropertySheet)[P_ROTATION]->value().toDouble();
}

void TShapeObject::setRotation(qreal rotation)
{
    (*mPropertySheet)[P_ROTATION]->setNewValue(rotation);
}

TShapeObject::Alignment TShapeObject::alignment() const
{
    return TopLeft;
}

bool TShapeObject::isVisible() const
{
    return mVisible;
}

void TShapeObject::setVisible(bool visible)
{
    mVisible = visible;
}

void TShapeObject::flip(FlipDirection direction)
{
    if (!mPolygon.isEmpty()) {
       const QPointF center2 = mPolygon.boundingRect().center() * 2;

       if (direction == FlipHorizontally) {
           for (int i = 0; i < mPolygon.size(); ++i)
               mPolygon[i].setX(center2.x() - mPolygon[i].x());
       } else if (direction == FlipVertically) {
           for (int i = 0; i < mPolygon.size(); ++i)
               mPolygon[i].setY(center2.y() - mPolygon[i].y());
       }
    }
}

TShapeObject *TShapeObject::clone() const
{
    TShapeObject *o = new TShapeObject(mName, mType, position(), size());
    o->setPolygon(mPolygon);
    o->setShape(mShape);
    o->setRotation(rotation());
    return o;
}

void TShapeObject::slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &value)
{
    if(!item)
       return;

    PropertyID propertyId = item->propertyId();
    emit propertyChanged(propertyId, value);
}

void TShapeObject::initPropertySheet(const QRectF &rect)
{
    connect(mPropertySheet,
           SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
           this,
           SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant)));

    mPropertySheet->addProperty(PT_RECT, P_RECT, PID_AREA_RESIZE, rect);

    if(mShape != Rectangle)
        mPropertySheet->addProperty(PT_DOUBLE, P_ROTATION, PID_BUCKLE_ROTATION, 0.0);
}
