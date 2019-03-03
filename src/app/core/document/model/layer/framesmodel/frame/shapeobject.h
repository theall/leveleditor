#ifndef SHAPEOBJECT_H
#define SHAPEOBJECT_H

#include <QPolygonF>
#include <QSizeF>
#include <QString>
#include <QRectF>

#include "../../../../base/docobject.h"

class TShapeObject : public TDocObject
{
    Q_OBJECT

public:
    /**
     * Enumerates the different object shapes. Rectangle is the default shape.
     * When a polygon is set, the shape determines whether it should be
     * interpreted as a filled polygon or a line.
     */
    enum Shape {
        Rectangle,
        Polygon,
        Polyline,
        Ellipse
    };

    enum FlipDirection {
        FlipHorizontally,
        FlipVertically
    };

    enum RotateDirection {
        RotateLeft,
        RotateRight
    };

    enum Alignment {
        TopLeft,
        Top,
        TopRight,
        Left,
        Center,
        Right,
        BottomLeft,
        Bottom,
        BottomRight
    };

    TShapeObject(QObject *parent=nullptr);
    TShapeObject(const QRectF &rect, QObject *parent = nullptr);
    TShapeObject(qreal _x, qreal _y, qreal w, qreal h, QObject *parent);
    TShapeObject(const QString &name,
                 const QString &type,
                 const QPointF &pos,
                 const QSizeF &size,
                 QObject *parent=nullptr);

    /**
     * Returns the id of this object. Each object gets an id assigned that is
     * unique for the map the object is on.
     */
    int id() const;

    /**
     * Sets the id of this object.
     */
    void setId(int id);

    /**
     * Returns the name of this object. The name is usually just used for
     * identification of the object in the editor.
     */
    const QString &name() const;

    /**
     * Sets the name of this object.
     */
    void setName(const QString &name);

    /**
     * Returns the type of this object. The type usually says something about
     * how the object is meant to be interpreted by the engine.
     */
    const QString &type() const;

    /**
     * Sets the type of this object.
     */
    void setType(const QString &type);

    /**
     * Returns the position of this object.
     */
    QPointF position() const;

    /**
     * Sets the position of this object.
     */
    void setPosition(const QPointF &pos);
    void cmdSetPosition(const QPointF &pos);

    /**
     * Returns the x position of this object.
     */
    qreal x() const;

    /**
     * Sets the x position of this object.
     */
    void cmdSetX(qreal x);

    /**
     * Returns the y position of this object.
     */
    qreal y() const;

    /**
     * Sets the x position of this object.
     */
    void cmdSetY(qreal y);

    /**
     * Returns the size of this object.
     */
    QSizeF size() const;

    /**
     * Sets the size of this object.
     */
    void setSize(const QSizeF &size);
    void cmdSetSize(const QSizeF &size);
    void setSize(qreal width, qreal height);
    void cmdSetSize(qreal width, qreal height);

    /**
     * Returns the width of this object.
     */
    qreal width() const;

    /**
     * Sets the width of this object.
     */
    void cmdSetWidth(qreal width);

    /**
     * Returns the height of this object.
     */
    qreal height() const;

    /**
     * Sets the height of this object.
     */
    void cmdSetHeight(qreal height);

    /**
     * Sets the polygon associated with this object. The polygon is only used
     * when the object shape is set to either Polygon or Polyline.
     *
     * \sa setShape()
     */
    void setPolygon(const QPolygonF &polygon);

    /**
     * Returns the polygon associated with this object. Returns an empty
     * polygon when no polygon is associated with this object.
     */
    const QPolygonF &polygon() const;

    /**
     * Sets the shape of the object.
     */
    void setShape(Shape shape);

    /**
     * Returns the shape of the object.
     */
    Shape shape() const;

    /**
     * Shortcut to getting a QRectF from position() and size().
     */
    QRectF bounds() const;
    void setBounds(const QRectF &rect);

    /**
     * Returns the rotation of the object in degrees.
     */
    qreal rotation() const;

    /**
     * Sets the rotation of the object in degrees.
     */
    void setRotation(qreal rotation);

    Alignment alignment() const;

    bool isVisible() const;
    void setVisible(bool visible);

    /**
     * Flip this object in the given \a direction. This doesn't change the size
     * of the object.
     */
    void flip(FlipDirection direction);

    /**
     * Returns a duplicate of this object. The caller is responsible for the
     * ownership of this newly created object.
     */
    TShapeObject *clone() const;

signals:
    void propertyChanged(PropertyID id, const QVariant &value);

private slots:
    void slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &value);

private:
    int mId;
    QString mName;
    QString mType;
    QPolygonF mPolygon;
    Shape mShape;
    bool mVisible;

    void initPropertySheet(const QRectF &rect = QRectF());
};

#endif // SHAPEOBJECT_H
