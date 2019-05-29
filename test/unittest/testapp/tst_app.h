#ifndef TESTAPP_H
#define TESTAPP_H

#include <QObject>
#include <QStringList>
#include "utils/tst_utils.h"

class TApp;
#define ARGC_MAX 10

class TestApp : public QObject
{
    Q_OBJECT

public:
    explicit TestApp(QObject *parent = 0);
    ~TestApp();

private:
    TApp *mApp;
    int mExitCode;
    QStringList mArguments;
    int mArgc;
    char *mArgv[ARGC_MAX];

    void updateArgv();

private Q_SLOTS:
    void testStart();
};

#endif // TESTAPP_H
