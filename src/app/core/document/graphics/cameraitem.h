#ifndef TCAMERAITEM_H
#define TCAMERAITEM_H

#include <QGraphicsObject>

class TCameraItem : public QGraphicsObject
{
    Q_OBJECT

public:
    TCameraItem(QGraphicsItem *parent = Q_NULLPTR);
    ~TCameraItem();

    QColor borderColor() const;
    void setBorderColor(const QColor &borderColor);
    void setBoundingRect(const QRectF &boundingRect);

private:
    QColor mBorderColor;
    QRectF mBoundingRect;
    QPixmap *mIcon;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // TCAMERAITEM_H
