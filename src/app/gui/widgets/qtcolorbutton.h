#ifndef QTCOLORBUTTON_H
#define QTCOLORBUTTON_H

#include <QPixmap>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QToolButton>

QT_BEGIN_NAMESPACE

class QtColorButton;
class QtColorButtonPrivate
{
    QtColorButton *q_ptr;
    Q_DECLARE_PUBLIC(QtColorButton)
public:
    QColor mColor;
#ifndef QT_NO_DRAGANDDROP
    QColor mDragColor;
    QPoint mDragStart;
    bool mDragging;
#endif
    bool mBackgroundCheckered;

    void slotEditColor();
    QColor shownColor() const;
    QPixmap generatePixmap() const;
};

class QtColorButton : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(bool backgroundCheckered READ isBackgroundCheckered WRITE setBackgroundCheckered)
public:
    QtColorButton(QWidget *parent = 0);
    ~QtColorButton();

    bool isBackgroundCheckered() const;
    void setBackgroundCheckered(bool checkered);

    QColor color() const;

public slots:

    void setColor(const QColor &color);

signals:
    void colorChanged(const QColor &color);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
#ifndef QT_NO_DRAGANDDROP
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);
#endif
private:
    QScopedPointer<QtColorButtonPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtColorButton)
    Q_DISABLE_COPY(QtColorButton)
    Q_PRIVATE_SLOT(d_func(), void slotEditColor())
};

QT_END_NAMESPACE

#endif
