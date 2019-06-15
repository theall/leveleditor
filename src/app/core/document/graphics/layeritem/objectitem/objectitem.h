#ifndef TOBJECTITEM_H
#define TOBJECTITEM_H

#include <QList>
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>

#include "../../../model/entity/object.h"

class TObjectItem : public QGraphicsObject
{
    Q_OBJECT

public:
    enum { Type = UserType + 1 };
    TObjectItem(TObject *object, QGraphicsItem *parent = nullptr);
    ~TObjectItem();

    int type() const;

    TObject *object() const;
    TObject::Type objectType() const;
    bool isCongener(TObjectItem *objectItem) const;
    static TObjectItem *getObjectItem(TObject *object);

    virtual void propertyValueChanged(PropertyID pid) = 0;

    bool autonomy() const;
    void setAutonomy(bool autonomy);

    virtual void mousePressed(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoved(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleased(QGraphicsSceneMouseEvent *event);

    bool needGrabMouse() const;
    void setNeedGrabMouse(bool needGrabMouse);

    QColor borderColor() const;
    void setBorderColor(const QColor &borderColor);

    bool drawBorder() const;
    void setDrawBorder(bool drawBorder);

    void setBoundingRect(const QRectF &boundingRect);

signals:
    void boundingRectChanged(const QRectF &boundingRect);

private slots:
    void slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue);

protected:
    QRectF mBoundingRect;

private:
    TObject *mObject;
    bool mAutonomy;
    bool mNeedGrabMouse;
    bool mDrawBorder;
    QColor mBorderColor;
    static QMap<TObject*, TObjectItem*> mObjectItemMap;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

typedef QList<TObjectItem*> TObjectItemList;
#endif // TOBJECTITEM_H
