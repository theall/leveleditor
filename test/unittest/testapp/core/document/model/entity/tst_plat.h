#ifndef TESTPLAT_H
#define TESTPLAT_H

#include <QObject>

class TestPlat : public QObject
{
    Q_OBJECT

public:
    explicit TestPlat(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();

};

#endif // TESTPLAT_H
