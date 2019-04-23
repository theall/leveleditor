#ifndef LAYERDOCK_H
#define LAYERDOCK_H

#include <QLabel>
#include <QDockWidget>
#include "layerview.h"

/**
 * The dock widget that displays scene layers.
 */
class TLayerDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit TLayerDock(QWidget *parent = nullptr);
    ~TLayerDock();

    void enableOpacitySlider(bool enabled);
    void setOpacitySliderValue(int value);

signals:
    void opacitySliderValueChanged(int);

protected:
    void changeEvent(QEvent *e) override;

private slots:
    void layerChanged(int index);
    void editLayerName();
    void slotSliderValueChanged(int opacity);

private:
    TLayerView *mLayerView;
    bool mUpdatingSlider;
    bool mChangingLayerOpacity;

    void retranslateUi();
};

#endif // LAYERDOCK_H
