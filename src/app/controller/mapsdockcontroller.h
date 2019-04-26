#ifndef TMAPSDOCKCONTROLLER_H
#define TMAPSDOCKCONTROLLER_H

#include "abstractcontroller.h"
#include "core/model/mapsmodel.h"

class TMapsProxyView;
class TMapsDockController : public TAbstractController
{
    Q_OBJECT

public:
    explicit TMapsDockController(QObject *parent = 0);
    ~TMapsDockController();

signals:
    void requestOpenMap(TMap *map);

private:
    TMapsModel *mMapsModel;
    TMapsProxyView *mMapsProxyView;

    // TAbstractController interface
public:
    bool joint(TMainWindow *mainWindow, TCore *core);
    void setCurrentDocument(TDocument *document);

private slots:
    void slotOnCoreReady();
    void slotOnModelIndexDoubleClicked(const QModelIndex &index);
    void slotOnModuleAdded(TModule *module, int);
    void slotOnModuleRemoved(TModule *module, int index);

protected slots:
    void slotTimerEvent();
};

#endif // TMAPSDOCKCONTROLLER_H
