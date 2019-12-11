#ifndef TESTWALL_H
#define TESTWALL_H

#include <QObject>

class TestWall : public QObject
{
    Q_OBJECT

public:
    explicit TestWall(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    void testReadWrite2();
    void testReadWrite3();
};

#endif // TESTWALL_H
