#ifndef TESTABSTRACTCONTROLLER_H
#define TESTABSTRACTCONTROLLER_H

#include <QObject>

class TestAbstractController : public QObject
{
    Q_OBJECT

public:
    explicit TestAbstractController(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTABSTRACTCONTROLLER_H