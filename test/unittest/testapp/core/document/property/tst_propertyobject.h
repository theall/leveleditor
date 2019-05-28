#ifndef TESTPROPERTYOBJECT_H
#define TESTPROPERTYOBJECT_H

#include <QObject>

class TestPropertyObject : public QObject
{
    Q_OBJECT

public:
    explicit TestPropertyObject(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTPROPERTYOBJECT_H