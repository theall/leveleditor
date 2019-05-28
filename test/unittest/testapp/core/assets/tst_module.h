#ifndef TESTMODULE_H
#define TESTMODULE_H

#include <QObject>

class TestModule : public QObject
{
    Q_OBJECT

public:
    explicit TestModule(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTMODULE_H