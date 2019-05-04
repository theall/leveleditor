#ifndef LAYERSCONTROLLER_H
#define LAYERSCONTROLLER_H

#include "abstractcontroller.h"

class TLayerView;
class TLayersController : public TAbstractController
{
    Q_OBJECT

public:
    TLayersController(QObject *parent = 0);
    ~TLayersController();

    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;

signals:

private slots:

private:
    TLayerView *mLayerView;

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // LAYERSCONTROLLER_H
