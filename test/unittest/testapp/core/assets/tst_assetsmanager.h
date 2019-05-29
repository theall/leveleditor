#ifndef TESTASSETSMANAGER_H
#define TESTASSETSMANAGER_H

#include <QObject>

class TAssetsManager;
class TestAssetsManager : public QObject
{
    Q_OBJECT

public:
    explicit TestAssetsManager(QObject *parent = 0);

private:
    TAssetsManager *mAssetsManager;
    void slotOnAssetsLoadCompleted();
    void slotAssetsLoadingProgress(int value, int maxValue);

private Q_SLOTS:
    void testSetResourcePath();
    void testLoadResource();
};

#endif // TESTASSETSMANAGER_H
