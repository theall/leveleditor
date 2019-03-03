#ifndef MINISCENE_H
#define MINISCENE_H

#include <QFrame>
#include <QImage>
#include <QTimer>
#include <QFlags>

class TMiniScene : public QFrame
{
    Q_OBJECT

public:
    TMiniScene(QWidget *parent);
    ~TMiniScene();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    QImage sceneImage() const;
    void setSceneImage(const QImage &sceneImage);

    QRect imageRect() const;
    void setImageRect(const QRect &imageRect);

signals:
    void resized();
    void wheeled(const QPoint &pos, int delta);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QRect mImageRect;
    QRect mViewRect;
    QImage mSceneImage;
    bool mIsDragging;
    QPoint mDragOffset;
    bool mMouseMoveCursorState;
};

#endif // MINISCENE_H
