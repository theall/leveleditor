#ifndef TESTTILELAYERMODEL_H
#define TESTTILELAYERMODEL_H

#include <QObject>

class TestTileLayerModel : public QObject
{
    Q_OBJECT

public:
    explicit TestTileLayerModel(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    
};

#endif // TESTTILELAYERMODEL_H
