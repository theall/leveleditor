#ifndef TESTFRAME_H
#define TESTFRAME_H

#include <QObject>

class TestFrame : public QObject
{
    Q_OBJECT

public:
    explicit TestFrame(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    void testReadWrite2();
    void testReadWrite3();
};

#endif // TESTFRAME_H
