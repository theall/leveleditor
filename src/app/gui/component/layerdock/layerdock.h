#ifndef LAYERDOCK_H
#define LAYERDOCK_H

#include <QMenu>
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

    TLayerView *layerView() const;
    void setOpacitySliderValue(int value);
    void setOpacitySliderValue(qreal value);

signals:
    void layerOpacityChanged(QList<int> rows, float opacity);

protected:
    void changeEvent(QEvent *e) override;

private slots:
    void slotSliderValueChanged(int value);
    void slotCurrentLayerSelected(int row);

private:
    TLayerView *mLayerView;
    QLabel *mOpacityLabel;
    QSlider *mOpacitySlider;

    QAction *mActionShowTiles;
    QAction *mActionShowObjects;
    QAction *mActionToggleOther;
    QAction *mActionToggleLockOther;

    void retranslateUi();
};

#endif // LAYERDOCK_H
