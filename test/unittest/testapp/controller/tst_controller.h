#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>

class TestController : public QObject
{
    Q_OBJECT

public:
    explicit TestController(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTCONTROLLER_H
