#include "tst_app.h"
#include "utils/tst_utils.h"
#include "../macro_for_test.h"

#include "../../../src/app/app.h"

TestApp::TestApp(QObject *parent) : QObject(parent)
{
    RUN_CLASS(TestUtils);
}

void TestApp::testStart()
{

}
