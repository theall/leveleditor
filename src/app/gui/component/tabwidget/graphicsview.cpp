#include "graphicsview.h"
#include "../../widgets/flexiblescrollbar.h"

#include <utils/preferences.h>

TGraphicsView::TGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
  , mLeftButtonDown(false)
{
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
#ifdef Q_OS_MAC
    setFrameStyle(QFrame::NoFrame);
#endif

    QWidget *v = viewport();

    /* Since Qt 4.5, setting this attribute yields significant repaint
     * reduction when the view is being resized. */
    v->setAttribute(Qt::WA_StaticContents);

    /* Since Qt 4.6, mouse tracking is disabled when no graphics item uses
     * hover events. We need to set it since our scene wants the events. */
    v->setMouseTracking(true);

    // Adjustment for antialiasing is done by the items that need it
    setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);

    grabGesture(Qt::PinchGesture);

    setVerticalScrollBar(new TFlexibleScrollBar(Qt::Vertical, this));
    setHorizontalScrollBar(new TFlexibleScrollBar(Qt::Horizontal, this));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

TGraphicsView::~TGraphicsView()
{

}

qreal TGraphicsView::scale() const
{
    return mScale;
}

void TGraphicsView::setScale(const qreal &scale)
{
    if(mScale == scale)
        return;

    mScale = scale;
    setTransform(QTransform::fromScale(mScale, mScale));
}

/**
 * Centers the view on the given scene position, even when this requires
 * extending the range of the scroll bars.
 *
 * This code is based on QGraphicsView::centerOn.
 */
void TGraphicsView::forceCenterOn(const QPointF &pos)
{
    // This is only to make it update QGraphicsViewPrivate::lastCenterPoint,
    // just in case this is important.
    centerOn(pos);

    TFlexibleScrollBar *hBar = static_cast<TFlexibleScrollBar*>(horizontalScrollBar());
    TFlexibleScrollBar *vBar = static_cast<TFlexibleScrollBar*>(verticalScrollBar());
    bool hScroll = hBar->minimum()!=0 || hBar->maximum()!=0;
    bool vScroll = vBar->minimum()!=0 || vBar->maximum()!=0;

    qreal width = viewport()->width();
    qreal height = viewport()->height();
    QPointF viewPoint = transform().map(pos);

    if(hScroll) {
        if (isRightToLeft()) {
            qint64 horizontal = 0;
            horizontal += hBar->minimum();
            horizontal += hBar->maximum();
            horizontal -= int(viewPoint.x()-width/2.0);
            hBar->forceSetValue(static_cast<int>(horizontal));
        } else {
            hBar->forceSetValue(int(viewPoint.x()-width/2.0));
        }
    }
    if(vScroll) {
        vBar->forceSetValue(int(viewPoint.y()-height/2.0));
    }
}

void TGraphicsView::resizeEvent(QResizeEvent *)
{
    emit resized();
}

void TGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    emit requestPopupContextMenu(event->globalPos());
}

void TGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    mLeftButtonDown = true;
    mLastMousePos = event->globalPos();
}

void TGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

    mLeftButtonDown = false;
}

void TGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsView::mouseDoubleClickEvent(event);
}

void TGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

//    if(!mLeftButtonDown)
//        return;

//    QGraphicsScene *graphicsScene = scene();
//    if(!graphicsScene)
//        return;

//    TFlexibleScrollBar *hBar = static_cast<TFlexibleScrollBar*>(horizontalScrollBar());
//    TFlexibleScrollBar *vBar = static_cast<TFlexibleScrollBar*>(verticalScrollBar());
//    const QPoint d = event->globalPos() - mLastMousePos;

//    int horizontalValue = hBar->value() + (isLeftToRight()?d.x():-d.x());
//    int verticalValue = vBar->value() + d.y();

//    // Panning can freely move the map without restriction on boundaries
//    //hBar->forceSetValue(horizontalValue);
//    //vBar->forceSetValue(verticalValue);

//    mLastMousePos = event->globalPos();
}
