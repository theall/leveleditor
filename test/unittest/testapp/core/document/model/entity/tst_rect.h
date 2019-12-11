#ifndef TESTRECT_H
#define TESTRECT_H

#include <QObject>

class TestRect : public QObject
{
    Q_OBJECT

public:
    explicit TestRect(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    void testReadWrite2();
    void testReadWrite3();
};

#endif // TESTRECT_H
