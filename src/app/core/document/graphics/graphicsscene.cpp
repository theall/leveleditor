#include "graphicsscene.h"

#include <QDebug>
#include <QCursor>
#include <QPainter>
#include <QWheelEvent>
#include <QCoreApplication>
#include <QGraphicsSceneMouseEvent>

#include "../base/finddoc.h"
#include "../document.h"
#include "../model/scenemodel.h"
#include "../model/entity/area.h"
#include "../model/entity/box.h"
#include "../model/entity/darea.h"
#include "../model/entity/plat.h"
#include "../model/entity/wall.h"

#include "../undocommand/objectaddcommand.h"
#include "../undocommand/objectmovecommand.h"
#include "../undocommand/removeselectioncommand.h"
#include "../undocommand/rectresizeundocommand.h"

#include "sceneitem.h"
#include "base/stamp.h"
#include "uiitem/resizeitem.h"
#include "uiitem/hovereditem.h"
#include "uiitem/tilestampitem.h"
#include "uiitem/selecteditems.h"
#include "uiitem/objectareaitem.h"
#include "uiitem/selectionrectangle.h"

#define TOP_Z_VALUE 10000
#define ADJUST_SIZE 100

inline float squareOfRect(const QRectF &rect) {
    return rect.width() * rect.height();
}

bool objectRectCompare(TObjectItem *i1, TObjectItem *i2) {
    return squareOfRect(i1->boundingRect()) < squareOfRect(i2->boundingRect());
}

TGraphicsScene::TGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
  , mFps(60)
  , mStepMode(false)
  , mTimerId(-1)
  , mLeftButtonDown(false)
  , mUnderMouse(false)
  , mAction(NoAction)
  , mCursor(Qt::ArrowCursor)
  , mSceneModel(nullptr)
  , mSceneItem(nullptr)
  , mUiItemsGroup(new QGraphicsRectItem)
  , mHoveredItem(new THoveredItem(mUiItemsGroup))
  , mTileStampItem(new TTileStampItem(mUiItemsGroup))
  , mSelectedItems(new TSelectedItems(mUiItemsGroup))
  , mObjectAreaItem(new TObjectAreaItem(mUiItemsGroup))
  , mSelectionRectangle(new TSelectionRectangle(mUiItemsGroup))
  , mLastSelectedObjectItem(nullptr)
  , mDocument(nullptr)
  , mStamp(new TStamp)
  , mEditMode(DEFAULT)
{
    mUiItemsGroup->setZValue(TOP_Z_VALUE);
    addItem(mUiItemsGroup);

    FIND_DOCUMENT;
}

TGraphicsScene::~TGraphicsScene()
{
    delete mUiItemsGroup;
}

void TGraphicsScene::setSize(qreal w, qreal h)
{
    setSceneRect(QRectF(0.0, 0.0, w, h));
    update();
}

void TGraphicsScene::setSize(const QSizeF &size)
{
    setSize(size.width(), size.height());
}

void TGraphicsScene::moveItem(QGraphicsItem *item, const QPointF &pos)
{
    moveItem(item, pos.x(), pos.y());
}

void TGraphicsScene::moveItem(QGraphicsItem *item, int x, int y)
{
    if(item)
    {
        item->setPos(x, y);
        item->setToolTip(QString("%1 %2").arg(x).arg(y));
    }
}

void TGraphicsScene::setBackgroundColor(const QColor &color)
{
    setBackgroundBrush(QBrush(color));
}

bool TGraphicsScene::play()
{
    if(mTimerId != -1){
        killTimer(mTimerId);
        return true;
    }

    mStepMode = false;
    mTimerId = startTimer(1000.0/mFps);
    return false;
}

bool TGraphicsScene::suspend()
{
    if(mTimerId != -1)
    {
        killTimer(mTimerId);
        mTimerId = -1;
        return true;
    }
    return false;
}

bool TGraphicsScene::isPlaying()
{
    return mTimerId != -1;
}

bool TGraphicsScene::stop()
{
    if(mTimerId != -1)
    {
        killTimer(mTimerId);
        mTimerId = -1;
    }
    return false;
}

int TGraphicsScene::fps() const
{
    return mFps;
}

