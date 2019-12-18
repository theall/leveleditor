#ifndef TESTRESPAWNSMODEL_H
#define TESTRESPAWNSMODEL_H

#include <QObject>

class TestRespawnsModel : public QObject
{
    Q_OBJECT

public:
    explicit TestRespawnsModel(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    
};

#endif // TESTRESPAWNSMODEL_H
