#include "updateanimationthread.h"

TUpdateAnimationThread::TUpdateAnimationThread()
{

}

void TUpdateAnimationThread::setSleepInterval(int sleepInterval)
{
    mSleepInterval = sleepInterval;
}

void TUpdateAnimationThread::run()
{
    while(true) {
        //mGraphicsScene->step();
        sleep(mSleepInterval);
    }
}
