#ifndef TMAPSDOCKCONTROLLER_H
#define TMAPSDOCKCONTROLLER_H

#include "abstractcontroller.h"

class TMapsDockController : public TAbstractController
{
    Q_OBJECT

public:
    explicit TMapsDockController(QObject *parent = 0);
    ~TMapsDockController();

private:

    // TAbstractController interface
public:
    bool joint(TMainWindow *mainWindow, TCore *core);
    void setCurrentDocument(TDocument *document);

private slots:
    void slotOnCoreReady();

protected slots:
    void slotTimerEvent();
};

#endif // TMAPSDOCKCONTROLLER_H
