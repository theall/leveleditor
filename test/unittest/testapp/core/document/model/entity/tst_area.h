#ifndef TESTAREA_H
#define TESTAREA_H

#include <QObject>

class TestArea : public QObject
{
    Q_OBJECT

public:
    explicit TestArea(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    void testReadWrite2();
    void testReadWrite3();
};

#endif // TESTAREA_H
