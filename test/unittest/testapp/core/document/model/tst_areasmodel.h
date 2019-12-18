#ifndef TESTAREASMODEL_H
#define TESTAREASMODEL_H

#include <QObject>

class TestAreasModel : public QObject
{
    Q_OBJECT

public:
    explicit TestAreasModel(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    
};

#endif // TESTAREASMODEL_H