void TGraphicsScene::setFps(int fps)
{
    if(mFps==fps)
        return;

    mFps = fps;

    if(isPlaying()) {
        stop();
        play();
    }
}

void TGraphicsScene::setSceneModel(TSceneModel *sceneModel)
{
    if(mSceneModel == sceneModel)
        return;

    if(mSceneModel) {
        mSceneModel->disconnect(this);
        mSceneItem->disconnect(this);
        removeItem((QGraphicsItem*)mSceneItem);
    }

    mSceneModel = sceneModel;

    if(mSceneModel) {
        mSceneItem = new TSceneItem(sceneModel);
        connect(mSceneItem, SIGNAL(boundingRectChanged(QRectF)), this, SLOT(slotOnSceneItemBoundingRectChanged(QRectF)));
        addItem((QGraphicsItem*)mSceneItem);

        connect(mSceneModel,
                SIGNAL(currentIndexChanged(int)),
                this,
                SLOT(slotOnSceneModelCurrentIndexChanged(int)));
        connect(mSceneModel->propertySheet(),
                SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
                this,
                SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant)));
        setBackgroundColor(mSceneModel->getBackgroundColor());
        QRectF rect = mSceneItem->boundingRect();
        setSceneRect(rect);
    }
}

TObjectItemList TGraphicsScene::getSelectedObjectItemList() const
{
    return mSelectedItems->getSelectedObjectItemList();
}

void TGraphicsScene::selectObjectItemList(const TObjectItemList &objectItemList)
{
    mSelectedItems->setObjectItemList(objectItemList);
}

void TGraphicsScene::selectObjectItem(TObjectItem *objectItem)
{
    mSelectedItems->setObjectItem(objectItem);
}

void TGraphicsScene::removeSelectedItems()
{
    TObjectList objectList = mSelectedItems->getSelectedObjectList();
    if(objectList.isEmpty())
        return;

    TBaseModel *currentModel = mSceneModel->getCurrentModel();
    if(currentModel) {
        TRemoveSelectionCommand *command = new TRemoveSelectionCommand(
            currentModel,
            mSceneItem->getCurrentLayerItem(),
            mSelectedItems
        );
        mDocument->addUndoCommand(command);
    }
}

qreal TGraphicsScene::scale() const
{
    return mScale;
}

void TGraphicsScene::setScale(const qreal &scale)
{
    mScale = scale;
}

void TGraphicsScene::step()
{
    mSceneItem->step();

    QRectF r = sceneRect();
    update(r);
}

void TGraphicsScene::setSelectedObjectItem(TObjectItem *objectItem)
{
    if(mLastSelectedObjectItem == objectItem)
        return;

    TObjectItem *prevObjectItem = mLastSelectedObjectItem;
    mLastSelectedObjectItem = objectItem;

    TObject *prevObject, *currentObject;
    prevObject = prevObjectItem?prevObjectItem->object():nullptr;
    currentObject = objectItem?objectItem->object():nullptr;
    emit selectedObjectChanged(prevObject, currentObject);
}

QList<QGraphicsItem*> TGraphicsScene::itemsOfCurrentLayerItem(
        const QPointF &pos,
        Qt::ItemSelectionMode mode) const
{
    QList<QGraphicsItem*> itemList;
    TLayerItem *currentLayerItem = mSceneItem->getCurrentLayerItem();
    if(currentLayerItem) {
        itemList = items(pos, mode);
        QSet<QGraphicsItem*> itemSet = QSet<QGraphicsItem*>::fromList(itemList);
        QList<QGraphicsItem*> childItemList = currentLayerItem->childItems();
        QSet<QGraphicsItem*> childItemSet = QSet<QGraphicsItem*>::fromList(childItemList);
        itemList = itemSet.intersect(childItemSet).toList();
    }
    return itemList;
}

QList<QGraphicsItem *> TGraphicsScene::itemsOfCurrentLayerItem(
        const QRectF &rect,
        Qt::ItemSelectionMode mode) const
{
    QList<QGraphicsItem*> itemList;
    TLayerItem *currentLayerItem = mSceneItem->getCurrentLayerItem();
    if(currentLayerItem) {
        itemList = items(rect, mode);
        QSet<QGraphicsItem*> itemSet = QSet<QGraphicsItem*>::fromList(itemList);
        QSet<QGraphicsItem*> childItemSet = QSet<QGraphicsItem*>::fromList(currentLayerItem->childItems());
        itemList = itemSet.intersect(childItemSet).toList();
    }
    return itemList;
}

