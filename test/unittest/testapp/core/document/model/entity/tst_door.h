#ifndef TESTDOOR_H
#define TESTDOOR_H

#include <QObject>

class TestDoor : public QObject
{
    Q_OBJECT

public:
    explicit TestDoor(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTDOOR_H