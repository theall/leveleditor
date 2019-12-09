#ifndef TESTENEMYFACTORY_H
#define TESTENEMYFACTORY_H

#include <QObject>

class TestEnemyFactory : public QObject
{
    Q_OBJECT

public:
    explicit TestEnemyFactory(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    void testReadWrite2();
    void testReadWrite3();
    
};

#endif // TESTENEMYFACTORY_H
