#include <QDebug>
#include <QPainter>
#include <QWheelEvent>
#include <QCoreApplication>
#include <QGraphicsSceneMouseEvent>

#include "graphicsscene.h"
#include "../base/finddoc.h"
#include "../document.h"
#include "../undocommand/objectundocommand.h"

#define TOP_Z_VALUE 10000
TGraphicsScene::TGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
  , mStepMode(false)
  , mTimerId(-1)
  , mLeftButtonDown(false)
  , mAction(NoAction)
  , mCursor(Qt::ArrowCursor)
  , mSceneModel(nullptr)
  , mSceneItem(nullptr)
  , mHoveredItem(new THoveredItem)
  , mSelectedItems(new TSelectedItems)
  , mSelectionRectangle(new TSelectionRectangle)
  , mLastSelectedObjectItem(nullptr)
  , mDocument(nullptr)
{
    setSize(640, 480);

    mHoveredItem->setZValue(TOP_Z_VALUE-2);
    addItem(mHoveredItem);

    mSelectedItems->setZValue(TOP_Z_VALUE-1);
    addItem(mSelectedItems);

    mSelectionRectangle->setZValue(TOP_Z_VALUE);
    addItem(mSelectionRectangle);

    FIND_DOCUMENT;
}

TGraphicsScene::~TGraphicsScene()
{
    delete mHoveredItem;
    delete mSelectedItems;
    delete mSelectionRectangle;
}

void TGraphicsScene::setSize(qreal w, qreal h)
{
    setSceneRect(0.0, 0.0, w, h);
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

void TGraphicsScene::play()
{
    if(mTimerId != -1)
        killTimer(mTimerId);

    mStepMode = false;
    mTimerId = startTimer(1000.0/mFps);
}

bool TGraphicsScene::isPlaying()
{
    return mTimerId != -1;
}

void TGraphicsScene::stop()
{
    if(mTimerId != -1)
    {
        killTimer(mTimerId);
        mTimerId = -1;
    }
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
    if(mSceneModel) {
        mSceneModel->disconnect(this);
        removeItem((QGraphicsItem*)mSceneItem);
    }

    mSceneModel = sceneModel;

    if(mSceneModel) {
        mSceneItem = new TSceneItem(sceneModel);
        addItem((QGraphicsItem*)mSceneItem);
        connect(mSceneModel->propertySheet(),
                SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
                this,
                SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant)));

        setBackgroundColor(mSceneModel->getBackgroundColor());
        QRectF rect = mSceneItem->boundingRect();
        setSize(rect.size());
    }
}

void TGraphicsScene::removeSelectedItems()
{
    TObjectList objectList = mSelectedItems->getSelectedObjectList();
    if(objectList.size() < 1)
        return;
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

}

void TGraphicsScene::pushObjectMoveCommand(const TObjectList &objectList, const QPointF &offset)
{
    TObjectUndoCommand *command = new TObjectUndoCommand(
                TObjectUndoCommand::Move,
                objectList,
                offset);
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
    Qt::MouseButton button = event->button();
    mLeftButtonDown = (button==Qt::LeftButton);
    if(button == Qt::RightButton)
    {
        if(mTimerId==-1)
            play();
        else
            stop();
    } else if(button == Qt::LeftButton) {
        mLeftButtonDownPos = event->scenePos();
        Qt::KeyboardModifiers modifers = event->modifiers();
        if(modifers&Qt::ShiftModifier) {
            TObjectItem *objectItem = getTopMostObjectItem(mLeftButtonDownPos);
            if(mLastSelectedObjectItem && mLastSelectedObjectItem->isCongener(objectItem)) {
                qreal leftButtonDownX = mLeftButtonDownPos.x();
                qreal leftButtonDownY = mLeftButtonDownPos.y();
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
}

void TGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    TObjectItem *objectItem = getTopMostObjectItem(event->scenePos());
    if(!mLeftButtonDown) {
        if(mSelectedItems->containsObjectItem(objectItem))
            mHoveredItem->setObjectItem(nullptr);
        else
            mHoveredItem->setObjectItem(objectItem);
        mAction = NoAction;
    } else {
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
        if(mAction == Moving) {
            // Move selected object item
            TObjectList objectList = mSelectedItems->getSelectedObjectList();
            if(objectList.size() > 0) {
                QPointF offset = event->scenePos() - event->lastScenePos();
                if(!offset.isNull()) {
                    pushObjectMoveCommand(objectList, offset);
                }
            }
        } else if(mAction == Selecting) {
            mSelectionRectangle->setRectangle(QRectF(mLeftButtonDownPos, event->scenePos()));
        }
    }
    updateCursor();
    update();
}

void TGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(mLeftButtonDown) {
        mLeftButtonDown = false;
        if(mAction == NoAction) {
            TObjectItem *objectItem = getTopMostObjectItem(event->scenePos());
            if(objectItem) {
                Qt::KeyboardModifiers modifers = event->modifiers();
                if(modifers&Qt::ControlModifier) {
                    if(mLeftButtonDownPos==event->scenePos()) {
                        // The mouse pos is not equal to mLeftButtonDownPos after selected items moved
                        if(!mSelectedItems->containsObjectItem(objectItem)) {
                            mSelectedItems->addObjectItem(objectItem);
                        } else {
                            mSelectedItems->removeObjectItem(objectItem);
                        }
                    }
                    mLastSelectedObjectItem = objectItem;
                } else if(modifers&Qt::ShiftModifier) {
                    if(!mLastSelectedObjectItem)
                        mLastSelectedObjectItem = objectItem;
                } else {
                    mSelectedItems->setObjectItem(objectItem);
                    mLastSelectedObjectItem = objectItem;
                }
            } else {
                mSelectedItems->setObjectItem(nullptr);
                mLastSelectedObjectItem = nullptr;
            }
        } else if(mAction == Moving) {
            mAction = NoAction;
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
        }

        update();
    }
}

void TGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void TGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
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

TObject *TGraphicsScene::getTopMostObject(const QPointF &pos) const
{
    TObjectItem *objectItem = getTopMostObjectItem(pos);
    if (objectItem)
        return objectItem->object();
    return nullptr;
}

TObjectItem *TGraphicsScene::getTopMostObjectItem(const QPointF &pos) const
{
    const QList<QGraphicsItem *> &itemList = items(pos);

    for (QGraphicsItem *item : itemList) {
        if (!item->isEnabled())
            continue;

        TObjectItem *objectItem = qgraphicsitem_cast<TObjectItem*>(item);
        if (objectItem)
            return objectItem;
    }
    return nullptr;
}

TObjectItemList TGraphicsScene::getObjectItemList(const QRectF &rect) const
{
    const QList<QGraphicsItem *> &itemList = items(rect);
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
    const QList<QGraphicsItem *> &itemList = items(rect);
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

    const QList<QGraphicsItem *> &itemList = items(rect);
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
