#ifndef TESTENEMYFACTORYMODEL_H
#define TESTENEMYFACTORYMODEL_H

#include <QObject>

class TestEnemyFactoryModel : public QObject
{
    Q_OBJECT

public:
    explicit TestEnemyFactoryModel(QObject *parent = 0);
private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
};

#endif // TESTENEMYFACTORYMODEL_H
