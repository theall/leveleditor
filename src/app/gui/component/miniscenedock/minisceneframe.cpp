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
  , mBackgroundColor(QColor(Qt::darkGray))//深灰色
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);//框架样式  画矩形 框架内容为凹陷，用当前颜色深浅画
    setMinimumSize(200, 200);//最小大小

    // for cursor changes 用于光标更改
    setMouseTracking(true);//是否开启鼠标追踪 默认为false
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

    if(mSceneImage.isNull() || mImageRect.isEmpty())//当前中间图像是否空||当前矩形中是否存放了图像
        return;

    QPainter p(this);//设置画笔
    p.setRenderHints(QPainter::SmoothPixmapTransform);//设置提供提示（如果on为true，则在绘制器上设置给定的渲染提示；否则清除渲染提示。）
    //指示引擎应使用平滑的pixmap转换算法（如双线性），而不是最近邻。

    p.setBrush(mBackgroundColor);//将画笔设为深灰色
    p.setPen(Qt::NoPen);//设置画笔样式（一点线也没有。）
    p.drawRect(contentsRect());//画矩形（矩形目录，返回小部件页边距内的区域）

    p.drawImage(mImageRect, mSceneImage);//画图像
    p.setBrush(Qt::NoBrush);//设置为白色的画笔样式即填充样式
    p.setPen(QColor(0, 0, 0, 128));//设置画笔样式（CMYK）,阴影样式
    p.translate(1, 1);//按给定偏移量转换坐标系；即将给定偏移量添加到点。
    p.drawRect(mViewPortRect);//画矩形

    QPen outLinePen(QColor(255, 0, 0), 2);//QPen 告诉画笔怎么画 RGB
    outLinePen.setJoinStyle(Qt::MiterJoin);//设置笔连接样式即两条线的连接样式（线的外缘被延伸成一定角度，并填充此区域。）
    p.translate(-1, -1);
    p.setPen(outLinePen);
    p.drawRect(mViewPortRect);
}

void TMiniSceneFrame::resizeEvent(QResizeEvent *)//大小调整事件
{
    emit resized();
}

void TMiniSceneFrame::wheelEvent(QWheelEvent *event)//轮事件（鼠标滚轮和触控板滚动手势都会生成滚轮事件。）
{
    if(event->orientation() == Qt::Vertical) {//如果轮子方向是垂直的
        int delta = event->delta();
        if(delta != 0)
            emit requestLocatePoint(event->pos(), delta);//返回鼠标所在位置的xy
        return;
    }

    QFrame::wheelEvent(event);//调用父类的轮事件
}

void TMiniSceneFrame::mousePressEvent(QMouseEvent *event)//鼠标按下事件
{
    if(event->button() == Qt::LeftButton) {//判断按下的是不是左鼠标
        QPoint cursorPos = event->pos();//返回鼠标光标相对于接收事件的小部件的位置。
        if(mViewPortRect.contains(cursorPos)) {//如果给定点位于矩形的内部或边缘，则返回true，否则返回false
            mDragOffset = mViewPortRect.center() - cursorPos + QPoint(1, 1);//矩形中心点减去鼠标所在点加上一
        } else {
            mDragOffset = QPoint();//构造一个空点，即（0，0）
            emit requestLocatePoint(cursorPos);//信号返回（鼠标所在点）
        }

        mIsDragging = true;
        setCursor(Qt::ClosedHandCursor);//设置光标形状为闭合的手

        return;
    }

    QFrame::mouseReleaseEvent(event);
}

void TMiniSceneFrame::mouseReleaseEvent(QMouseEvent *event)//鼠标释放事件
{
    if(event->button() == Qt::LeftButton && mIsDragging)//判断按下的是不是左鼠标并且已经被按下
    {
        mIsDragging = false;
        if(mViewPortRect.contains(event->pos())) {
            setCursor(Qt::OpenHandCursor);//设置光标为抓手
            mMouseMoveCursorState = true;
        } else if(rect().contains(event->pos())) {//此属性保留小部件的内部几何图形，不包括任何窗口框架。
            unsetCursor();//保存此小部件的光标形状。
            mMouseMoveCursorState = false;
        }

        return;
    }

    QFrame::mouseReleaseEvent(event);
}

void TMiniSceneFrame::mouseMoveEvent(QMouseEvent *event)//鼠标移动
{
    if(mIsDragging) {//判断鼠标释放
        emit requestLocatePoint(event->pos() + mDragOffset);//光标相对于接收事件的小部件的位置
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

    // Scale and center the image 缩放图像并使其居中
    const QRect r = contentsRect();
    qreal scale = qMin((qreal)r.width()/imageRect.width(), (qreal)r.height()/imageRect.height());
    imageRect.setSize(imageRect.size() * scale);
    imageRect.moveCenter(r.center());

    mImageRect = imageRect;
}
