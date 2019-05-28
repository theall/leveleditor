#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QObject>

class TestObject : public QObject
{
    Q_OBJECT

public:
    explicit TestObject(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTOBJECT_H