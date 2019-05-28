#include "tst_app.h"
#include "utils/tst_utils.h"
#include "core/tst_core.h"
#include "gui/tst_mainwindow.h"
#include "controller/tst_controller.h"
#include "../macro_for_test.h"

#include "../../../src/app/app.h"

TestApp::TestApp(QObject *parent) : QObject(parent)
{
    RUN_CLASS(TestUtils);
    RUN_CLASS(TestCore);
    RUN_CLASS(TestMainWindow);
    RUN_CLASS(TestController);
}

TestApp::~TestApp()
{

}

void TestApp::testStart()
{

}
