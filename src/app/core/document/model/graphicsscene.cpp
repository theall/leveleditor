#include <QPainter>
#include <QWheelEvent>
#include <QCoreApplication>
#include <QGraphicsSceneMouseEvent>

#include "graphicsscene.h"

static const int TILE_WIDTH = 16;
static const int TILE_HEIGHT = 16;
static const int CALIBRATION_LINE_WIDTH = 2;
static const int CALIBRATION_NUMBER_WITH = 48;
static const int CALIBRATION_NUMBER_FONT_SIZE = 8;
static const int PADING_WIDTH = 4;

TGraphicsScene::TGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
  , mStepMode(false)
  , mTimerId(-1)
{
    setSize(640, 480);
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
    if(event->button()==Qt::RightButton)
    {
        if(mTimerId==-1)
            play();
        else
            stop();
    }
}

void TGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
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

void TGraphicsScene::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    step();
}
