#include "tst_enemyfactorymodel.h"
#include "testapp/core/document/model/streamiotest.h"
#include <QtTest>
#include <core/document/model/enemyfactorymodel.h>
const char g_enemyfactorymodel_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C'
};

TestEnemyFactoryModel::TestEnemyFactoryModel(QObject *parent) :
    QObject(parent)
{

}




void TestEnemyFactoryModel::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TEnemyFactoryModel, buf, size);
}

void TestEnemyFactoryModel::testReadWrite1()
{
    readWriteTest( g_enemyfactorymodel_data1, sizeof( g_enemyfactorymodel_data1));
}

