#ifndef TESTAPP_H
#define TESTAPP_H

#include <QObject>
#include "utils/tst_utils.h"

class TApp;
class TestApp : public QObject
{
    Q_OBJECT

public:
    explicit TestApp(QObject *parent = 0);
    ~TestApp();

private:
    TApp *mApp;

private Q_SLOTS:
    void testStart();
};

#endif // TESTAPP_H
