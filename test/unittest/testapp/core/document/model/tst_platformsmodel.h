#ifndef TESTPLATFORMSMODEL_H
#define TESTPLATFORMSMODEL_H

#include <QObject>

class TestPlatformsModel : public QObject
{
    Q_OBJECT

public:
    explicit TestPlatformsModel(QObject *parent = 0);
private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    
};

#endif // TESTPLATFORMSMODEL_H
