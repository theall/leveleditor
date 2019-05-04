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

    TLayerView *layerView() const;

signals:

protected:
    void changeEvent(QEvent *e) override;

private slots:

private:
    TLayerView *mLayerView;
    QAction *mActionToggleOther;
    QAction *mActionToggleLockOther;

    void retranslateUi();
};

#endif // LAYERDOCK_H
