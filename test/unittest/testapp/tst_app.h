#ifndef TESTAPP_H
#define TESTAPP_H

#include <QObject>
#include "utils/tst_utils.h"

class TestApp : public QObject
{
    Q_OBJECT

public:
    explicit TestApp(QObject *parent = 0);

signals:

private Q_SLOTS:
    void testStart();
};

#endif // TESTAPP_H
