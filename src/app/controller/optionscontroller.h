#ifndef OPTIONSCONTROLLER_H
#define OPTIONSCONTROLLER_H

#include "abstractcontroller.h"

class TOptionsController : public TAbstractController
{
    Q_OBJECT

public:
    explicit TOptionsController(QObject *parent = 0);
    ~TOptionsController();

    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;

private slots:

private:
    TMainWindow *mMainWindow;

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // OPTIONSCONTROLLER_H
