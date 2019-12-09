#ifndef TESTDAREA_H
#define TESTDAREA_H

#include <QObject>

class TestDArea : public QObject
{
    Q_OBJECT

public:
    explicit TestDArea(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    void testReadWrite2();
    void testReadWrite3();
};

#endif // TESTDAREA_H
