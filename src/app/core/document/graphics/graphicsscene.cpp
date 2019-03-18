#include <QPainter>
#include <QWheelEvent>
#include <QCoreApplication>
#include <QGraphicsSceneMouseEvent>

#include "graphicsscene.h"

#define TOP_Z_VALUE 10000
TGraphicsScene::TGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
  , mStepMode(false)
  , mTimerId(-1)
  , mSceneModel(nullptr)
  , mSceneItem(nullptr)
  , mHoveredItem(new THoveredItem)
  , mSelectedItem(new TSelectedItem)
{
    setSize(640, 480);

    mHoveredItem->setZValue(TOP_Z_VALUE);
    addItem(mHoveredItem);

    mSelectedItem->setZValue(TOP_Z_VALUE+1);
    addItem(mSelectedItem);
}

TGraphicsScene::~TGraphicsScene()
{

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

}

void TGraphicsScene::refresh()
{

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
    if(button == Qt::RightButton)
    {
        if(mTimerId==-1)
            play();
        else
            stop();
    } else if(button == Qt::LeftButton) {
        TObjectItem *objectItem = getTopMostObjectItem(event->scenePos());
        mSelectedItem->setObjectItem(objectItem);
        update();
    }
}

void TGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    TObjectItem *objectItem = getTopMostObjectItem(event->scenePos());
    mHoveredItem->setObjectItem(objectItem);
    update();
}

void TGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
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
    } else if(event->modifiers()&Qt::ControlModifier) {

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
