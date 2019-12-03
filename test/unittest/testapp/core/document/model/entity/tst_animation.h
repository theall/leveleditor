#ifndef TESTANIMATION_H
#define TESTANIMATION_H

#include <QObject>

class TestAnimation : public QObject
{
    Q_OBJECT

public:
    explicit TestAnimation(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    
};

#endif // TESTANIMATION_H
