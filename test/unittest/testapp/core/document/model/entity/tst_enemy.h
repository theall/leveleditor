#ifndef TESTENEMY_H
#define TESTENEMY_H

#include <QObject>

class TestEnemy : public QObject
{
    Q_OBJECT

public:
    explicit TestEnemy(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    void testReadWrite2();
    void testReadWrite3();
    void testReadWrite4();
};

#endif // TESTENEMY_H
