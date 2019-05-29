#include "tst_maincontroller.h"
#include <controller/maincontroller.h>
#include <utils/preferences.h>
#include <QtTest>

TestMainController::TestMainController(QObject *parent) : 
    QObject(parent)
{

}

void TestMainController::testJoint()
{
    TCore core;
    TMainWindow mainWindow;
    TMainController controller;
    bool ret = controller.joint(&mainWindow, &core);
    QVERIFY(ret);
    mainWindow.close();
}

void TestMainController::testSetCurrentDocument()
{

}
