#include "framescene.h"

#include "graphicsitem/rotatehandle.h"
#include "graphicsitem/resizehandle.h"
#include "graphicsitem/anchorindicator.h"
#include "graphicsitem/selectiongraphicsitem.h"
#include "graphicsitem/areagraphicsitem.h"
#include "graphicsitem/anchorindicator.h"

#include "../frame.h"

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

#define CONNECT_AREA_MANAGER(manager,func) \
    if(manager) \
    { \
        connect(manager, \
                SIGNAL(areasAdded(TAreaList)), \
                this, \
                SLOT(func(TAreaList)) \
                ); \
        connect(manager, \
                SIGNAL(areasRemoved(TAreaList)), \
                this, \
                SLOT(slotAreasRemoved(TAreaList)) \
                ); \
    }

TFrameScene::TFrameScene(TFrame *frame) :
    QGraphicsScene(frame)
  , mFrame(frame)
  , mPixmapItem(new QGraphicsPixmapItem)
  , mBuddyPixmapItem(new QGraphicsPixmapItem)
  , mResizeHandlesManager(new TResizeHandlesManager(this))
  , mAnchorIndicator(new TAnchorIndicator(mPixmapItem))
  , mCurrentClickedItem(nullptr)
  , mMousePressed(false)
  , mScale(1.0)
  , mMode(Normal)
  , mAction(NoAction)
  , mIgnorePropertyChange(false)
{
    Q_ASSERT(frame);

    connect(frame,
            SIGNAL(propertyChanged(TPropertyItem *, QVariant)),
            this,
            SLOT(slotFramePropertyChanged(TPropertyItem *,QVariant))
            );
    connect(frame,
            SIGNAL(frameBuddyChanged(TFrame*)),
            this,
            SLOT(slotFrameBuddyChanged(TFrame*))
            );
    connect(mAnchorIndicator, SIGNAL(itemMoved(QPointF)), this, SLOT(slotAnchorMoved(QPointF)));

    CONNECT_AREA_MANAGER(frame->collideAreaManager(), slotCollideAreasAdded);
    CONNECT_AREA_MANAGER(frame->attackAreaManager(), slotAttackAreasAdded);
    CONNECT_AREA_MANAGER(frame->undertakeAreaManager(), slotUndertakeAreasAdded);
    CONNECT_AREA_MANAGER(frame->terrianAreaManager(), slotTerrianAreasAdded);

    mBuddyPixmapItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    mBuddyPixmapItem->setFlag(QGraphicsItem::ItemIsMovable, false);
    mBuddyPixmapItem->setFlag(QGraphicsItem::ItemIsFocusable, false);
    mBuddyPixmapItem->setZValue(1);
    mBuddyPixmapItem->setOpacity(0.5);
    mBuddyPixmapItem->setVisible(false);
    mPixmapItem->setZValue(2);
    addItem(mBuddyPixmapItem);
    addItem(mPixmapItem);
}

TFrameScene::~TFrameScene()
{

}

TFrame *TFrameScene::keyFrame() const
{
    return mFrame;
}

void TFrameScene::slotFramePropertyChanged(TPropertyItem *item, const QVariant &oldValue)
{
    Q_UNUSED(oldValue);

    if(mIgnorePropertyChange || !item)
        return;

    PropertyID id = item->propertyId();
    if(id==PID_FRAME_IMAGE)
    {
        mPixmapItem->setPixmap(mFrame->pixmap()->pixmap());
    } else if(id==PID_FRAME_ANCHOR) {
        QPointF newPos = item->value().toPointF();
        if(newPos != mAnchorIndicator->pos())
        {
            mAnchorIndicator->blockSignals(true);
            mAnchorIndicator->setPos(newPos);
            mAnchorIndicator->blockSignals(false);
        }
        TFrame *buddyFrame = mFrame->prevBuddy();
        if(buddyFrame)
        {
            mBuddyPixmapItem->setPos(newPos-buddyFrame->anchor());
        }
    }
}

void TFrameScene::slotFrameBuddyPropertyChanged(TPropertyItem *item, const QVariant &oldValue)
{
    if(!mFrame || !item)
        return;

    PropertyID id = item->propertyId();
    if(id == PID_FRAME_ANCHOR) {
        TFrame *buddyFrame = mFrame->prevBuddy();
        if(buddyFrame)
            mFrame->moveAnchor(item->value().toPointF() - oldValue.toPointF());
    }
}

void TFrameScene::slotCollideAreasAdded(const TAreaList &areaList)
{
    for(TArea *area : areaList)
        addArea(area, QColor(255,128,255));
}

void TFrameScene::slotAttackAreasAdded(const TAreaList &areaList)
{
    for(TArea *area : areaList)
        addArea(area, Qt::red);
}

void TFrameScene::slotUndertakeAreasAdded(const TAreaList &areaList)
{
    for(TArea *area : areaList)
        addArea(area, Qt::blue);
}

