#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QPair>
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsScene>

#include "sceneitem.h"
#include "uiitem/hovereditem.h"
#include "uiitem/selecteditems.h"
#include "uiitem/selectionrectangle.h"
#include "../model/scenemodel.h"
#include "layeritem/objectitem/objectitem.h"

class TDocument;
class TGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TGraphicsScene(QObject *parent = nullptr);
    ~TGraphicsScene();

    void setSize(qreal w, qreal h);
    void setSize(const QSizeF &size);
    void moveItem(QGraphicsItem *item, const QPointF &pos);
    void moveItem(QGraphicsItem *item, int x, int y);

    void setBackgroundColor(const QColor &color);

    qreal scale() const;
    void setScale(const qreal &scale);

    void play();
    bool isPlaying();
    void stop();

    int fps() const;
    void setFps(int fps);
    void setSceneModel(TSceneModel *sceneModel);

    void removeSelectedItems();

    TObject *getTopMostObject(const QPointF &pos) const;
    TObjectItem *getTopMostObjectItem(const QPointF &pos) const;
    TObjectItemList getObjectItemList(const QRectF &rect) const;
    TObjectItemList getObjectItemList(const QRectF &rect, TObject::Type objectType) const;
    TObjectItemList getObjectItemList(const QRectF &rect, TObjectItem *objectItem) const;

signals:
    void needChangeCursor(Qt::CursorShape cursor);
    void selectedObjectChanged(TObject *prev, TObject *current);

    // Send to document
    void requestUndo();
    void requestRedo();

private slots:
    void slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue);

private:
    enum Action {
        NoAction,
        Selecting,
        Moving,
        Resizing
    };

    int mFps;
    bool mStepMode;
    qreal mScale;
    int mTimerId;
    bool mLeftButtonDown;
    bool mUnderMouse;
    QPointF mLeftButtonDownPos;
    int mCommandId;
    Action mAction;
    Qt::CursorShape mCursor;
    TSceneModel *mSceneModel;
    TSceneItem *mSceneItem;
    THoveredItem *mHoveredItem;
    TSelectedItems *mSelectedItems;
    TSelectionRectangle *mSelectionRectangle;
    TObjectItem *mLastSelectedObjectItem;
    TDocument *mDocument;

    void step();
    void setSelectedObjectItem(TObjectItem *objectItem);
    void pushObjectMoveCommand(const TObjectList &objectList, const QPointF &offset, int commandId);


private slots:
    void updateCursor();

    // QGraphicsScene interface
protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void drawForeground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) Q_DECL_OVERRIDE;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QGraphicsSceneWheelEvent *event) Q_DECL_OVERRIDE;

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
};

#endif // GRAPHICSSCENE_H
