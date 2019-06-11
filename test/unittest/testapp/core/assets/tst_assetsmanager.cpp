#include "tst_assetsmanager.h"
#include "assert.h"

#include <utils/preferences.h>
#include <core/assets/assetsmanager.h>
#include <macro_for_test.h>

TestAssetsManager::TestAssetsManager(QObject *parent) : 
    QObject(parent)
  , mAssetsManager(TAssetsManager::getInstance())
{
    connect(mAssetsManager, &TAssetsManager::loadCompleted, this, &TestAssetsManager::slotOnAssetsLoadCompleted);
    connect(mAssetsManager, &TAssetsManager::onProgress, this, &TestAssetsManager::slotAssetsLoadingProgress);
}

void TestAssetsManager::slotOnAssetsLoadCompleted()
{
    QVERIFY(!mAssetsManager->getFaceList().isEmpty());
    QVERIFY(!mAssetsManager->getModuleList().isEmpty());
    QVERIFY(!mAssetsManager->getTilesetList().isEmpty());
}

void TestAssetsManager::slotAssetsLoadingProgress(int value, int maxValue)
{
    if(value == maxValue) {
        QVERIFY(value>0);
    }
}

void TestAssetsManager::testSetResourcePath()
{
    QVERIFY(!mAssetsManager->setResourcePath("c:/"));
    QVERIFY(!mAssetsManager->setResourcePath("y:/"));
    QVERIFY(!mAssetsManager->setResourcePath(TPreferences::instance()->gameRoot()));
}

void TestAssetsManager::testLoadResource()
{
    QString gameRoot = TPreferences::instance()->gameRoot();
    QVERIFY(mAssetsManager->load(gameRoot, false));
    QVERIFY(mAssetsManager->load(gameRoot));
}

