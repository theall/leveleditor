#ifndef TESTPOINTF_H
#define TESTPOINTF_H

#include <QObject>

class TestPointF : public QObject
{
    Q_OBJECT

public:
    explicit TestPointF(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);
private Q_SLOTS:
    void testReadWrite1();
    void testReadWrite2();
};

#endif // TESTPOINTF_H
