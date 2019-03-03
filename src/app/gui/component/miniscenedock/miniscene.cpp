#include "miniscene.h"

#include <QCursor>
#include <QPainter>
#include <QResizeEvent>
#include <QScrollBar>
#include <QUndoStack>

TMiniScene::TMiniScene(QWidget *parent) :
    QFrame(parent)
  , mIsDragging(false)
  , mMouseMoveCursorState(false)
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    setMinimumSize(50, 50);

    // for cursor changes
    setMouseTracking(true);
}

TMiniScene::~TMiniScene()
{

}

QSize TMiniScene::sizeHint() const
{
    return QSize(200, 200);
}

void TMiniScene::paintEvent(QPaintEvent *pe)
{
    QFrame::paintEvent(pe);

    if(mSceneImage.isNull() || mImageRect.isEmpty())
        return;

//    QPainter p(this);
//    p.setRenderHints(QPainter::SmoothPixmapTransform);

//    QColor backgroundColor(Qt::darkGray);
//    if(mDocument && mDocument->map()->backgroundColor().isValid())
//        backgroundColor = mDocument->map()->backgroundColor();
//    p.setBrush(backgroundColor);
//    p.setPen(Qt::NoPen);
//    p.drawRect(contentsRect());

//    p.drawImage(mImageRect, mSceneImage);

//    const QRect viewRect = getViewPortRect();
//    p.setBrush(Qt::NoBrush);
//    p.setPen(QColor(0, 0, 0, 128));
//    p.translate(1, 1);
//    p.drawRect(viewRect);

//    QPen outLinePen(QColor(255, 0, 0), 2);
//    outLinePen.setJoinStyle(Qt::MiterJoin);
//    p.translate(-1, -1);
//    p.setPen(outLinePen);
//    p.drawRect(viewRect);
}

void TMiniScene::resizeEvent(QResizeEvent *)
{
    emit resized();
}

void TMiniScene::wheelEvent(QWheelEvent *event)
{    
    if(event->orientation() == Qt::Vertical) {
        int delta = event->delta();
        if(delta != 0)
            emit wheeled(event->pos(), delta);
        return;
    }

    QFrame::wheelEvent(event);
}

void TMiniScene::mousePressEvent(QMouseEvent *event)
{       
    if(event->button() == Qt::LeftButton) {
        QPoint cursorPos = event->pos();
//        QRect viewPort = getViewPortRect();

//        if(viewPort.contains(cursorPos)) {
//            mDragOffset = viewPort.center() - cursorPos + QPoint(1, 1);
//            cursorPos += mDragOffset;
//        } else {
//            mDragOffset = QPoint();
//            centerViewOnLocalPixel(cursorPos);
//        }

        mIsDragging = true;
        setCursor(Qt::ClosedHandCursor);

        return;
    }

    QFrame::mouseReleaseEvent(event);
}

void TMiniScene::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && mIsDragging)
    {
        mIsDragging = false;

//        QRect viewPort = getViewPortRect();
//        if(viewPort.contains(event->pos())) {
//            setCursor(Qt::OpenHandCursor);
//            mMouseMoveCursorState = true;
//        } else if(rect().contains(event->pos())) {
//            unsetCursor();
//            mMouseMoveCursorState = false;
//        }

        return;
    }

    QFrame::mouseReleaseEvent(event);
}

void TMiniScene::mouseMoveEvent(QMouseEvent *event)
{    
//    if(mIsDragging) {
//        centerViewOnLocalPixel(event->pos() + mDragOffset);
//        return;
//    }

//    if(getViewPortRect().contains(event->pos())) {
//        if(!mMouseMoveCursorState) {
//            setCursor(Qt::OpenHandCursor);
//            mMouseMoveCursorState = true;
//        }
//    } else {
//        if(mMouseMoveCursorState) {
//            unsetCursor();
//            mMouseMoveCursorState = false;
//        }
//    }

    QFrame::mouseMoveEvent(event);
}

QRect TMiniScene::imageRect() const
{
    return mImageRect;
}

void TMiniScene::setImageRect(const QRect &imageRect)
{
    mImageRect = imageRect;
    update();
}

QImage TMiniScene::sceneImage() const
{
    return mSceneImage;
}

void TMiniScene::setSceneImage(const QImage &sceneImage)
{
    mSceneImage = sceneImage;
    update();
}
