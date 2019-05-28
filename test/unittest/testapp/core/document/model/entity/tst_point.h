#ifndef TESTPOINT_H
#define TESTPOINT_H

#include <QObject>

class TestPoint : public QObject
{
    Q_OBJECT

public:
    explicit TestPoint(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTPOINT_H