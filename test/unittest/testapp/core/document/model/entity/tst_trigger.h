#ifndef TESTTRIGGER_H
#define TESTTRIGGER_H

#include <QObject>

class TestTrigger : public QObject
{
    Q_OBJECT

public:
    explicit TestTrigger(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();

};
#endif // TESTTRIGGER_H
