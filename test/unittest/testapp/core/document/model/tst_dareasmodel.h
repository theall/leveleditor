#ifndef TESTDAREASMODEL_H
#define TESTDAREASMODEL_H

#include <QObject>

class TestDAreasModel : public QObject
{
    Q_OBJECT

public:
    explicit TestDAreasModel(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    
};

#endif // TESTDAREASMODEL_H
