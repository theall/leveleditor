#ifndef TESTTILE_H
#define TESTTILE_H

#include <QObject>

class TestTile : public QObject
{
    Q_OBJECT

public:
    explicit TestTile(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    void testReadWrite2();
    void testReadWrite3();
};

#endif // TESTTILE_H
