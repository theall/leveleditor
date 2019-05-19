#ifndef LAYERSCONTROLLER_H
#define LAYERSCONTROLLER_H

#include "abstractcontroller.h"

class TLayerView;
class TLayerDock;
class TLayersController : public TAbstractController
{
    Q_OBJECT

public:
    TLayersController(QObject *parent = 0);
    ~TLayersController();

    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;

signals:
    void layerSelected(int index);

private slots:
    void slotCurrentLayerSelected(int row);
    void slotLayerOpacityChanged(const QList<int> &rows, float opacity);
    void slotRequestShowLayers(const QList<int> &rows, bool show);
    void slotRequestLockLayers(const QList<int> &rows, bool lock);

private:
    TLayerView *mLayerView;
    TLayerDock *mLayerDock;

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // LAYERSCONTROLLER_H
