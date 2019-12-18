#ifndef TESTANIMATIONSMODEL_H
#define TESTANIMATIONSMODEL_H

#include <QObject>

class TestAnimationsModel : public QObject
{
    Q_OBJECT

public:
    explicit TestAnimationsModel(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
};

#endif // TESTANIMATIONSMODEL_H
