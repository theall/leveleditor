#include "minisceneframe.h"

#include <QDebug>
#include <QCursor>
#include <QPainter>
#include <QScrollBar>
#include <QUndoStack>
#include <QResizeEvent>

TMiniSceneFrame::TMiniSceneFrame(QWidget *parent) :
    QFrame(parent)
  , mIsDragging(false)
  , mMouseMoveCursorState(false)
  , mBackgroundColor(QColor(Qt::darkGray))
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    setMinimumSize(50, 50);

    // for cursor changes
    setMouseTracking(true);
}

TMiniSceneFrame::~TMiniSceneFrame()
{

}

QSize TMiniSceneFrame::sizeHint() const
{
    return QSize(200, 200);
}

void TMiniSceneFrame::paintEvent(QPaintEvent *pe)
{
    QFrame::paintEvent(pe);

    if(mSceneImage.isNull() || mImageRect.isEmpty())
        return;

    QPainter p(this);
    p.setRenderHints(QPainter::SmoothPixmapTransform);

    p.setBrush(mBackgroundColor);
    p.setPen(Qt::NoPen);
    p.drawRect(contentsRect());

    p.drawImage(mImageRect, mSceneImage);
    p.setBrush(Qt::NoBrush);
    p.setPen(QColor(0, 0, 0, 128));
    p.translate(1, 1);
    p.drawRect(mViewPortRect);

    QPen outLinePen(QColor(255, 0, 0), 2);
    outLinePen.setJoinStyle(Qt::MiterJoin);
    p.translate(-1, -1);
    p.setPen(outLinePen);
    p.drawRect(mViewPortRect);
}

void TMiniSceneFrame::resizeEvent(QResizeEvent *)
{
    emit resized();
}

void TMiniSceneFrame::wheelEvent(QWheelEvent *event)
{
    if(event->orientation() == Qt::Vertical) {
        int delta = event->delta();
        if(delta != 0)
            emit requestLocatePoint(event->pos(), delta);
        return;
    }

    QFrame::wheelEvent(event);
}

void TMiniSceneFrame::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        QPoint cursorPos = event->pos();
        if(mViewPortRect.contains(cursorPos)) {
            mDragOffset = mViewPortRect.center() - cursorPos + QPoint(1, 1);
        } else {
            mDragOffset = QPoint();
            emit requestLocatePoint(cursorPos);
        }

        mIsDragging = true;
        setCursor(Qt::ClosedHandCursor);

        return;
    }

    QFrame::mouseReleaseEvent(event);
}

void TMiniSceneFrame::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && mIsDragging)
    {
        mIsDragging = false;
        if(mViewPortRect.contains(event->pos())) {
            setCursor(Qt::OpenHandCursor);
            mMouseMoveCursorState = true;
        } else if(rect().contains(event->pos())) {
            unsetCursor();
            mMouseMoveCursorState = false;
        }

        return;
    }

    QFrame::mouseReleaseEvent(event);
}

void TMiniSceneFrame::mouseMoveEvent(QMouseEvent *event)
{
    if(mIsDragging) {
        emit requestLocatePoint(event->pos() + mDragOffset);
        return;
    }

    if(mViewPortRect.contains(event->pos())) {
        if(!mMouseMoveCursorState) {
            setCursor(Qt::OpenHandCursor);
            mMouseMoveCursorState = true;
        }
    } else {
        if(mMouseMoveCursorState) {
            unsetCursor();
            mMouseMoveCursorState = false;
        }
    }

    QFrame::mouseMoveEvent(event);
}

QRect TMiniSceneFrame::imageRect() const
{
    return mImageRect;
}

QRect TMiniSceneFrame::viewPortRect() const
{
    return mViewPortRect;
}

void TMiniSceneFrame::setViewPortRect(const QRect &viewPortRect)
{
    if(viewPortRect == mViewPortRect)
        return;

    mViewPortRect = viewPortRect;
}

void TMiniSceneFrame::setBackgroundColor(const QColor &backgroundColor)
{
    if(mBackgroundColor == backgroundColor)
        return;

    mBackgroundColor = backgroundColor;
}

QImage TMiniSceneFrame::sceneImage() const
{
    return mSceneImage;
}

void TMiniSceneFrame::setSceneImage(const QImage &sceneImage)
{
    mSceneImage = sceneImage;
    updateImageRect();
}

void TMiniSceneFrame::updateImageRect()
{
    QRect imageRect = mSceneImage.rect();
    if(imageRect.isEmpty()) {
        mImageRect = QRect();
        return;
    }

    // Scale and center the image
    const QRect r = contentsRect();
    qreal scale = qMin((qreal)r.width()/imageRect.width(), (qreal)r.height()/imageRect.height());
    imageRect.setSize(imageRect.size() * scale);
    imageRect.moveCenter(r.center());

    mImageRect = imageRect;
}
