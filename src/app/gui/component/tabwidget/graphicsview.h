#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class TGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    TGraphicsView(QWidget *parent = Q_NULLPTR);
    ~TGraphicsView();

    qreal scale() const;
    void setScale(const qreal &scale);

signals:
    void resized();

private:
    qreal mScale;

private:
    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // GRAPHICSVIEW_H
