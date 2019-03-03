#ifndef KEYFRAMESCENE_H
#define KEYFRAMESCENE_H

#include <QMap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

#include "../../../../../base/property.h"

class TFrame;
class TArea;
class TShapeObject;
class TAnchorIndicator;
class TRotateHandle;
class TRotateHandlesManager;
class TResizeHandle;
class TResizeHandlesManager;
class TSelectionGraphicsItem;
class TOriginIndicator;
class TAreaGraphicsItem;
class TPropertySheet;
class TPropertyItem;

typedef QList<TArea*> TAreaList;

class TFrameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode {
        Normal,
        AddAttackArea,
        AddUndertakeArea,
        AddTerrianArea,
        AddCollideArea,
        AddFireObject,
        AddSound,
        AdjustAnchor,
        ModeCount
    };

    TFrameScene(TFrame *frame);
    ~TFrameScene();

    TFrame *keyFrame() const;
    void setMode(Mode mode);

    TAreaList getSelectedAreas() const;

    qreal getScale() const;
    void setScale(const qreal &scale);

    void setAreasVisible(int areaType, bool visible);

    Mode getMode() const;

signals:
    void requestDisplayPropertySheet(TPropertySheet *proertySheet);

private slots:
    void slotFrameBuddyChanged(TFrame *oldBuddy);
    void slotFramePropertyChanged(TPropertyItem *item, const QVariant &oldValue);
    void slotFrameBuddyPropertyChanged(TPropertyItem *item, const QVariant &value);
    void slotCollideAreasAdded(const TAreaList &areaList);
    void slotAttackAreasAdded(const TAreaList &areaList);
    void slotUndertakeAreasAdded(const TAreaList &areaList);
    void slotTerrianAreasAdded(const TAreaList &areaList);
    void slotAreasRemoved(const TAreaList &areaList);
    void slotAnchorMoved(const QPointF &newPos);

private:
    enum Action {
        NoAction,
        Selecting,
        Moving,
        Adding
    };

    TFrame *mFrame;
    QGraphicsPixmapItem *mPixmapItem;
    QGraphicsPixmapItem *mBuddyPixmapItem;
    QMap<TArea*, TAreaGraphicsItem*> mAreaItemList;
    QMap<TAreaGraphicsItem*, TArea*> mItemAreaList;
    TResizeHandlesManager *mResizeHandlesManager;
    TRotateHandlesManager *mRotateHandlesManager;
    TAnchorIndicator *mAnchorIndicator;
    QGraphicsItem *mCurrentClickedItem;

    bool mMousePressed;
    qreal mScale;
    Mode mMode;
    Action mAction;
    QPointF mMousePressedPos;
    QPointF mMouseCurrentPos;
    bool mIgnorePropertyChange;

    QSet<TAreaGraphicsItem*> mSelectedAreaItems;

    void addArea(TArea *area, const QColor &color);
    QList<TAreaGraphicsItem *> getSelectedAreaItems();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void drawForeground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // KEYFRAMESCENE_H
