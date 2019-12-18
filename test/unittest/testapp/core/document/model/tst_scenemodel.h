#ifndef TESTSCENEMODEL_H
#define TESTSCENEMODEL_H

#include <QObject>

class TestSceneModel : public QObject
{
    Q_OBJECT

public:
    explicit TestSceneModel(QObject *parent = 0);
private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
};

#endif // TESTSCENEMODEL_H