void TFrameScene::slotTerrianAreasAdded(const TAreaList &areaList)
{
    for(TArea *area : areaList)
        addArea(area, Qt::green);
}

void TFrameScene::slotAreasRemoved(const TAreaList &areaList)
{
    for(TArea *area : areaList)
    {
        TAreaGraphicsItem *areaItem = mAreaItemList[area];
        if(mSelectedAreaItems.contains(areaItem))
            mSelectedAreaItems.remove(areaItem);
        areaItem->setParent(this);
        removeItem(areaItem);
        mAreaItemList.remove(area);
        mItemAreaList.remove(areaItem);
    }
    update();
}

void TFrameScene::slotAnchorMoved(const QPointF &newPos)
{
    if(!mFrame)
        return;

    TFrame *buddyFrame = mFrame->prevBuddy();
    if(buddyFrame)
    {
        mBuddyPixmapItem->setPos(newPos-buddyFrame->anchor());
    }

    mIgnorePropertyChange = true;
    mFrame->cmdSetAnchor(newPos);
    mIgnorePropertyChange = false;
}

TFrameScene::Mode TFrameScene::getMode() const
{
    return mMode;
}

qreal TFrameScene::getScale() const
{
    return mScale;
}

void TFrameScene::setScale(const qreal &scale)
{
    mScale = scale;
}

void TFrameScene::slotFrameBuddyChanged(TFrame *oldBuddy)
{
    if(oldBuddy)
        oldBuddy->disconnect(this);

    TFrame *newBuddy = mFrame->prevBuddy();
    if(newBuddy)
    {
        connect(newBuddy,
                SIGNAL(propertyChanged(TPropertyItem*,QVariant)),
                this,
                SLOT(slotFrameBuddyPropertyChanged(TPropertyItem*,QVariant)));

        TPixmap *pixmap = newBuddy->pixmap();
        if(pixmap)
            mBuddyPixmapItem->setPixmap(pixmap->pixmap());
        mBuddyPixmapItem->setPos(mFrame->anchor() - newBuddy->anchor());
    } else {
        mBuddyPixmapItem->setPixmap(QPixmap());
    }
}

void TFrameScene::setMode(TFrameScene::Mode mode)
{
    if(mode==ModeCount)
        throw(tr("Invalid frame scene mode."));

    if (mMode != mode) {
        setAreasVisible(TArea::Attack, mode==AddAttackArea);
        setAreasVisible(TArea::Undertake, mode==AddUndertakeArea);
        setAreasVisible(TArea::Terrain, mode==AddTerrianArea);
        setAreasVisible(TArea::Collide, mode==AddCollideArea);

        bool anchorMode = mode==AdjustAnchor;
        mAnchorIndicator->setVisible(anchorMode);
        if(mFrame->prevBuddy())
        {
            mBuddyPixmapItem->setVisible(anchorMode);
        }
        mMode = mode;
        mSelectedAreaItems.clear();
        mMousePressed = false;

        update();
    }
}

void TFrameScene::setAreasVisible(int areaType, bool visible)
{
    TArea::Type type = (TArea::Type)areaType;
    for(QGraphicsItem *item : items())
    {
        if(TAreaGraphicsItem *areaItem = dynamic_cast<TAreaGraphicsItem*>(item))
        {
            if(areaItem->areaType()==type)
                areaItem->setVisible(visible);
        }
    }
}

TAreaList TFrameScene::getSelectedAreas() const
{
    TAreaList areaList;
    for(QGraphicsItem *item : selectedItems())
    {
        if(TAreaGraphicsItem *areaItem = dynamic_cast<TAreaGraphicsItem*>(item))
            areaList.append(areaItem->area());
    }
    return areaList;
}

void TFrameScene::addArea(TArea *area, const QColor &color)
{
    if(!area || mAreaItemList.contains(area))
        return;

    TAreaGraphicsItem *areaItem = new TAreaGraphicsItem(area, mPixmapItem);
    areaItem->setColor(color);

    TArea::Type areaType = area->type();
    if((mMode==AddAttackArea && areaType==TArea::Attack)
            || (mMode==AddCollideArea && areaType==TArea::Collide)
            || (mMode==AddTerrianArea && areaType==TArea::Terrain)
            || (mMode==AddUndertakeArea && areaType==TArea::Undertake))
        areaItem->setVisible(true);

    mAreaItemList.insert(area, areaItem);
    mItemAreaList.insert(areaItem, area);
}

void TFrameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(painter);
    Q_UNUSED(rect);
}

void TFrameScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    painter->save();
    QPen pen(Qt::DotLine);
    pen.setColor(Qt::gray);
    painter->setPen(pen);
    for(TAreaGraphicsItem *areaItem : mSelectedAreaItems) {
        painter->drawRect(areaItem->boundingRect());
    }
    if(!mCurrentClickedItem && mMousePressed)
    {
        QRectF fakeRect = QRectF(mMousePressedPos, mMouseCurrentPos).normalized();
        painter->drawRect(fakeRect);
    }
    painter->restore();
}

