#include "tst_app.h"
#include "utils/tst_utils.h"
#include "core/tst_core.h"
#include "gui/tst_mainwindow.h"
#include "controller/tst_controller.h"
#include "../macro_for_test.h"

#include <app.h>
#include <QtTest>
#include <utils/preferences.h>

#define MAX_PATH 256
TestApp::TestApp(QObject *parent) :
    QObject(parent)
  , mApp(nullptr)
  , mExitCode(-1)
  , mArgc(0)
{
    QStringList sl = qApp->arguments();
    QString validPath;
    sl.pop_front();
    for(QString s : sl) {
        if(!s.startsWith('-')) {
            validPath = s;
            break;
        }
    }
    if(validPath.isEmpty())
        throw("Need game root as test argument!");

    RUN_CLASS(TestUtils);

    TPreferences::instance()->setGameRoot(validPath);

    RUN_CLASS(TestCore);
    //RUN_CLASS(TestMainWindow);
    //RUN_CLASS(TestController);

    mArguments.append(qApp->applicationFilePath());
    for(int i=0;i<ARGC_MAX;i++) {
        mArgv[i] = new char[MAX_PATH];
    }
}

TestApp::~TestApp()
{
    for(int i=0;i<ARGC_MAX;i++) {
        delete mArgv[i];
    }
}

void TestApp::updateArgv()
{
    mArgc = qMin(ARGC_MAX, mArguments.size());
    for(int i=0;i<mArgc;i++) {
        std::string a = mArguments.at(i).toStdString();
        strcpy(mArgv[i], a.c_str());
    }
}

void TestApp::testStart()
{

}
