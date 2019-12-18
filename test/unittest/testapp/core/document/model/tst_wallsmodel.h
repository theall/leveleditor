#ifndef TESTWALLSMODEL_H
#define TESTWALLSMODEL_H

#include <QObject>

class TestWallsModel : public QObject
{
    Q_OBJECT

public:
    explicit TestWallsModel(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    
};

#endif // TESTWALLSMODEL_H