void TFrameScene::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    int dx = 0;
    int dy = 0;
    TAreaList areaList;
    for(TAreaGraphicsItem *areaItem : mSelectedAreaItems)
        areaList.append(areaItem->area());
    bool hasSelectedAreas = areaList.size();

    if(key==Qt::Key_Escape) {
        mMousePressed = false;
    } else if(key==Qt::Key_Delete) {
        if(hasSelectedAreas)
            mFrame->cmdRemoveAreas(areaList);
    } else if(key==Qt::Key_Left) {
        dx--;
    } else if(key==Qt::Key_Right) {
        dx++;
    } else if(key==Qt::Key_Up) {
        dy--;
    } else if(key==Qt::Key_Down) {
        dy++;
    }
    if(hasSelectedAreas && dx!=0 && dy!=0)
        mFrame->cmdMoveAreas(areaList, QPointF((qreal)dx, (qreal)dy));

    update();
}

void TFrameScene::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void TFrameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        const QPointF scenePos = event->scenePos();
        Qt::KeyboardModifiers modifers = event->modifiers();
        bool controlPressed = modifers&Qt::ControlModifier;
        mCurrentClickedItem = itemAt(scenePos, QTransform());
        TAreaGraphicsItem *clickedAreaItem = dynamic_cast<TAreaGraphicsItem*>(mCurrentClickedItem);

        // Display clicked object's property sheet
        TPropertySheet *propertySheet = mFrame->propertySheet();
        if(mCurrentClickedItem && !clickedAreaItem)
            clickedAreaItem = dynamic_cast<TAreaGraphicsItem*>(mCurrentClickedItem->parentItem());
        if(clickedAreaItem)
            propertySheet = clickedAreaItem->propertySheet();
        emit requestDisplayPropertySheet(propertySheet);

        if(mMode==Normal)
        {
            return;
        } else if(mMode>Normal && mMode<AddFireObject) {
            // Update selected area items
            if(controlPressed)
            {
                if(clickedAreaItem)
                {
                    if(mSelectedAreaItems.contains(clickedAreaItem))
                        mSelectedAreaItems.remove(clickedAreaItem);
                    else
                        mSelectedAreaItems.insert(clickedAreaItem);
                }
            } else {
                mSelectedAreaItems.clear();
                if(clickedAreaItem)
                {
                    mSelectedAreaItems.insert(clickedAreaItem);
                }
            }

            if(mAction==NoAction)
            {
                if(controlPressed)
                {
                    mAction = Selecting;
                    mResizeHandlesManager->setParentItem(nullptr);
                } else {
                    mResizeHandlesManager->setParentItem(clickedAreaItem);
                    if(mCurrentClickedItem && mCurrentClickedItem->flags()&QGraphicsItem::ItemIsMovable)
                    {
                        QGraphicsScene::mousePressEvent(event);
                        return;
                    }
                }
            }
            mMousePressedPos = scenePos;
            mMouseCurrentPos = scenePos;
            mMousePressed = true;
            update();
        }  else if(mMode==AdjustAnchor) {
            if(mCurrentClickedItem==mAnchorIndicator) {
                // Pass event to clicked item
                QGraphicsScene::mousePressEvent(event);
            }
        } else {

        }
    }
}

void TFrameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    if(mMousePressed) {
        mMouseCurrentPos = event->scenePos();
        update();
    }
}

void TFrameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    mMouseCurrentPos = event->scenePos();
    if (mMousePressed)
    {
        QRectF selectingRectF = QRectF(mMousePressedPos, mMouseCurrentPos).normalized();
        if(mMode==Normal) {
            Qt::KeyboardModifiers modifers = event->modifiers();
            if(!(modifers&Qt::ControlModifier) && !(modifers&Qt::ShiftModifier)) {
                mSelectedAreaItems.clear();
            }
            for(QGraphicsItem *item : items(selectingRectF)) {
                if(TAreaGraphicsItem *areaItem = dynamic_cast<TAreaGraphicsItem*>(item))
                    mSelectedAreaItems.insert(areaItem);
            }
        } else if(mMode>Normal && mMode<AddFireObject) {
            if(!mCurrentClickedItem && mMouseCurrentPos!=mMousePressedPos)
            {
                TArea::Type areaType;
                switch (mMode) {
                case AddAttackArea:
                    areaType = TArea::Attack;
                    break;
                case AddUndertakeArea:
                    areaType = TArea::Undertake;
                    break;
                case AddCollideArea:
                    areaType = TArea::Collide;
                    break;
                case AddTerrianArea:
                    areaType = TArea::Terrain;
                    break;
                default:
                    break;
                }

                mFrame->cmdAddArea(selectingRectF, areaType);
            }
        }
    }
    mMousePressed = false;
    mAction = NoAction;
    update();
}

QList<TAreaGraphicsItem *> TFrameScene::getSelectedAreaItems()
{
    return mSelectedAreaItems.toList();
}
