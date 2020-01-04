#include "graphicsview.h"
#include "../../widgets/flexiblescrollbar.h"
#include "graphicsviewcontexmenu.h"

#include <utils/preferences.h>

TGraphicsView::TGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
  , mLeftButtonDown(false)
  , mGraphicsViewContextMenu(new TGraphicsViewContextMenu(this))
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

    connect(mGraphicsViewContextMenu,SIGNAL(pressDownPaste()), this, SLOT(slotPressDownPaste()));
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

TGraphicsViewContextMenu *TGraphicsView::graphicsViewContextMenu() const
{
    return mGraphicsViewContextMenu;
}

void TGraphicsView::slotPressDownPaste()
{
    emit pressDownPaste(mCurrentMousePos);
}

void TGraphicsView::resizeEvent(QResizeEvent *)
{
    emit resized();
}

void TGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
//    emit requestPopupContextMenu(event->globalPos());
}

void TGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    mLeftButtonDown = true;
    mLastMousePos = event->globalPos();
    if(event->button() == Qt::RightButton) {
        emit requestPopupContextMenu();
        mGraphicsViewContextMenu->exec(QCursor::pos());
        mLeftButtonDown = false;
    }if(event->button() == Qt::LeftButton)
        mGraphicsViewContextMenu->setAllActionsState(false);
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
    mCurrentMousePos = mapToScene(event->pos());
    emit onMouseMoved(mCurrentMousePos);
    if(!mLeftButtonDown)
        return;

    QGraphicsScene *graphicsScene = scene();
    if(!graphicsScene)
        return;

    QPoint mousePos = event->globalPos();
    TFlexibleScrollBar *hBar = static_cast<TFlexibleScrollBar*>(horizontalScrollBar());
    TFlexibleScrollBar *vBar = static_cast<TFlexibleScrollBar*>(verticalScrollBar());
    bool hOverceed = hBar->overceed();
    bool vOverceed = vBar->overceed();
    if(hOverceed || vOverceed) {
        const QPoint d = mousePos - mLastMousePos;

        int horizontalValue = hBar->value() + (isLeftToRight()?d.x():-d.x());
        int verticalValue = vBar->value() + d.y();

        // Panning can freely move the map without restriction on boundaries
        if(hOverceed)
            hBar->forceSetValue(horizontalValue);

        if(vOverceed)
            vBar->forceSetValue(verticalValue);
    }
    mLastMousePos = mousePos;
}
