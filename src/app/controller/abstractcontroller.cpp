#include "abstractcontroller.h"

QList<TAbstractController*> TAbstractController::mInstances;
TDocument *TAbstractController::mDocument = nullptr;

TAbstractController::TAbstractController(QObject *parent) :
    QObject(parent),
    mTimer(new QTimer(this))
{
    connect(mTimer, SIGNAL(timeout()), this, SLOT(slotTimerEvent()));
    mInstances.append(this);
}

TAbstractController::~TAbstractController()
{
    if(mTimer)
    {
        mTimer->stop();
        delete mTimer;
    }
    mInstances.removeOne(this);
}

bool TAbstractController::joint(TMainWindow *mainWindow, TCore *core)
{
    mMainWindow = mainWindow;
    mCore = core;
    return true;
}

bool TAbstractController::jointAll(TMainWindow *mainWindow, TCore *core)
{
    bool ret = true;

    for(TAbstractController *controller : mInstances)
    {
        if(static_cast<TAbstractController*>(controller->parent()))
        {
            ret &= controller->joint(mainWindow, core);
        }
    }
    return ret;
}

void TAbstractController::startMyTimer(int mSecs)
{
    if(mTimer && !mTimer->isActive())
        mTimer->start(mSecs);
}

void TAbstractController::stopMyTimer()
{
    if(mTimer && mTimer->isActive())
        mTimer->stop();
}


