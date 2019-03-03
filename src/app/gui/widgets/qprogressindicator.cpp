#include "qprogressindicator.h"

#include <QTimer>
#include <QPainter>

QProgressIndicator::QProgressIndicator(QWidget* parent):
    QWidget(parent)
{
    mParent = parent;
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFocusPolicy(Qt::NoFocus);
    mAngle = 0;
    mTimerId = -1;
    mDelayShowSec = 1500;
    mDelayTime = 64;
    bTerminate = false;
    mDisplay = false;

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);

    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(QSize(48, 48));
    setMaximumSize(QSize(48, 48));

    updatePos();
}

QProgressIndicator::~QProgressIndicator()
{

}

void QProgressIndicator::updatePos()
{
    if(mParent && mParent->isVisible())
    {
        QPoint pos = mParent->mapToGlobal(QPoint(0, 0));
        int pl = pos.x();
        int pt = pos.y();
        int pw = mParent->width();
        int ph = mParent->height();
        int w = width();
        int h = height();

        move(pl+(pw-w)/2, pt+(ph-h)/2);
    }
}

bool QProgressIndicator::isAnimated()
{
    return (mTimerId != -1);
}

int QProgressIndicator::animationDelay()
{
    return mDelayTime;
}

void QProgressIndicator::setColor(QColor color)
{
    mColor = color;
    update();
}

QColor QProgressIndicator::getColor()
{
    return mColor;
}

void QProgressIndicator::setDisplayWhenStop(bool display)
{
    mDisplay = display;
    update();
}

bool QProgressIndicator::isDisplayWhenStop()
{
    return mDisplay;
}

void QProgressIndicator::delayStart()
{
    if(!bTerminate)
        mTimerId = QObject::startTimer(mDelayTime);
}

void QProgressIndicator::start(int delayTime)
{
    startAnimation(delayTime);
}

void QProgressIndicator::startAnimation(int delayTime)
{
    mAngle = 0;
    if(mTimerId == -1)
    {
        bTerminate = false;
        QTimer::singleShot(delayTime, this, SLOT(delayStart()));
    }
    mDelayShowSec = delayTime;
    mSecElispse = 0;
}

QProgressIndicator* QProgressIndicator::getWaitIcon(QWidget* parent, int delayTime)
{
    QProgressIndicator* dialog = new QProgressIndicator(parent);
    dialog->startAnimation(delayTime);
    return dialog;
}

void QProgressIndicator::stop()
{
    if(mTimerId != -1)
    {
        killTimer(mTimerId);
        mTimerId = -1;
        update();
    }
    bTerminate = true;
    hide();
}

void QProgressIndicator::setTerminate()
{
    bTerminate = true;
}

void QProgressIndicator::stopAnimation()
{
    bTerminate = true;
}

void QProgressIndicator::setAnimationDelay(int delayTime)
{
    if(mTimerId != -1)
    {
        killTimer(mTimerId);
        mTimerId = startTimer(delayTime);
    }
    mDelayTime = mDelayTime;
    show();
}

void QProgressIndicator::timerEvent(QTimerEvent* event)
{
    event = event;
    if(bTerminate)
    {
        stop();
        return;
    }
    if(mParent && !mParent->isVisible())
    {
        hide();
        return;
    }
    bool bVisible = isVisible();
    updatePos();

    if(!bVisible)
        show();

    mAngle = (mAngle + 30) % 360;
    update();
}

void QProgressIndicator::paintEvent(QPaintEvent* event)
{
    event = event;
    if(!mDisplay && !isAnimated())
        return;
    int _width = qMin(width(), height());
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    int outer_radius = (_width - 1) * 0.5;
    int inner_radius = (_width - 1) * 0.5 * 0.4;
    int capsule_height = outer_radius - inner_radius;
    int capsule_width  = 0;
    if(_width > 32)
        capsule_width = capsule_height * 0.30;
    else
        capsule_height *= 0.35;
    int capsule_radius = capsule_width/2;
    for(int i=0;i<12;i++)
    {
        QColor color;
        color.setAlphaF(1.0 - (i/12.0));
        p.setPen(Qt::NoPen);
        p.setBrush(color) ;
        p.save();
        p.translate(rect().center());
        p.rotate(mAngle - i*30.0);
        p.drawRoundedRect(-capsule_width*0.5, -(inner_radius+capsule_height), capsule_width, capsule_height, capsule_radius, capsule_radius);
        p.restore();
    }
}
