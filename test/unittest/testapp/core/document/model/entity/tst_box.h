#ifndef TESTBOX_H
#define TESTBOX_H

#include <QObject>

class TestBox : public QObject
{
    Q_OBJECT

public:
    explicit TestBox(QObject *parent = 0);
private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();

};

#endif // TESTBOX_H