void TGraphicsScene::updateUiItems()
{
    if(!mSceneModel)
        return;

    bool isDefaultMode = mEditMode==DEFAULT;
    bool isInsertMode = mEditMode==INSERT;
    TBaseModel::Type modelType = mSceneModel->getCurretnModelType();
    bool isInsertTileMode = isInsertMode && modelType==TBaseModel::TILE;
    bool isInsertEnemyMode = isInsertMode && modelType==TBaseModel::ENEMY_FACTORY;
    bool tileStampNeedShow = mUnderMouse && (isInsertTileMode|isInsertEnemyMode);
    if(tileStampNeedShow)
        mTileStampItem->setCenterPos(mMouseMovingPos);
    mTileStampItem->setVisible(tileStampNeedShow);

    mHoveredItem->setVisible(mUnderMouse && isDefaultMode);
    mSelectedItems->setVisible(isDefaultMode);
    mSelectionRectangle->setVisible(false);
    mObjectAreaItem->setVisible(false);
}

void TGraphicsScene::pushObjectMoveCommand(const TObjectList &objectList, const QPointF &offset)
{
    TObjectMoveUndoCommand *command = new TObjectMoveUndoCommand(
                objectList,
                offset,
                mCommandId);
    mDocument->addUndoCommand(command);
}

void TGraphicsScene::pushRectResizingCommand(const TRectObjectList &rectObjectList, const QMarginsF &margins)
{
    TRectResizeUndoCommand *command = new TRectResizeUndoCommand(
                rectObjectList,
                margins,
                mCommandId);
    mDocument->addUndoCommand(command);
}

void TGraphicsScene::updateCursor()
{
    Qt::CursorShape cursorShape = Qt::ArrowCursor;

    switch (mAction) {
    case NoAction:
    {
        if(mHoveredItem->isVisible())
            cursorShape = Qt::SizeAllCursor;
        break;
    }
    case Moving:
        cursorShape = Qt::SizeAllCursor;
        break;
    default:
        break;
    }

    if(mCursor != cursorShape)
    {
        emit needChangeCursor(cursorShape);
        mCursor = cursorShape;
    }
}

bool TGraphicsScene::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::Enter:
        mUnderMouse = true;
        updateUiItems();
        break;
    case QEvent::Leave:
        mUnderMouse = false;
        updateUiItems();
        break;
    default:
        break;
    }

    return QGraphicsScene::event(event);
}

void TGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);
}

void TGraphicsScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawForeground(painter, rect);
}

void TGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    Qt::MouseButton button = event->button();
    mLeftButtonDown = (button==Qt::LeftButton);
    if(!mLeftButtonDown)
        return;

    QPointF mousePos = event->scenePos();
    mLeftButtonDownPos = mousePos;
    mCommandId = qAbs(((int)mLeftButtonDownPos.x())<<16) + qAbs(mLeftButtonDownPos.y());

    if(mEditMode == DEFAULT) {
        THandleItem *handleItem = dynamic_cast<THandleItem*>(itemAt(mousePos, QTransform()));
        // Check resize handle
        if(handleItem) {
            mAction = Resizing;
            mResizeHandle = handleItem;
            return;
        }

        TObjectItem *autonomyObjectitem = nullptr;
        TObjectItem *objectItem = getTopMostObjectItem(mousePos);
        if(mLastSelectedObjectItem && mLastSelectedObjectItem->needGrabMouse()) {
            autonomyObjectitem = mLastSelectedObjectItem;
        }
        if(!autonomyObjectitem) {
            if(objectItem && objectItem->autonomy())
                autonomyObjectitem = objectItem;
        }
        if(autonomyObjectitem)
        {
            autonomyObjectitem->mousePressed(event);
            setSelectedObjectItem(autonomyObjectitem);
            if(event->isAccepted())
                return;
        }

        if(mLeftButtonDown) {
            Qt::KeyboardModifiers modifers = event->modifiers();
            if(modifers & Qt::ShiftModifier) {
                TObjectItem *objectItem = getTopMostObjectItem(mousePos);
                if(mLastSelectedObjectItem && mLastSelectedObjectItem->isCongener(objectItem)) {
                    qreal leftButtonDownX = mousePos.x();
                    qreal leftButtonDownY = mousePos.y();
                    QRectF lastObjectItemRect = mLastSelectedObjectItem->boundingRect();
                    QPointF centerPos = lastObjectItemRect.center();
                    qreal left = qMin(leftButtonDownX, centerPos.x());
                    qreal top = qMin(leftButtonDownY, centerPos.y());
                    qreal right = qMax(leftButtonDownX, centerPos.x());
                    qreal bottom = qMax(leftButtonDownY, centerPos.y());
                    TObjectItemList objectItemList = getObjectItemList(QRectF(left,top,right-left,bottom-top), mLastSelectedObjectItem);
                    if(objectItemList.size() > 0)
                        mSelectedItems->setObjectItemList(objectItemList);
                }
            }
        }
    } else if(mEditMode == INSERT) {
        if(mLeftButtonDown) {
            TBaseModel::Type currentModelType = mSceneModel->getCurretnModelType();
            if(currentModelType == TBaseModel::TILE) {
                TTileModel *tileLayerModel = mSceneModel->getCurrentAsTileLayerModel();
                TTile *tile = tileLayerModel->createTile(mStamp->getTileId(), mTileStampItem->pos());
                TObjectList objectList;
                objectList.append(tile);
                TObjectAddCommand *command = new TObjectAddCommand(
                    TObjectAddCommand::ADD,
                    tileLayerModel,
                    objectList
                );
                mDocument->addUndoCommand(command);
            } else if(currentModelType == TBaseModel::ENEMY_FACTORY) {

            } else {
                mObjectAreaItem->setRectangle(QRectF(mousePos, QSizeF()));
                mObjectAreaItem->setVisible(true);
            }
        }
    }
}

void TGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    mMouseMovingPos = event->scenePos();

    if(mEditMode == DEFAULT) {
        TObjectItem *autonomyObjectitem = nullptr;
        TObjectItem *objectItem = getTopMostObjectItem(mMouseMovingPos);
        if(mLastSelectedObjectItem && mLastSelectedObjectItem->needGrabMouse()) {
            autonomyObjectitem = mLastSelectedObjectItem;
        }
        if(!autonomyObjectitem) {
            if(objectItem && objectItem->autonomy())
                autonomyObjectitem = objectItem;
        }
        if(autonomyObjectitem)
        {
            autonomyObjectitem->mouseMoved(event);
            if(event->isAccepted())
                return;
        }

        if(!mLeftButtonDown) {
            if(mSelectedItems->containsObjectItem(objectItem))
                mHoveredItem->setObjectItem(nullptr);
            else
                mHoveredItem->setObjectItem(objectItem);
            mAction = NoAction;
        } else {
            // Check whether needing moving or selecting
            if(mAction == NoAction) {
                if(objectItem) {
                    QPointF lastScenePos = event->lastScenePos();
                    // Check whether need to add object item under mouse to selected items
                    if(lastScenePos == mLeftButtonDownPos) {
                        mAction = Moving;
                        if(!mSelectedItems->containsObjectItem(objectItem)) {
                            mSelectedItems->setObjectItem(objectItem);
                        }
                    }
                } else {
                    mAction = Selecting;
                    mSelectionRectangle->setVisible(true);
                }
            }

            // Run once after action set
            if(mAction == Moving) {
                mHoveredItem->setObjectItem(nullptr);
                // Move selected object item
                QPointF offset = mMouseMovingPos - event->lastScenePos();
                if(!offset.isNull()) {
                    mSelectedItems->move(offset);
                }
            } else if(mAction == Selecting) {
                mSelectionRectangle->setRectangle(QRectF(mLeftButtonDownPos, mMouseMovingPos));
            } else if(mAction == Resizing) {
                mResizeHandle->move(mMouseMovingPos - event->lastScenePos());
            }
        }
        updateCursor();
        update();
    } else if(mEditMode == INSERT) {
        TBaseModel::Type currentModelType = mSceneModel->getCurretnModelType();
        if(currentModelType==TBaseModel::TILE
                || currentModelType==TBaseModel::ENEMY_FACTORY) {
            mTileStampItem->setCenterPos(mMouseMovingPos);
        } else {
            mObjectAreaItem->setRectangle(QRectF(mLeftButtonDownPos, mMouseMovingPos));
        }
    }
}

void TGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);

    if(mEditMode == DEFAULT) {
        TObjectItem *autonomyObjectitem = nullptr;
        QPointF mouseScenePos = event->scenePos();
        TObjectItem *objectItem = getTopMostObjectItem(mouseScenePos);
        if(mLastSelectedObjectItem && mLastSelectedObjectItem->needGrabMouse()) {
            autonomyObjectitem = mLastSelectedObjectItem;
        }
        if(!autonomyObjectitem) {
            if(objectItem && objectItem->autonomy())
                autonomyObjectitem = objectItem;
        }
        if(autonomyObjectitem)
        {
            autonomyObjectitem->mouseReleased(event);
            if(event->isAccepted())
                return;
        }

        if(mLeftButtonDown) {
            mLeftButtonDown = false;
            if(mAction == NoAction) {
                TObjectItem *objectItem = getTopMostObjectItem(mouseScenePos);
                if(objectItem) {
                    Qt::KeyboardModifiers modifers = event->modifiers();
                    if(modifers&Qt::ControlModifier) {
                        if(mLeftButtonDownPos==mouseScenePos) {
                            // The mouse pos is not equal to mLeftButtonDownPos after selected items moved
                            if(!mSelectedItems->containsObjectItem(objectItem)) {
                                mSelectedItems->addObjectItem(objectItem);
                                setSelectedObjectItem(objectItem);
                            } else {
                                mSelectedItems->removeObjectItem(objectItem);
                                TObjectItem *lastSelectedObjectItem = mLastSelectedObjectItem;
                                mLastSelectedObjectItem = nullptr;
                                setSelectedObjectItem(lastSelectedObjectItem);
                            }
                        }
                    } else if(modifers&Qt::ShiftModifier) {
                        if(!mLastSelectedObjectItem)
                            setSelectedObjectItem(objectItem);
                    } else {
                        mSelectedItems->setObjectItem(objectItem);
                        setSelectedObjectItem(objectItem);
                    }
                } else {
                    mSelectedItems->setObjectItem(nullptr);
                    setSelectedObjectItem(nullptr);
                }
            } else if(mAction == Selecting) {
                mAction = NoAction;

                QRectF selectionRect = mSelectionRectangle->boundingRect();
                TObjectItemList objectItemList = getObjectItemList(selectionRect);
                Qt::KeyboardModifiers modifers = event->modifiers();
                if(modifers&Qt::ControlModifier) {
                    mSelectedItems->addObjectItems(objectItemList);
                } else {
                    mSelectedItems->setObjectItemList(objectItemList);
                }
                mSelectionRectangle->setVisible(false);
                if(!mSelectedItems->isVisible())
                    mSelectedItems->setVisible(true);
            } else if(mAction == Moving) {
                mAction = NoAction;
                QPointF offset = event->scenePos() - mLeftButtonDownPos;
                if(!offset.isNull()) {
                    TObjectList objectList = mSelectedItems->getSelectedObjectList();
                    if(!objectList.isEmpty())
                        pushObjectMoveCommand(objectList, offset);
                }

            } else if(mAction == Resizing) {
                mAction = NoAction;
                QPointF offset = event->scenePos() - mLeftButtonDownPos;
                if(!offset.isNull()) {
                    //TRectObjectList rectObjectList = mSelectedItems->getSelectedRectObjectList();
                    //if(!rectObjectList.isEmpty())
                    //    pushRectResizingCommand(rectObjectList, offset);
                }
            }

            update();
        }
    } else if(mEditMode == INSERT) {
        TBaseModel *baseModel = mSceneModel->getCurrentModel();
        TBaseModel::Type modelType = baseModel->type();
        TObject *newObject = nullptr;
        QRect areaRect = mObjectAreaItem->boundingRect().toRect();
        switch(modelType) {
        case TBaseModel::AREA:
            newObject = new TArea(areaRect, baseModel);
            break;
        case TBaseModel::DAREA:
            newObject = new TDArea(areaRect, baseModel);
            break;
        case TBaseModel::PLAT:
            newObject = new TPlat(areaRect, baseModel);
            break;
        case TBaseModel::WALL:
            newObject = new TWall(areaRect, baseModel);
            break;
        case TBaseModel::BOX:
            newObject = new TBox(areaRect, baseModel);
            break;
        case TBaseModel::EVENT:
        case TBaseModel::TRIGGER:
        case TBaseModel::RESPAWN:
        case TBaseModel::ANIMATION:
        case TBaseModel::FRAME:
        case TBaseModel::SCENE:
        case TBaseModel::TILE:
        case TBaseModel::INVALID:
        default:
            break;
        }
        if(newObject) {
            TObjectList objectList;
            objectList.append(newObject);
            TObjectAddCommand *command = new TObjectAddCommand(
                TObjectAddCommand::ADD,
                baseModel,
                objectList
            );
            mDocument->addUndoCommand(command);
        }
        mObjectAreaItem->setVisible(false);
    }
}

void TGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void TGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    Qt::KeyboardModifiers keyboardModifiers = event->modifiers();

    if(mEditMode == DEFAULT) {
        if(key == Qt::Key_Space)
        {
            if(!mStepMode) {
                mStepMode = true;
                if(isPlaying())
                    stop();
            } else {
                step();
            }
        } else if(key>=Qt::Key_Left && key<=Qt::Key_Down) {
            TObjectList objectList = mSelectedItems->getSelectedObjectList();
            if(objectList.size() > 0) {
                QPointF offset;
                if(key == Qt::Key_Left) {
                    offset.setX(-1);
                } else if(key == Qt::Key_Up) {
                    offset.setY(-1);
                } else if(key == Qt::Key_Right) {
                    offset.setX(1);
                } else if(key == Qt::Key_Down) {
                    offset.setY(1);
                }
                pushObjectMoveCommand(objectList, offset);
            }
        } else if(key==Qt::Key_Delete) {
            removeSelectedItems();
        } else if(key==Qt::Key_Z && (keyboardModifiers&Qt::ControlModifier)) {
            emit requestUndo();
        } else if(key==Qt::Key_Y && (keyboardModifiers&Qt::ControlModifier)) {
            emit requestRedo();
        } else if(key==Qt::Key_Escape) {
            mSelectedItems->setObjectItem(nullptr);
            update();
        }
    } else if(mEditMode == INSERT) {
        if(key == Qt::Key_Escape) {
            // Call document to emit editModelChanged signal
            mDocument->setEditMode(DEFAULT);
        }
    }

    QGraphicsScene::keyPressEvent(event);
}

void TGraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsScene::keyReleaseEvent(event);
}

void TGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsScene::contextMenuEvent(event);
}

void TGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dragEnterEvent(event);
}

void TGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dragMoveEvent(event);
}

void TGraphicsScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dragLeaveEvent(event);
}

void TGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dropEvent(event);
}

void TGraphicsScene::focusInEvent(QFocusEvent *event)
{
    QGraphicsScene::focusInEvent(event);
}

void TGraphicsScene::focusOutEvent(QFocusEvent *event)
{
    QGraphicsScene::focusOutEvent(event);
}

void TGraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    QGraphicsScene::wheelEvent(event);
}

void TGraphicsScene::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    step();
}

void TGraphicsScene::slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue)
{
    Q_UNUSED(oldValue);

    if(!item)
        return;

    PropertyID pid = item->propertyId();
    if(pid==PID_SCENE_BACKGROUND_COLOR) {
        setBackgroundColor(item->value().value<QColor>());
    }
}

void TGraphicsScene::slotOnSceneItemBoundingRectChanged(const QRectF &rect)
{
    QRectF r = rect.adjusted(-ADJUST_SIZE, -ADJUST_SIZE, ADJUST_SIZE, ADJUST_SIZE);
    setSceneRect(r);
}

void TGraphicsScene::setEditMode(int editMode)
{
    if(mEditMode == editMode)
        return;

    mEditMode = editMode;
    mLeftButtonDown = false;
    updateUiItems();
}

