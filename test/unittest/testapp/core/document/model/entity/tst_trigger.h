#ifndef TESTTRIGGER_H
#define TESTTRIGGER_H

#include <QObject>

class TestTrigger : public QObject
{
    Q_OBJECT

public:
    explicit TestTrigger(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTTRIGGER_H