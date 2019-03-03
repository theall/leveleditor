#include "areagraphicsitem.h"
#include "graphicsitemutil.h"

#include <QPen>
#include <QPolygonF>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

static QPolygonF pixelToScreenCoords(const QPolygonF &polygon)
{
    QPolygonF screenPolygon(polygon.size());
    for (int i = polygon.size() - 1; i >= 0; --i)
        screenPolygon[i] = polygon[i];
    return screenPolygon;
}

static QPolygonF lineToPolygon(const QPointF &start, const QPointF &end)
{
    QPointF direction = QVector2D(end - start).normalized().toPointF();
    QPointF perpendicular(-direction.y(), direction.x());

    const qreal thickness = 5.0f; // 5 pixels on each side
    direction *= thickness;
    perpendicular *= thickness;

    QPolygonF polygon(4);
    polygon[0] = start + perpendicular - direction;
    polygon[1] = start - perpendicular - direction;
    polygon[2] = end - perpendicular + direction;
    polygon[3] = end + perpendicular + direction;
    return polygon;
}

TAreaGraphicsItem::TAreaGraphicsItem(TArea *area, QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mArea(area)
  , mScale(1.0)
  , mMousePressed(false)
{
    Q_ASSERT(area);

    connect(area,
            SIGNAL(propertyChanged(PropertyID,QVariant)),
            this,
            SLOT(slotPropertyChanged(PropertyID,QVariant)));

    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIgnoresParentOpacity);

    setOpacity(0.8);
    setVisible(false);
}

TAreaGraphicsItem::~TAreaGraphicsItem()
{

}

QRectF TAreaGraphicsItem::boundingRect() const
{
    return mArea->bounds();
}

QPainterPath TAreaGraphicsItem::shape() const
{
    QPainterPath path;

    switch (mArea->shape()) {
        case TShapeObject::Rectangle: {
            const QRectF bounds = mArea->bounds();

            if (bounds.isNull()) {
                path.addEllipse(bounds.topLeft(), 20, 20);
            } else {
                path.addRoundedRect(bounds, 10, 10);
            }
            break;
        }
        case TShapeObject::Polygon:
        case TShapeObject::Polyline: {
            const QPointF &pos = mArea->position();
            const QPolygonF polygon = mArea->polygon().translated(pos);
            const QPolygonF screenPolygon = pixelToScreenCoords(polygon);
            if (mArea->shape() == TShapeObject::Polygon) {
                path.addPolygon(screenPolygon);
            } else {
                for (int i = 1; i < screenPolygon.size(); ++i) {
                    path.addPolygon(lineToPolygon(screenPolygon[i - 1],
                                                  screenPolygon[i]));
                }
                path.setFillRule(Qt::WindingFill);
            }
            break;
        }
        case TShapeObject::Ellipse: {
            const QRectF bounds = mArea->bounds();

            if (bounds.isNull()) {
                path.addEllipse(bounds.topLeft(), 20, 20);
            } else {
                path.addEllipse(bounds);
            }
            break;
        }
    }

    path.translate(-pos());
    return path;
}

void TAreaGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    const QRectF bounds = mArea->bounds();
    QRectF rect(bounds);

    painter->translate(rect.topLeft());
    rect.moveTopLeft(QPointF(0, 0));

    const qreal lineWidth = 1;
    QPen linePen(mColor, lineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    linePen.setCosmetic(true);

    painter->setRenderHint(QPainter::Antialiasing);

    // Trying to draw an ellipse with 0-width is causing a hang in
    // CoreGraphics when drawing the path requested by the
    // QCoreGraphicsPaintEngine. Draw them as rectangle instead.
    TShapeObject::Shape shape = mArea->shape();
    if (shape == TShapeObject::Ellipse &&
            ((rect.width() == qreal(0)) ^ (rect.height() == qreal(0)))) {
        shape = TShapeObject::Rectangle;
    }

    switch (shape) {
        case TShapeObject::Rectangle: {
            if (rect.isNull())
                rect = QRectF(QPointF(-10, -10), QSizeF(20, 20));

            painter->setPen(linePen);
            painter->drawRect(rect);
            break;
        }
        case TShapeObject::Polyline: {
            QPolygonF screenPolygon = pixelToScreenCoords(mArea->polygon());
            painter->setPen(linePen);
            painter->drawPolyline(screenPolygon);
            break;
        }
        case TShapeObject::Polygon: {
            QPolygonF screenPolygon = pixelToScreenCoords(mArea->polygon());
            painter->setPen(linePen);
            painter->drawPolygon(screenPolygon);
            break;
        }
        case TShapeObject::Ellipse: {
            if (rect.isNull())
                rect = QRectF(QPointF(-10, -10), QSizeF(20, 20));
            painter->setPen(linePen);
            painter->drawEllipse(rect);
            break;
        }
    }
    painter->restore();
}

void TAreaGraphicsItem::resize(const QSizeF &size)
{
    mArea->cmdSetSize(size);
}

void TAreaGraphicsItem::setPolygon(const QPolygonF &polygon)
{
    mArea->setPolygon(polygon);
}

TArea *TAreaGraphicsItem::area() const
{
    return mArea;
}

QColor TAreaGraphicsItem::color() const
{
    return mColor;
}

void TAreaGraphicsItem::setColor(const QColor &color)
{
    mColor = color;
}

void TAreaGraphicsItem::cmdSetRect(const QRectF &rect)
{
    if(!mArea)
        return;

    mArea->setBounds(rect);
}

TPropertySheet *TAreaGraphicsItem::propertySheet() const
{
    return mArea->propertySheet();
}

TArea::Type TAreaGraphicsItem::areaType() const
{
    return mArea->type();
}

void TAreaGraphicsItem::slotPropertyChanged(PropertyID id, const QVariant &value)
{
    Q_UNUSED(id);

    if(!mArea)
        return;

    QRectF newBounds = value.toRectF();
    emit areaChanged(newBounds);
    prepareGeometryChange();
}

int TAreaGraphicsItem::type() const
{
    return GIT_AREA;
}

QVariant TAreaGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsObject::itemChange(change, value);
}

void TAreaGraphicsItem::keyPressEvent(QKeyEvent *event)
{
    return QGraphicsObject::keyPressEvent(event);
}

void TAreaGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mLastPosition = mArea->position();
    mLastSize = mArea->size();
    mMousePressedPos = event->scenePos();
    mMousePressed = true;
}

void TAreaGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(mMousePressed)
    {
        const QPointF moveDistance = event->scenePos() - mMousePressedPos;
        if(mArea)
            mArea->cmdSetPosition(moveDistance + mLastPosition);
    }
}

void TAreaGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        mMousePressed = false;
}
