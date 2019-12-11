#ifndef TESTPOINT_H
#define TESTPOINT_H

#include <QObject>

class TestPoint : public QObject
{
    Q_OBJECT

public:
    explicit TestPoint(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    void testReadWrite2();
};

#endif // TESTPOINT_H
