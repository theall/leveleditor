#ifndef TESTWALL_H
#define TESTWALL_H

#include <QObject>

class TestWall : public QObject
{
    Q_OBJECT

public:
    explicit TestWall(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTWALL_H