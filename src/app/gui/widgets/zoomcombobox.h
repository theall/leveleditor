#ifndef ZOOMCOMBOBOX_H
#define ZOOMCOMBOBOX_H

#include <QComboBox>
#include <QPinchGesture>

class TZoomComboBox : public QComboBox
{
    Q_OBJECT

public:
    TZoomComboBox(QWidget *parent = Q_NULLPTR);
    ~TZoomComboBox();

    qreal scaleValue() const;
    void setScaleValue(qreal scaleValue, bool emitSignal = true);

    void zoomIn();
    void zoomOut();
    void resetZoom();

    void handleWheelDelta(int delta);
    void handlePinchGesture(QPinchGesture *pinch);

    bool canZoomIn() const;
    bool canZoomOut() const;

signals:
    void scaleChanged(qreal scale);

private slots:
    void slotComboEdited();
    void slotCurrentIndexChanged(int index);

private:
    qreal mScaleValue;
    qreal mGestureStartScale;
    QVector<qreal> mZoomFactors;
    QRegExp mComboRegExp;
};

#endif // ZOOMCOMBOBOX_H