void TGraphicsScene::showSelectedItemsBorder(bool visible)
{
    mSelectedItems->setVisible(visible);
}

void TGraphicsScene::setSceneRect(const QRectF &rect)
{
    QGraphicsScene::setSceneRect(rect);
}

QImage TGraphicsScene::toImage(const QSize &size)
{
    QSizeF imageSize(sceneRect().size());
    QImage image(imageSize.width(), imageSize.height(), QImage::Format_ARGB32);
    //get thumbnail
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    render(&painter);
    if(!size.isEmpty()) {
        return image.scaled(size);
    }
    return image;
}

void TGraphicsScene::slotOnSceneModelCurrentIndexChanged(int)
{
    if(mSceneModel->getCurrentModel()) {
        mSelectedItems->clear();
    }
}

TObjectItem *TGraphicsScene::getLastSelectedObjectItem() const
{
    return mLastSelectedObjectItem;
}

TLayerItem *TGraphicsScene::getLayerItem(int index) const
{
    return mSceneItem->getLayerItem(index);
}

TLayerItemList TGraphicsScene::getLayerItemList() const
{
    return mSceneItem->getLayerItemList();
}

void TGraphicsScene::setCurrentStamp(TPixmapId *pixmapId)
{
    mStamp->setPixmapId(pixmapId);
    mTileStampItem->setPixmap(mStamp->pixmap());
}

TObject *TGraphicsScene::getTopMostObject(const QPointF &pos) const
{
    TObjectItem *objectItem = getTopMostObjectItem(pos);
    if (objectItem)
        return objectItem->object();
    return nullptr;
}

TObjectItem *TGraphicsScene::getTopMostObjectItem(const QPointF &pos) const
{
    QList<QGraphicsItem*> itemList = itemsOfCurrentLayerItem(pos, Qt::IntersectsItemBoundingRect);
    TObjectItemList objectItemList;
    for (QGraphicsItem *item : itemList) {
        if (!item->isEnabled())
            continue;

        TObjectItem *objectItem = qgraphicsitem_cast<TObjectItem*>(item);
        if (objectItem) {
            objectItemList.append(objectItem);
        }
    }

    if(objectItemList.isEmpty())
        return nullptr;

    // Find minimized rect
    qSort(objectItemList.begin(), objectItemList.end(), objectRectCompare);
    return objectItemList.first();
}

TObjectItemList TGraphicsScene::getObjectItemList(const QRectF &rect) const
{
    QList<QGraphicsItem*> itemList = itemsOfCurrentLayerItem(rect, Qt::IntersectsItemBoundingRect);
    TObjectItemList objectItemList;
    for (QGraphicsItem *item : itemList) {
        if (!item->isEnabled())
            continue;

        TObjectItem *objectItem = qgraphicsitem_cast<TObjectItem*>(item);
        if (objectItem)
            objectItemList.append(objectItem);
    }
    return objectItemList;
}

TObjectItemList TGraphicsScene::getObjectItemList(const QRectF &rect, TObject::Type objectType) const
{
    QList<QGraphicsItem*> itemList = itemsOfCurrentLayerItem(rect, Qt::IntersectsItemBoundingRect);
    TObjectItemList objectItemList;
    for (QGraphicsItem *item : itemList) {
        if (!item->isEnabled())
            continue;

        TObjectItem *objectItem = qgraphicsitem_cast<TObjectItem*>(item);
        if (objectItem && objectItem->objectType()==objectType)
            objectItemList.append(objectItem);
    }
    return objectItemList;
}

TObjectItemList TGraphicsScene::getObjectItemList(const QRectF &rect, TObjectItem *objectItem) const
{
    TObjectItemList objectItemList;
    if(!objectItem)
        return objectItemList;

    QList<QGraphicsItem*> itemList = itemsOfCurrentLayerItem(rect);
    TObject *object = objectItem->object();
    for (QGraphicsItem *item : itemList) {
        if (!item->isEnabled())
            continue;

        TObjectItem *objectItem = qgraphicsitem_cast<TObjectItem*>(item);
        if (objectItem && object->isCongener(objectItem->object()))
            objectItemList.append(objectItem);
    }
    return objectItemList;
}
