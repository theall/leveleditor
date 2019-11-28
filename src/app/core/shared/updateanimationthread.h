#ifndef TUPDATEANIMATIONTHREAD_H
#define TUPDATEANIMATIONTHREAD_H

#include <QThread>

#include "../document/graphics/graphicsscene.h"
class TUpdateAnimationThread : public QThread
{
public:
    TUpdateAnimationThread();

    void setSleepInterval(int sleepInterval);

private:
    int mSleepInterval;
    TGraphicsScene *mGraphicsScene;

    // QThread interface
protected:
    void run();
};

#endif // TUPDATEANIMATIONTHREAD_H
