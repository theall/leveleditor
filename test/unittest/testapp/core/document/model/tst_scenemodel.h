#ifndef TESTSCENEMODEL_H
#define TESTSCENEMODEL_H

#include <QObject>

class TestSceneModel : public QObject
{
    Q_OBJECT

public:
    explicit TestSceneModel(QObject *parent = 0);

private Q_SLOTS:
    void testType();
    void testReadSave();
};

#endif // TESTSCENEMODEL_H
