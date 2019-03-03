#ifndef TABSTRACTCONTROLLER_H
#define TABSTRACTCONTROLLER_H

#include <QTimer>

#include "../gui/mainwindow.h"
#include "../core/core.h"

class TAbstractController : public QObject
{
    Q_OBJECT

public:
    explicit TAbstractController(QObject *parent = 0);
    ~TAbstractController();

    virtual bool joint(TMainWindow *mainWindow, TCore *core);
    virtual void setCurrentDocument(TDocument *document) = 0;

    static bool jointAll(TMainWindow *mainWindow, TCore *core);

    void startMyTimer(int mSecs = 50);
    void stopMyTimer();

protected slots:
    virtual void slotTimerEvent() = 0;

signals:

protected:
    TMainWindow *mMainWindow;
    TCore *mCore;
    QTimer *mTimer;
    static TDocument *mDocument;

private:
    static QList<TAbstractController*> mInstances;
};

#endif // TABSTRACTCONTROLLER_H
