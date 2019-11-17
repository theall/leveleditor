#ifndef MINISCENEFRAME_H
#define MINISCENEFRAME_H

#include <QFrame>
#include <QImage>
#include <QTimer>
#include <QFlags>

class TMiniSceneFrame : public QFrame
{
    Q_OBJECT

public:
    TMiniSceneFrame(QWidget *parent);
    ~TMiniSceneFrame();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    QImage sceneImage() const;
    void setSceneImage(const QImage &sceneImage);

    void setBackgroundColor(const QColor &backgroundColor);

    QRect viewPortRect() const;
    void setViewPortRect(const QRect &viewPortRect);

    QRect imageRect() const;

signals:
    void resized();
    void requestLocatePoint(const QPoint &point, int delta = 0);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;//画图
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;//调整大小
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;//轮事件
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QRect mImageRect;//矩形中存放按照比例缩小的窗口图像
    QRect mViewPortRect;
    QImage mSceneImage;
    bool mIsDragging;
    QPoint mDragOffset;
    bool mMouseMoveCursorState;
    QColor mBackgroundColor;

    void updateImageRect();
};

#endif // MINISCENEFRAME_H
